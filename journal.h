#ifndef JOURNAL_H
#define JOURNAL_H

#include "note.h"
#include "collection.h"
#include "water.h"
#include "branches.h"

class Journal : public Collection {
public:
    Journal();
    Journal(size_t n);
    Journal(const Journal& other_);
    Journal(Journal&& other_) = default;
    Journal& operator=(const Journal& other_);
    Journal& operator=(Journal&& other_) = default;
    ~Journal() = default;
    Note& searchIndex(size_t n) const;
    void clear();
    void pushBackWater(const Water& note);
    void pushBackBranches(const Branches& note);
    size_t size() const;
    void erase(size_t n);
    void writeToFile(std::string filename) const;
    void readFromFile(std::string filename);
    bool checkLogic() const;
    bool checkData() const;

private:
    struct notes{
        Water m_water;
        Branches m_branches;
    };
    notes *m_notes;
    size_t m_size;
    size_t m_allocated;
    void copyFromOther(const Journal& other);
};

#endif // JOURNAL_H
