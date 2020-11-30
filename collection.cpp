#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <memory>

#include "collection.h"
#include "note.h"

using namespace std;

Collection::Collection() {
    this->m_size = 0;
    this->m_allocated = 0;
    this->m_data = nullptr;
}

Collection::Collection(size_t n) {
    this->m_size = n;
    this->m_allocated = this->m_size;
    this->m_data = new Note[this->m_size];
}

Collection::Collection(const Collection& other) {
    copyFromOther(other);
}

Collection &Collection::operator=(const Collection &other) {
    copyFromOther(other);
    return *this;
}


void Collection::writeToFile(string filename) const {
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

void Collection::readFromFile(string filename) {
    ifstream file (filename);
    size_t n;
    Note tmp_data;
    vector<unsigned int> tmp_date;
    vector<string> tmp_student;
    string buffer_string;
    size_t buffer_integer;
    if (file.is_open()) {
        file >> n;
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < 3; ++j) {
                file >> buffer_integer;
                tmp_date.push_back(buffer_integer);
            }
            for (size_t j = 0; j < 3; ++j) {
                file >> buffer_string;
                tmp_student.push_back(buffer_string);
            }
            file >> buffer_integer;
            tmp_data.setNumber(buffer_integer);
            tmp_data.setData(tmp_date);
            tmp_data.setStudent(tmp_student);
            tmp_date.clear();
            tmp_student.clear();
            this->pushBack(tmp_data);
        }
    }
    file.close();
}

size_t Collection::size() const {
    return this->m_size;
}

Note &Collection::searchIndex(size_t n) const {
    if (n >= this->m_size) {
        throw out_of_range("");
    }
    return this->m_data[n];
}

void Collection::pushBack(const Note &note) {
    if (this->m_size >= this->m_allocated) {
        this->m_allocated += 1;
        auto newMemory = new Note[this->m_allocated];
        for (size_t i = 0; i < this->m_size; ++i) {
            newMemory[i] = this->m_data[i];
        }
        delete[] this->m_data;
        this->m_data = new Note[this->m_allocated];
        for (size_t i = 0; i < this->m_size; ++i) {
            this->m_data[i] = newMemory[i];
        }
        delete[] newMemory;
    }
    this->m_data[this->m_size] = note;
    ++this->m_size;
}

void Collection::erase(size_t n) {
    if (this->m_size > 0) {
        this->m_allocated -= 1;
        auto newMemory = new Note[this->m_allocated];
        for (size_t i = 0; i < n; ++i) {
            newMemory[i] = this->m_data[i];
        }
        for (size_t i = n; i < this->m_size; i++)
            newMemory[i-1] = this->m_data[i];
        delete[] this->m_data;
        this->m_data = new Note[this->m_allocated];
        for (size_t i = 0; i < this->m_size; ++i) {
            this->m_data[i] = newMemory[i];
        }
        delete[] newMemory;
    }
    --this->m_size;
}

void Collection::clear() {
    if (this->m_size > 0) {
        delete[] this->m_data;
        this->m_data = nullptr;
        this->m_size = 0;
        this->m_allocated = 0;
    }
}


void Collection::copyFromOther(const Collection& other) {
    this->m_size = other.m_size;
    this->m_data = new Note[m_size];
    this->m_allocated = this->m_size;
    for (size_t i = 0; i < this->m_size; ++i) {
        this->m_data[i] = other.m_data[i];
    }
}
