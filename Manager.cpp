#include "Authentication.h"
#include "Catalog.h"
#include <iostream>
#include <limits>
#include <string>


void showMenu() {
    setlocale(LC_ALL, "Russian");
    std::cout << "\n=== Меню управления каталогом товаров ===\n";
    std::cout << "1. Показать каталог товаров\n";
    std::cout << "2. Добавить товар в каталог\n";
    std::cout << "3. Найти товар по названию\n";
    std::cout << "4. Сортировать товары по цене\n";
    std::cout << "5. Сохранить каталог в файл\n";
    std::cout << "6. Загрузить каталог из файла\n";
    std::cout << "7. Удалить товар по ID\n";
    std::cout << "0. Выход\n";
    std::cout << "Выберите действие: ";
}

void addProductToCatalog(Catalog& catalog) {
    int id, quantity;
    std::string name, category;
    double price;

    std::cout << "Введите ID товара: ";
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера

    std::cout << "Введите название товара: ";
    std::getline(std::cin, name);

    std::cout << "Введите категорию товара: ";
    std::getline(std::cin, category);

    std::cout << "Введите цену товара: ";
    std::cin >> price;

    std::cout << "Введите количество товара на складе: ";
    std::cin >> quantity;

    catalog.addProduct(Product(id, name, category, price, quantity));
    std::cout << "Товар добавлен в каталог.\n";
}

void printCatalog(const Catalog& catalog) {

    for (const auto& product : catalog.getProducts()) {
        std::cout << "ID: " << product.getId() << ", "
            << "Название: " << product.getName() << ", "
            << "Категория: " << product.getCategory() << ", "
            << "Цена: " << product.getPrice() << ", "
            << "Количество: " << product.getQuantity() << std::endl;
    }
}



int main() {
    setlocale(LC_ALL, "Russian");
    Authentication authSystem;
    Catalog catalog;
    // Предполагается, что каталог загружается из файла
    catalog.loadFromFile("catalog.txt");

    std::string username, password;
    bool isAuthenticated = false;

    while (!isAuthenticated) {
        std::cout << "Имя пользователя: ";
        std::cin >> username;
        std::cout << "Пароль: ";
        std::cin >> password;

        if (authSystem.login(username, password)) {
            isAuthenticated = true; // Пользователь успешно аутентифицирован
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорирование оставшегося ввода
            std::cout << "Чтобы вести данные снова нажмите 'Enter'. Для выхода введите 'exit'";
            std::string decision;
            std::getline(std::cin, decision);
            if (decision == "exit") {
                return 0; // Выход из программы
            }
        }
    }

    // После успешной аутентификации показываем меню
    int choice = -1;
    while (choice != 0) {
        showMenu();
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear(); // Очистка флага ошибки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорирование лишнего ввода
            continue; // Продолжение цикла
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода

        switch (choice) {
        case 1:
            printCatalog(catalog); // Показать каталог товаров
            break;
        case 2:
            addProductToCatalog(catalog); // Добавить товар в каталог
            break;
        case 3: {
            std::string searchName;
            std::cout << "Введите название товара для поиска: ";
            std::getline(std::cin, searchName);
            auto foundProducts = catalog.findByName(searchName);
            if (!foundProducts.empty()) {
                for (const auto& product : foundProducts) {
                    std::cout << "ID: " << product.getId() << ", Название: " << product.getName()
                        << ", Категория: " << product.getCategory() << ", Цена: "
                        << product.getPrice() << ", Количество: " << product.getQuantity() << std::endl;
                }
            }
            else {
                std::cout << "Товар с названием \"" << searchName << "\" не найден.\n";
            }
            break;
        }
        case 4: {
            catalog.sortByPrice();
            std::cout << "Товары отсортированы по цене.\n";
            printCatalog(catalog); // Предполагается, что эта функция выводит отсортированный каталог
            break;
        }
        case 5:
            catalog.saveToFile("catalog.txt"); // Сохранить каталог в файл
            std::cout << "Каталог сохранен.\n";
            break;
        case 6:
            catalog.loadFromFile("catalog.txt"); // Загрузить каталог из файла
            std::cout << "Каталог загружен.\n";
            break;
        case 7:
            // Удалить товар по ID

            int idToRemove;
            std::cout << "Введите ID товара для удаления: ";
            std::cin >> idToRemove;
            catalog.removeProductById(idToRemove);
            
            break;
        case 0:
            std::cout << "Выход из программы...\n";
            break;
        default:
            std::cout << "Некорректный ввод. Пожалуйста, попробуйте снова.\n";
            break;
        }
    }

    return 0;
}
