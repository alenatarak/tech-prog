#include "Speaker.h"
#include <iostream>
#include <stdexcept>
#include "Utils.h"
namespace {
void validate(const std::string& s) {
    if (s.empty())
        throw std::invalid_argument("Поле не может быть пустым");
}
}  // namespace
Speaker::Speaker() {
    std::cout << "[Выступающий] конструктор без параметров\n";
}
Speaker::Speaker(const std::string& n, const std::string& o,
                 const std::string& r, const std::string& a) {
    setFullName(n);
    setOrganization(o);
    setReport(r);
    setAnnotation(a);
    std::cout << "[Выступающий] конструктор с параметрами\n";
}
Speaker::Speaker(const Speaker& s)
    : Base(s),
      fullName_(s.fullName_),
      organization_(s.organization_),
      report_(s.report_),
      annotation_(s.annotation_) {
    std::cout << "[Выступающий] конструктор копирования\n";
}
Speaker& Speaker::operator=(const Speaker& s) {
    if (this != &s) {
        fullName_ = s.fullName_;
        organization_ = s.organization_;
        report_ = s.report_;
        annotation_ = s.annotation_;
    }
    return *this;
}
Speaker::~Speaker() {
    std::cout << "[Выступающий] деструктор\n";
}
const std::string& Speaker::getFullName() const {
    return fullName_;
}
const std::string& Speaker::getOrganization() const {
    return organization_;
}
const std::string& Speaker::getReport() const {
    return report_;
}
const std::string& Speaker::getAnnotation() const {
    return annotation_;
}
void Speaker::setFullName(const std::string& s) {
    validate(s);
    fullName_ = s;
}
void Speaker::setOrganization(const std::string& s) {
    validate(s);
    organization_ = s;
}
void Speaker::setReport(const std::string& s) {
    validate(s);
    report_ = s;
}
void Speaker::setAnnotation(const std::string& s) {
    validate(s);
    annotation_ = s;
}
int Speaker::type() const {
    return 1;
}
Base* Speaker::clone() const {
    return new Speaker(*this);
}
void Speaker::input() {
    setFullName(readText("ФИО: "));
    setOrganization(readText("Организация / вуз: "));
    setReport(readText("Название доклада: "));
    setAnnotation(readText("Аннотация доклада: "));
}
void Speaker::print(std::ostream& out) const {
    out << "Выступающий | ФИО: " << fullName_
        << " | Организация: " << organization_ << " | Доклад: " << report_
        << " | Аннотация: " << annotation_;
}
void Speaker::save(std::ostream& out) const {
    writeString(out, fullName_);
    writeString(out, organization_);
    writeString(out, report_);
    writeString(out, annotation_);
}
void Speaker::load(std::istream& in) {
    setFullName(readString(in));
    setOrganization(readString(in));
    setReport(readString(in));
    setAnnotation(readString(in));
}
