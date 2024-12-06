#include "Product.h"

Product::Product(const std::string& name, double price, int quantity, double cost)
    : name(name), price(price), quantity(quantity), cost(cost) {}

std::string Product::getName() const {
    return name;
}

double Product::getPrice() const {
    return price;
}

double Product::getCost() const {
    return cost;
}

int Product::getQuantity() const {
    return quantity;
}

void Product::reduceQuantity(int amount) {
    quantity -= amount;
}
