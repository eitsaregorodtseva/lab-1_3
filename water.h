#ifndef WATER_H
#define WATER_H

#include <note.h>

class Water : public Note {
public:
std::vector<unsigned int> getDate() const override;
    std::vector<std::string> getStudent() const override;
    double getNumber() const override;
    double getInterval() const override;
    double getMax() const override;
    double getMin() const override;

private:
    static constexpr double INTERVAL = 0;
    static constexpr double WATER_MAX = 2;
    static constexpr double WATER_MIN = 1;
    double water_number{0};
};

#endif // WATER_H
