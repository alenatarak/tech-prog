#pragma once
#include <string>
#include "Conference.h"

class Keeper {
    Conference** items_;
    int size_;
    int capacity_;
    void reserve(int capacity);
    void swap(Keeper& other) noexcept;

   public:
    Keeper();
    explicit Keeper(int capacity);
    Keeper(const Keeper& other);
    Keeper& operator=(const Keeper& other);
    ~Keeper();
    int size() const;
    void add(const Conference& item);
    void remove(int index);
    Conference& at(int index);
    const Conference& at(int index) const;
    void clear();
    void printAll() const;
    void save(const std::string& filename) const;
    void load(const std::string& filename);
};
