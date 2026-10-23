#include "Administrator.h"
#include <iostream>
#include <stdexcept>
#include "Utils.h"
namespace {
void validate(const std::string& s) {
    if (s.empty())
        throw std::invalid_argument("Поле не может быть пустым");
}
}  
Administrator::Administrator() {
    std::cout << "[Администрация] конструктор без параметров\n";
}
Administrator::Administrator(const std::string& n, const std::string& p,
                             const std::string& r) {
    setFullName(n);
    setPosition(p);
    setResponsibility(r);
    std::cout << "[Администрация] конструктор с параметрами\n";
}
Administrator::Administrator(const Administrator& a)
    : Conference(a),
      fullName_(a.fullName_),
      position_(a.position_),
      responsibility_(a.responsibility_) {
    std::cout << "[Администрация] конструктор копирования\n";
}
Administrator& Administrator::operator=(const Administrator& a) {
    if (this != &a) {
        fullName_ = a.fullName_;
        position_ = a.position_;
        responsibility_ = a.responsibility_;
    }
    return *this;
}
Administrator::~Administrator() {
    std::cout << "[Администрация] деструктор\n";
}
const std::string& Administrator::getFullName() const {
    return fullName_;
}
const std::string& Administrator::getPosition() const {
    return position_;
}
const std::string& Administrator::getResponsibility() const {
    return responsibility_;
}
void Administrator::setFullName(const std::string& s) {
    validate(s);
    fullName_ = s;
}
void Administrator::setPosition(const std::string& s) {
    validate(s);
    position_ = s;
}
void Administrator::setResponsibility(const std::string& s) {
    validate(s);
    responsibility_ = s;
}
int Administrator::type() const {
    return 2;
}
Conference* Administrator::clone() const {
    return new Administrator(*this);
}
void Administrator::input() {
    setFullName(readText("ФИО: "));
    setPosition(readText("Должность: "));
    setResponsibility(readText("Область ответственности: "));
}
void Administrator::print(std::ostream& out) const {
    out << "Администрация | ФИО: " << fullName_ << " | Должность: " << position_
        << " | Ответственность: " << responsibility_;
}
void Administrator::save(std::ostream& out) const {
    writeString(out, fullName_);
    writeString(out, position_);
    writeString(out, responsibility_);
}
void Administrator::load(std::istream& in) {
    setFullName(readString(in));
    setPosition(readString(in));
    setResponsibility(readString(in));
}
