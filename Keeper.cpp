#include "Keeper.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include "Administrator.h"
#include "ProgramItem.h"
#include "Speaker.h"
#include "Utils.h"

Keeper::Keeper() : items_(nullptr), size_(0), capacity_(0) {
    std::cout << "[Хранилище] конструктор без параметров\n";
}
Keeper::Keeper(int capacity) : Keeper() {
    if (capacity < 0)
        throw std::invalid_argument("Отрицательная вместимость контейнера");
    reserve(capacity);
    std::cout << "[Хранилище] конструктор с параметрами\n";
}
void Keeper::reserve(int n) {
    if (n <= capacity_)
        return;
    Conference** next = new Conference* [n] {
    };
    for (int i = 0; i < size_; ++i)
        next[i] = items_[i];
    delete[] items_;
    items_ = next;
    capacity_ = n;
}
Keeper::Keeper(const Keeper& other) : Keeper() {
    try {
        for (int i = 0; i < other.size_; ++i)
            add(*other.items_[i]);
    } catch (...) {
        clear();
        delete[] items_;
        items_ = nullptr;
        throw;
    }
    std::cout << "[Хранилище] конструктор копирования\n";
}
void Keeper::swap(Keeper& other) noexcept {
    std::swap(items_, other.items_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}
Keeper& Keeper::operator=(const Keeper& other) {
    if (this != &other) {
        Keeper copy(other);
        swap(copy);
    }
    return *this;
}
Keeper::~Keeper() {
    clear();
    delete[] items_;
    std::cout << "[Хранилище] деструктор\n";
}
int Keeper::size() const {
    return size_;
}
void Keeper::add(const Conference& item) {
    if (size_ == capacity_)
        reserve(capacity_ == 0 ? 2 : capacity_ * 2);
    items_[size_] = item.clone();
    ++size_;
}
void Keeper::remove(int index) {
    if (index < 0 || index >= size_)
        throw std::out_of_range("Номер объекта вне допустимого диапазона");
    delete items_[index];
    for (int i = index; i < size_ - 1; ++i)
        items_[i] = items_[i + 1];
    items_[--size_] = nullptr;
}
Conference& Keeper::at(int index) {
    if (index < 0 || index >= size_)
        throw std::out_of_range("Номер объекта вне допустимого диапазона");
    return *items_[index];
}
const Conference& Keeper::at(int index) const {
    if (index < 0 || index >= size_)
        throw std::out_of_range("Номер объекта вне допустимого диапазона");
    return *items_[index];
}
void Keeper::clear() {
    for (int i = 0; i < size_; ++i) {
        delete items_[i];
        items_[i] = nullptr;
    }
    size_ = 0;
}
void Keeper::printAll() const {
    if (size_ == 0) {
        std::cout << "Список конференции пуст.\n";
        return;
    }
    for (int i = 0; i < size_; ++i) {
        std::cout << (i + 1) << ". ";
        items_[i]->print(std::cout);
        std::cout << '\n';
    }
}
void Keeper::save(const std::string& filename) const {
    std::ofstream out(filename, std::ios::binary | std::ios::trunc);
    if (!out)
        throw std::runtime_error("Не удалось открыть файл для записи: " +
                                 filename);
    out << "CONFERENCE_V1\n" << size_ << '\n';
    for (int i = 0; i < size_; ++i) {
        out << items_[i]->type() << '\n';
        items_[i]->save(out);
    }
    if (!out)
        throw std::runtime_error("Ошибка при сохранении конференции");
}
void Keeper::load(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in)
        throw std::runtime_error("Не удалось открыть файл для чтения: " +
                                 filename);
    std::string header;
    std::getline(in, header);
    if (header != "CONFERENCE_V1")
        throw std::runtime_error("Некорректный формат или версия файла");
    int count = -1;
    in >> count;
    if (!in || count < 0 || count > 100000)
        throw std::runtime_error("Некорректное количество объектов");
    Keeper temporary;
    for (int i = 0; i < count; ++i) {
        int type = 0;
        in >> type;
        verifyStream(in);
        std::unique_ptr<Conference> object;
        switch (type) {
            case 1:
                object.reset(new Speaker());
                break;
            case 2:
                object.reset(new Administrator());
                break;
            case 3:
                object.reset(new ProgramItem());
                break;
            default:
                throw std::runtime_error("Неизвестный тип объекта в файле");
        }
        object->load(in);
        temporary.add(*object);
    }
    
    in >> std::ws;
    if (!in.eof())
        throw std::runtime_error("Лишние данные в конце файла");
    swap(temporary);
}
