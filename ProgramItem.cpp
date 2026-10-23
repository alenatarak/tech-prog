#include "ProgramItem.h"
#include <iostream>
#include <stdexcept>
#include "Utils.h"
namespace {
void validate(const std::string& s) {
    if (s.empty())
        throw std::invalid_argument("Поле не может быть пустым");
}
}  
ProgramItem::ProgramItem() {
    std::cout << "[Программа] конструктор без параметров\n";
}
ProgramItem::ProgramItem(const std::string& d, const std::string& t,
                         const std::string& n) {
    setDay(d);
    setTime(t);
    setTitle(n);
    std::cout << "[Программа] конструктор с параметрами\n";
}
ProgramItem::ProgramItem(const ProgramItem& p)
    : Conference(p), day_(p.day_), time_(p.time_), title_(p.title_) {
    std::cout << "[Программа] конструктор копирования\n";
}
ProgramItem& ProgramItem::operator=(const ProgramItem& p) {
    if (this != &p) {
        day_ = p.day_;
        time_ = p.time_;
        title_ = p.title_;
    }
    return *this;
}
ProgramItem::~ProgramItem() {
    std::cout << "[Программа] деструктор\n";
}
const std::string& ProgramItem::getDay() const {
    return day_;
}
const std::string& ProgramItem::getTime() const {
    return time_;
}
const std::string& ProgramItem::getTitle() const {
    return title_;
}
void ProgramItem::setDay(const std::string& s) {
    validate(s);
    day_ = s;
}
void ProgramItem::setTime(const std::string& s) {
    validate(s);
    time_ = s;
}
void ProgramItem::setTitle(const std::string& s) {
    validate(s);
    title_ = s;
}
int ProgramItem::type() const {
    return 3;
}
Conference* ProgramItem::clone() const {
    return new ProgramItem(*this);
}
void ProgramItem::input() {
    setDay(readText("День / дата: "));
    setTime(readText("Время выступления: "));
    setTitle(readText("Наименование мероприятия: "));
}
void ProgramItem::print(std::ostream& out) const {
    out << "Программа | День: " << day_ << " | Время: " << time_
        << " | Наименование: " << title_;
}
void ProgramItem::save(std::ostream& out) const {
    writeString(out, day_);
    writeString(out, time_);
    writeString(out, title_);
}
void ProgramItem::load(std::istream& in) {
    setDay(readString(in));
    setTime(readString(in));
    setTitle(readString(in));
}
