#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "water.h"
#include "branches.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->lineCourse->setValidator(&m_int_validator);
    ui->lineYear->setValidator(&m_int_validator);
    ui->lineMonth->setValidator(&m_int_validator);
    ui->lineDay->setValidator(&m_int_validator);
    ui->lineNumber->setValidator(&m_double_validator);
    ui->lineErase->setValidator(&m_int_validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showJournal() {
    ui->journalElements->clear();
    for (size_t i = 0; i < m_journal.size(); ++i) {
        Note tmp_data;
        tmp_data = m_journal.searchIndex(i);
        if (tmp_data.getStudent()[0] != "") {
            output(QString("%1 note: ").arg(i));
            for (size_t j = 0; j < tmp_data.getDate().size(); ++j)
                output(QString("%1 ").arg(tmp_data.getDate()[j]));
            for (size_t j = 0; j < tmp_data.getStudent().size(); ++j) {
                QString str = QString::fromStdString(tmp_data.getStudent()[j]);
                output(str + " ");
            }
            output(QString("%1").arg(tmp_data.getNumber()));
            output(QString("\n"));
        }
    }
}

void MainWindow::on_pushButtonAdd_clicked() {
    std::vector<unsigned int> tmp_date;
    std::vector<std::string> tmp_student;
    tmp_date.push_back(ui->lineYear->text().toInt());
    tmp_date.push_back(ui->lineMonth->text().toInt());
    tmp_date.push_back(ui->lineDay->text().toInt());
    tmp_student.push_back(ui->lineFirstName->text().toStdString());
    tmp_student.push_back(ui->lineLastName->text().toStdString());
    tmp_student.push_back(ui->linePatronymic->text().toStdString());
    tmp_student.push_back(ui->lineCourse->text().toStdString());
    if (ui->radioButtonWater->isChecked()) {
        if (tmp_student[0] != "" && tmp_student[1] != "" && tmp_student[2] != "" && tmp_student[3] != ""
                && tmp_date[0] != 0 && tmp_date[1] != 0 && tmp_date[2] != 0 &&
                ui->lineNumber->text().toDouble() != 0) {
            Water water_note;
            water_note.setData(tmp_date);
            water_note.setStudent(tmp_student);
            water_note.setNumber(ui->lineNumber->text().toDouble());
            m_journal.pushBackWater(water_note);
            ui->pushButtonClear->setEnabled(true);
            log(QString("Water note was added, %1 logic errors, %2 care errors"
                        ).arg(m_journal.checkLogic() ? "some" : "no", m_journal.checkData() ? "no" : "some"));
        }
        else
            log(QString("Water note was not added"));
    }
    else {
        if (tmp_student[0] != "" && tmp_student[1] != "" && tmp_student[2] != "" && tmp_student[3] != ""
                && tmp_date[0] != 0 && tmp_date[1] != 0 && tmp_date[2] != 0 &&
                ui->lineNumber->text().toDouble() != 0) {
            Branches branches_note;
            branches_note.setData(tmp_date);
            branches_note.setStudent(tmp_student);
            branches_note.setNumber(ui->lineNumber->text().toDouble());
            m_journal.pushBackBranches(branches_note);
            ui->pushButtonClear->setEnabled(true);
            log(QString("Branches note was added, %1 logic errors, %2 care errors"
                        ).arg(m_journal.checkLogic() ? "some" : "no", m_journal.checkData() ? "no" : "some"));
        }
        else
            log(QString("Branches note was not added"));
    }
    ui->pushButtonWrite->setEnabled(true);
    showJournal();
}

void MainWindow::on_pushButtonClear_clicked() {
    m_journal.clear();
    log(QString("Journal is emply; size is %1").arg(QString::number(m_journal.size())));
    ui->pushButtonClear->setEnabled(false);
    ui->pushButtonRead->setEnabled(true);
    ui->journalElements->clear();
}

void MainWindow::on_pushButtonRead_clicked() {
    ui->pushButtonClear->setEnabled(true);
    ui->pushButtonWrite->setEnabled(true);
    ui->pushButtonRead->setEnabled(false);
    ui->journalElements->clear();
    m_journal.clear();
    m_journal.readFromFile("C:\\Users\\liza\\Documents\\lab1\\part2\\input.txt");
    showJournal();
    log(QString("Read journal from file, %1 logic errors").arg(m_journal.checkLogic() ? "some" : "no"));
}

void MainWindow::on_pushButtonWrite_clicked() {
    m_journal.writeToFile("C:\\Users\\liza\\Documents\\lab1\\part2\\output.txt");
    log(QString("Journal was written to file"));
}

void MainWindow::log(const QString &text_) {
    ui->textEdit->setText(ui->textEdit->toPlainText() + text_ + "\n");
}

void MainWindow::output(const QString &text_) {
    ui->journalElements->setText(ui->journalElements->toPlainText() + text_);
}

void MainWindow::on_lineErase_textChanged() {
    ui->pushButtonErase->setEnabled(true);
}

void MainWindow::on_pushButtonErase_clicked() {
    if (m_journal.size() > 0) {
        m_journal.erase(ui->lineErase->text().toInt());
        showJournal();
        log(QString("Note was erased"));
    }
    else
        log(QString("Error! Journal is already empty"));
}
