#include "water.h"

using namespace std;

vector<unsigned int> Water::getDate() const {
    return date_info_;
};

vector<string> Water::getStudent() const {
    return student_info_;
};

double Water::getNumber() const {
    return number_;
}

double Water::getInterval() const {
    return INTERVAL;
}

double Water::getMax() const {
    return WATER_MAX;
}

double Water::getMin() const {
    return WATER_MIN;
};

