#include <iostream>
#include "D:\Project_Shop_cpp\Product\Product.h"
#include "D:\Project_Shop_cpp\Seller\Seller.h"
#include "D:\Project_Shop_cpp\Customer\Customer.h"
#include "D:\Project_Shop_cpp\Store\Store.h"

int main() {
    Store store;

    // Додавання початкових товарів
    store.addProduct(Product("Laptop", 1000.0, 10, 800.0));
    store.addProduct(Product("Phone", 500.0, 20, 400.0));

    // Показ початкового списку товарів
    store.displayProducts();

    // Закупівля товарів
    store.restockProduct("Laptop", 5, 850.0); // Збільшуємо кількість існуючого товару
    store.restockProduct("Headphones", 15, 50.0); // Додаємо новий товар

    // Показ оновленого списку товарів
    store.displayProducts();

    return 0;
}