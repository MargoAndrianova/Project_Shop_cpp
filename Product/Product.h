//Андріанова Маргарита Юріївна
//Комп'ютерна математика 2

#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    std::string name;
    double price;   // Ціна продажу
    double cost;    // Собівартість
    int quantity;

public:
    Product(const std::string& name, double price, int quantity, double cost);

    std::string getName() const;
    double getPrice() const;
    double getCost() const;
    int getQuantity() const;

    void reduceQuantity(int amount);
};

#endif