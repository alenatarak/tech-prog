#pragma once
#include <iosfwd>
#include <string>

class Base {
   public:
    Base();
    Base(const Base& other);
    Base& operator=(const Base& other);
    virtual ~Base();
    virtual int type() const = 0;
    virtual Base* clone() const = 0;
    virtual void input() = 0;
    virtual void print(std::ostream& out) const = 0;
    virtual void save(std::ostream& out) const = 0;
    virtual void load(std::istream& in) = 0;
};
