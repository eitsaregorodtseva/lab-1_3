#include "note.h"

using namespace std;

Note::Note(const vector<unsigned int>& date_info, const vector<string>& student_info,
           const double number) {
    setData(date_info);
    setStudent(student_info);
    setNumber(number);
};

Note::Note(const Note& copy) {
    setData(copy.getDate());
    setStudent(copy.getStudent());
    setNumber(copy.getNumber());
};

vector<unsigned int> Note::getDate() const {
    return date_info_;
};

vector<string> Note::getStudent() const {
    return student_info_;
};

double Note::getNumber() const {
    return number_;
}

double Note::getInterval() const {
    return interval_;
}

double Note::getMax() const {
    return max_;
};

double Note::getMin() const {
    return min_;
};

void Note::setData(const vector<unsigned int>& date_info) {
    date_info_ = date_info;
};

void Note::setStudent(const vector<string>& student_info) {
    student_info_ = student_info;
};

void Note::setNumber(const double number) {
    if (number >= 0)
        number_ = number;
};
