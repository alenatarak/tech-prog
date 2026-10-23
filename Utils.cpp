#include "Utils.h"
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

std::string readText(const std::string& label) {
    for (;;) {
        std::cout << label;
        std::string s;
        if (!std::getline(std::cin, s))
            throw std::runtime_error("Поток ввода закрыт");
        if (!s.empty())
            return s;
        std::cout << "Поле не может быть пустым.\n";
    }
}
int readInt(const std::string& label, int minValue, int maxValue) {
    for (;;) {
        std::string s = readText(label);
        std::istringstream ss(s);
        long long value;
        char extra;
        if ((ss >> value) && !(ss >> extra) && value >= minValue &&
            value <= maxValue)
            return static_cast<int>(value);
        std::cout << "Введите целое число от " << minValue << " до " << maxValue
                  << ".\n";
    }
}
void verifyStream(std::istream& in) {
    if (!in)
        throw std::runtime_error("Некорректный или повреждённый файл");
}
void writeString(std::ostream& out, const std::string& s) {
    out << std::quoted(s) << '\n';
    if (!out)
        throw std::runtime_error("Не удалось записать данные в файл");
}
std::string readString(std::istream& in) {
    std::string s;
    in >> std::quoted(s);
    verifyStream(in);
    if (s.empty())
        throw std::runtime_error("Некорректный файл: пустое текстовое поле");
    return s;
}
