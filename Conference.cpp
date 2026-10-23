#include "Conference.h"
#include <iostream>
Conference::Conference() {
    std::cout << "[Класс Конференция] конструктор без параметров\n";
}
Conference::Conference(const Conference&) {
    std::cout << "[Класс Конференция] конструктор копирования\n";
}
Conference& Conference::operator=(const Conference&) {
    return *this;
}
Conference::~Conference() {
    std::cout << "[Класс Конференция] деструктор\n";
}
