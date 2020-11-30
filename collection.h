#ifndef COLLECTION_H
#define COLLECTION_H

#include "note.h"
#include <memory>


class Collection {
public:
    Collection();
    Collection(size_t n);
    Collection(const Collection& other);
    Collection(Collection&& other) = default;
    Collection& operator=(const Collection& other);
    Collection& operator=(Collection&& other) = default;
    Note& searchIndex(size_t n) const;
    size_t size() const;
    void clear();
    void pushBack(const Note& note);
    void erase(size_t n);
    void writeToFile(std::string filename) const;
    void readFromFile(std::string filename);
    ~Collection() = default;

private:
    Note *m_data;
    size_t m_size;
    size_t m_allocated;
    void copyFromOther(const Collection& other);
};

#endif // COLLECTION_H



