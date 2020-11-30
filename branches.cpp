#include "branches.h"

using namespace std;

vector<unsigned int> Branches::getDate() const {
    return date_info_;
};

vector<string> Branches::getStudent() const {
    return student_info_;
};

double Branches::getNumber() const {
    return number_;
}

double Branches::getInterval() const {
    return INTERVAL;
};

double Branches::getMax() const {
    return BRANCHES_MAX;
}

double Branches::getMin() const {
    return BRANCHES_MIN;
};

