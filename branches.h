#ifndef BRANCHES_H
#define BRANCHES_H

#include "note.h"

class Branches : public Note {
public:
    std::vector<unsigned int> getDate() const override;
    std::vector<std::string> getStudent() const override;
    double getNumber() const override;
    double getInterval() const override;
    double getMax() const override;
    double getMin() const override;

private:
    static constexpr double BRANCHES_MIN = 4;
    static constexpr double BRANCHES_MAX = 8;
    static constexpr double INTERVAL = 6;
    double branches_number{0};
};

#endif // BRANCHES_H
