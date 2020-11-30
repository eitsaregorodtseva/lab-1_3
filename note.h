#ifndef NOTE_H
#define NOTE_H

#include <vector>
#include <string>


class Note {
public:
    Note() = default;
    Note(const std::vector<unsigned int>& data_info,
         const std::vector<std::string>& student_info,
         const double number);
    Note(const Note& copy_);
    Note(Note&& copy_) = default;
    Note& operator=(const Note& copy_) = default;
    Note& operator=(Note&& copy_) = default;

    virtual std::vector<unsigned int> getDate() const;
    virtual std::vector<std::string> getStudent() const;
    virtual double getNumber() const;
    virtual double getInterval() const;
    virtual double getMax() const;
    virtual double getMin() const;
     void setData(const std::vector<unsigned int>& data_info);
     void setStudent(const std::vector<std::string>& student_info);
     void setNumber(const double number);

    ~Note() = default;

protected:
    std::vector<unsigned int> date_info_{0, 0, 0}; //Год Месяц День
    std::vector<std::string> student_info_{"", "", "", ""};
    double number_{0};
    double interval_{0};
    double max_{0};
    double min_{0};
};

#endif // NOTE_H
