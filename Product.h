#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    int id;
    std::string name;
    std::string category;
    double price;
    int quantity;

public:
    Product(int id, std::string name, std::string category, double price, int quantity)
        : id(id), name(std::move(name)), category(std::move(category)), price(price), quantity(quantity) {}

    int getId() const { return id; }
    const std::string& getName() const { return name; }
    const std::string& getCategory() const { return category; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

};

#endif // PRODUCT_H
