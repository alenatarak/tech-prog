#include "Base.h"
#include <iostream>
Base::Base() {
    std::cout << "[Базовый класс] конструктор без параметров\n";
}
Base::Base(const Base&) {
    std::cout << "[Базовый класс] конструктор копирования\n";
}
Base& Base::operator=(const Base&) {
    return *this;
}
Base::~Base() {
    std::cout << "[Базовый класс] деструктор\n";
}
