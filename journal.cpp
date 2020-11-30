#include <algorithm>
#include <fstream>
#include <map>

#include "journal.h"
#include "note.h"
#include "water.h"
#include "branches.h"
#include "collection.h"

using namespace std;

Journal::Journal() {
    this->m_size = 0;
    this->m_allocated = 0;
    this->m_notes = nullptr;
}

Journal::Journal(size_t n) {
    this->m_size = n;
    this->m_allocated = this->m_size;
    this->m_notes = new notes[this->m_size];
}

Journal::Journal(const Journal &other) {
    copyFromOther(other);
}

Journal &Journal::operator=(const Journal &other) {
    copyFromOther(other);
    return *this;
}

void Journal::clear() {
    if (this->m_size > 0) {
    for (size_t i = 0; i < this->m_size; i++)
        this->erase(i);
    this->m_size = 0;
    this->m_allocated = 0;
    }
}

void Journal::pushBackWater(const Water &note) {
    if (this->m_size >= this->m_allocated) {
        this->m_allocated += 1;
        auto newMemory = new notes[this->m_allocated];
        for (size_t i = 0; i < this->m_size; ++i) {
            newMemory[i] = this->m_notes[i];
        }
        delete[] this->m_notes;
        this->m_notes = new notes[this->m_allocated];
        for (size_t i = 0; i < this->m_size; ++i) {
            this->m_notes[i] = newMemory[i];
        }
        delete[] newMemory;
    }
    this->m_notes[this->m_size].m_water = note;
    Branches note_;
    this->m_notes[this->m_size].m_branches = note_;
    ++this->m_size;
}

void Journal::pushBackBranches(const Branches &note) {
    if (this->m_size >= this->m_allocated) {
        this->m_allocated += 1;
        auto newMemory = new notes[this->m_allocated];
        for (size_t i = 0; i < this->m_size; ++i) {
            newMemory[i] = this->m_notes[i];
        }
        delete[] this->m_notes;
        this->m_notes = new notes[this->m_allocated];
        for (size_t i = 0; i < this->m_size; ++i) {
            this->m_notes[i] = newMemory[i];
        }
        delete[] newMemory;
    }
    this->m_notes[this->m_size].m_branches = note;
    Water note_;
    this->m_notes[this->m_size].m_water = note_;
    ++this->m_size;
}

size_t Journal::size() const {
    return this->m_size;;
}

void Journal::erase(size_t n) {
    if (this->m_size > 0) {
        this->m_allocated = this->m_size - 1;
        auto newMemory = new notes[this->m_allocated];
        for (size_t i = 0; i < n; ++i) {
            newMemory[i] = this->m_notes[i];
        }
        for (size_t i = n; i < this->m_size - 1; i++) {
            newMemory[i] = this->m_notes[i + 1];
        }
        delete[] this->m_notes;
        this->m_notes = new notes[this->m_allocated];
        for (size_t i = 0; i < this->m_allocated; ++i) {
            this->m_notes[i] = newMemory[i];
        }
        delete[] newMemory;
        --this->m_size;
    }   
}

void Journal::writeToFile(string filename) const {
    ofstream file (filename);
    Note tmp_data;
    if (file.is_open()) {
        file << this->m_size << endl;
        for (size_t i = 0; i < this->m_size; ++i) {
            tmp_data = this->searchIndex(i);
            for (size_t j = 0; j < tmp_data.getDate().size(); ++j)
                file << tmp_data.getDate()[j] << endl;
            for (size_t j = 0; j < tmp_data.getStudent().size(); ++j)
                file << tmp_data.getStudent()[j] << endl;
            file << tmp_data.getNumber() << endl;
        }
    }
    file.close();
}

