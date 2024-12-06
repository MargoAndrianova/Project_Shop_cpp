//Андріанова Маргарита Юріївна
//Комп'ютерна математика 2

#ifndef STORE_H
#define STORE_H

#include <vector>
#include <string>
#include "D:\Project_Shop_cpp\Product\Product.h"
#include "D:\Project_Shop_cpp\Seller\Seller.h"
#include "D:\Project_Shop_cpp\Customer\Customer.h"
#include <random>

class Store {
private:
    std::vector<Product> products;   // Список товарів
    std::vector<Seller> sellers;    // Список продавців
    double totalProfit;             // Загальний прибуток магазину

    std::default_random_engine randomEngine; // Генератор випадкових чисел

public:
    Store();

    void addProduct(const Product& product);
    void addSeller(const Seller& seller);

    void sellProduct(const std::string& productName, int quantity, Seller& seller, Customer& customer);
    void simulatePurchase(const std::vector<Customer>& customers);
    void simulateRestock();

    void restockProduct(const std::string& name, int quantity, double cost); // Закупівля товару

    bool updateProduct(const std::string& name, double newPrice, int newQuantity);
    bool removeProduct(const std::string& name);

    bool updateSeller(const std::string& name, double newSalary);
    bool removeSeller(const std::string& name);

    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);

    std::vector<Product> getProducts() const;
    std::vector<Seller> getSellers() const;

    double getTotalProfit() const;

    void displayProducts() const;
    void displaySellers() const;
    void displayProfit() const;
};

#endif