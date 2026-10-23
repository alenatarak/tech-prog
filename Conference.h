#pragma once
#include <iosfwd>
#include <string>

class Conference {
   public:
    Conference();
    Conference(const Conference& other);
    Conference& operator=(const Conference& other);
    virtual ~Conference();
    virtual int type() const = 0;
    virtual Conference* clone() const = 0;
    virtual void input() = 0;
    virtual void print(std::ostream& out) const = 0;
    virtual void save(std::ostream& out) const = 0;
    virtual void load(std::istream& in) = 0;
};