void Journal::readFromFile(string filename) {
    ifstream file (filename);
    size_t n;
    string s;
    vector<unsigned int> tmp_date;
    vector<string> tmp_student;
    string buffer_string;
    size_t buffer_integer;
    if (file.is_open()) {
        file >> n;
        for (size_t i = 0; i < n; ++i) {
            file >> s;
            for (size_t j = 0; j < 3; ++j) {
                file >> buffer_integer;
                tmp_date.push_back(buffer_integer);
            }
            for (size_t j = 0; j < 3; ++j) {
                file >> buffer_string;
                tmp_student.push_back(buffer_string);
            }
            file >> buffer_integer;
            if (s == "w") {
                Water tmp_data;
                tmp_data.setNumber(buffer_integer);
                tmp_data.setData(tmp_date);
                tmp_data.setStudent(tmp_student);
                tmp_date.clear();
                tmp_student.clear();
                this->pushBackWater(tmp_data);
            }
            else {
                Branches tmp_data;
                tmp_data.setNumber(buffer_integer);
                tmp_data.setData(tmp_date);
                tmp_data.setStudent(tmp_student);
                tmp_date.clear();
                tmp_student.clear();
                this->pushBackBranches(tmp_data);
            }
        }
    }
    file.close();
}

void Journal::copyFromOther(const Journal &other) {
    this->m_size = other.m_size;
    this->m_notes = new notes[m_size];
    this->m_allocated = this->m_size;
    for (size_t i = 0; i < this->m_size; ++i) {
        this->m_notes[i] = other.m_notes[i];
    }
}

Note &Journal::searchIndex(size_t n) const {
    if (n >= this->m_size) {
        throw out_of_range("");
    }
    if (this->m_notes[n].m_water.getStudent()[0] != "")
        return this->m_notes[n].m_water;
    else
        return this->m_notes[n].m_branches;
}

 bool Journal::checkLogic() const {
    bool error = 1;
    if (this->m_size > 0) {
        vector<vector<unsigned int>> sort_date, unsort_date;
        Note tmp_data;
        for (size_t i = 0; i < this-> m_size; ++i) {
            tmp_data = searchIndex(i);
            sort_date.push_back(tmp_data.getDate());
            unsort_date.push_back(tmp_data.getDate());
        }
        sort(sort_date.begin(), sort_date.end());
        if (sort_date == unsort_date) {
            error = 0;
        }
    }
    return error;
 }

 bool Journal::checkData() const {
     bool error_1 = 1, error_2 = 1;
     Note tmp_data;
     map<vector<unsigned int>, double> water_map, branches_map;
     vector<vector<unsigned int>> branches_dates;
     for (size_t i = 0; i < this->m_size; ++i) {
         auto tmp_data = searchIndex(i);
         if (this->m_notes[i].m_water.getStudent()[0] != "") {
             if (water_map.count(tmp_data.getDate()) == 0)
                 water_map[tmp_data.getDate()] = tmp_data.getNumber();
             else
                 water_map[tmp_data.getDate()] += tmp_data.getNumber();
         }
         else
             if (branches_map.count(tmp_data.getDate()) == 0) {
                 branches_map[tmp_data.getDate()] = tmp_data.getNumber();
                 branches_dates.push_back(tmp_data.getDate());
             }
             else
                 branches_map[tmp_data.getDate()] += tmp_data.getNumber();
     }
     if (water_map.size() > 0) {
     for (auto a : water_map)
         if (a.second >= 1 && a.second <= 2)
             error_1 = 1;
         else
             return error_1 = 0;
     }
     if (branches_map.size() > 0) {
         vector<double> sums;
         double sum = 0;
         for (size_t i = 0; i < branches_dates.size() - 1; i++) {
             sum = branches_map.find(branches_dates[i])->second;
             for (size_t j = 1; j < branches_dates.size(); j++)
                 if (branches_map.find(branches_dates[i])->first[0] -
                         branches_map.find(branches_dates[j])->first[0] == 0)
                     if (branches_map.find(branches_dates[i])->first[1] -
                             branches_map.find(branches_dates[j])->first[1] == 0)
                         if (branches_map.find(branches_dates[i])->first[2] -
                                 branches_map.find(branches_dates[j])->first[2] <=6)
                             sum += branches_map.find(branches_dates[j])->second;
             sums.push_back(sum);
             sum = 0;
         }
     for (auto a : sums)
         if (a >= 4 && a <= 8)
             error_2 = 1;
         else
             return error_2 = 0;
     }
     return error_1&&error_2;
}
