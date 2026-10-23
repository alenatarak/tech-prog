#include <windows.h>
#include <clocale>
#include <iostream>
#include <memory>
#include <stdexcept>
#include "Administrator.h"
#include "Keeper.h"
#include "ProgramItem.h"
#include "Speaker.h"
#include "Utils.h"

std::unique_ptr<Conference> makeObject(int type) {
    switch (type) {
        case 1:
            return std::unique_ptr<Conference>(new Speaker());
        case 2:
            return std::unique_ptr<Conference>(new Administrator());
        case 3:
            return std::unique_ptr<Conference>(new ProgramItem());
        default:
            throw std::invalid_argument("Неизвестный тип объекта");
    }
}
void printMenu() {
    std::cout << "\nМЕНЮ ПРОГРАММЫ\n"
              << "1. Добавить выступающего\n"
              << "2. Добавить администратора\n"
              << "3. Добавить пункт программы\n"
              << "4. Показать все объекты\n"
              << "5. Показать объекты выбранного типа\n"
              << "6. Показать один объект\n"
              << "7. Изменить объект\n"
              << "8. Удалить объект\n"
              << "9. Сохранить в файл\n"
              << "10. Загрузить из файла (заменяет текущие данные)\n"
              << "11. Скопировать объект\n"
              << "12. Очистить конференцию\n"
              << "0. Выход\n";
}
int chooseIndex(const Keeper& keeper) {
    if (keeper.size() == 0)
        throw std::runtime_error("Список конференции пуст");
    keeper.printAll();
    return readInt("Номер объекта: ", 1, keeper.size()) - 1;
}
int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::setlocale(LC_ALL, ".UTF-8");

    Keeper conference;
    std::cout << "Введите данные на русском языке.\n";
    for (;;) {
        try {
            printMenu();
            int option = readInt("Выберите действие: ", 0, 12);
            if (option == 0)
                break;
            if (option >= 1 && option <= 3) {
                auto object = makeObject(option);
                object->input();
                conference.add(*object);
                std::cout << "Объект добавлен.\n";
            } else if (option == 4)
                conference.printAll();
            else if (option == 5) {
                int type = readInt(
                    "Тип (1 — выступающий, 2 — администрация, 3 — программа): ",
                    1, 3);
                bool found = false;
                for (int i = 0; i < conference.size(); ++i) {
                    if (conference.at(i).type() == type) {
                        std::cout << i + 1 << ". ";
                        conference.at(i).print(std::cout);
                        std::cout << '\n';
                        found = true;
                    }
                }
                if (!found)
                    std::cout << "Объекты выбранного типа не найдены.\n";
            } else if (option == 6) {
                int i = chooseIndex(conference);
                conference.at(i).print(std::cout);
                std::cout << '\n';
            } else if (option == 7) {
                int i = chooseIndex(conference);

                auto edited = std::unique_ptr<Conference>(conference.at(i).clone());
                edited->input();

                switch (edited->type()) {
                    case 1:
                        dynamic_cast<Speaker&>(conference.at(i)) =
                            dynamic_cast<const Speaker&>(*edited);
                        break;
                    case 2:
                        dynamic_cast<Administrator&>(conference.at(i)) =
                            dynamic_cast<const Administrator&>(*edited);
                        break;
                    case 3:
                        dynamic_cast<ProgramItem&>(conference.at(i)) =
                            dynamic_cast<const ProgramItem&>(*edited);
                        break;
                }
                std::cout << "Объект изменён.\n";
            } else if (option == 8) {
                conference.remove(chooseIndex(conference));
                std::cout << "Объект удалён.\n";
            } else if (option == 9) {
                auto name = readText("Путь к файлу для сохранения: ");
                conference.save(name);
                std::cout << "Данные успешно сохранены.\n";
            } else if (option == 10) {
                auto name = readText("Путь к файлу для загрузки: ");
                conference.load(name);
                std::cout << "Данные успешно загружены.\n";
            } else if (option == 11) {
                conference.add(conference.at(chooseIndex(conference)));
                std::cout << "Объект скопирован.\n";
            } else if (option == 12) {
                conference.clear();
                std::cout << "Данные конференции очищены.\n";
            }
        } catch (const std::exception& ex) {
            std::cerr << "Ошибка: " << ex.what() << '\n';
            if (!std::cin)
                break;
        }
    }
    return 0;
}
