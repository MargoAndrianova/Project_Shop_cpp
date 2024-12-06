#include "Store.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>

// Конструктор
Store::Store() : totalProfit(0.0) {
    randomEngine.seed(std::chrono::system_clock::now().time_since_epoch().count());
}

// Показ товарів
void Store::displayProducts() const {
    if (products.empty()) {
        std::cout << "No products in the store.\n";
        return;
    }

    std::cout << "\nProducts in store:\n";
    std::cout << std::left << std::setw(20) << "Name"
              << std::setw(10) << "Price"
              << std::setw(10) << "Cost"
              << std::setw(10) << "Quantity" << "\n";

    for (const auto& product : products) {
        std::cout << std::left << std::setw(20) << product.getName()
                  << std::setw(10) << product.getPrice()
                  << std::setw(10) << product.getCost()
                  << std::setw(10) << product.getQuantity() << "\n";
    }
}

// Показ продавців
void Store::displaySellers() const {
    if (sellers.empty()) {
        std::cout << "No sellers in the store.\n";
        return;
    }

    std::cout << "\nSellers in store:\n";
    std::cout << std::left << std::setw(20) << "Name"
              << std::setw(10) << "Salary" << "\n";

    for (const auto& seller : sellers) {
        std::cout << std::left << std::setw(20) << seller.getName()
                  << std::setw(10) << seller.getSalary() << "\n";
    }
}

// Показ загального прибутку
void Store::displayProfit() const {
    std::cout << "\nTotal Profit: $" << totalProfit << "\n";
}

// Додавання товару
void Store::addProduct(const Product& product) {
    products.push_back(product);
}

// Додавання продавця
void Store::addSeller(const Seller& seller) {
    sellers.push_back(seller);
}

// Продаж товару
void Store::sellProduct(const std::string& productName, int quantity, Seller& seller, Customer& customer) {
    for (auto& product : products) {
        if (product.getName() == productName && product.getQuantity() >= quantity) {
            double sellingPrice = product.getPrice() * quantity;
            double discount = customer.getDiscount();

            if (discount > 0) {
                sellingPrice *= (1 - discount); // Застосування знижки
                std::cout << "Customer '" << customer.getName() << "' received a discount of " << discount * 100 << "%.\n";
            }

            double costPrice = product.getCost() * quantity; // Собівартість товару
            double profit = sellingPrice - costPrice;        // Прибуток за продаж
            totalProfit += profit;                           // Додаємо до загального прибутку

            product.reduceQuantity(quantity);
            seller.updateSalary(sellingPrice);              // Оновлюємо зарплату продавця
            customer.updateLastPurchaseTime();              // Оновлюємо час останньої покупки

            std::cout << "Customer '" << customer.getName() << "' bought " << quantity
                      << " of '" << product.getName() << "' for $" << sellingPrice
                      << " (Profit: $" << profit << ").\n";
            return;
        }
    }

    std::cout << "Product '" << productName << "' is not available or insufficient quantity.\n";
}

// Симуляція покупки
void Store::simulatePurchase(const std::vector<Customer>& customers) {
    if (products.empty() || sellers.empty() || customers.empty()) {
        std::cout << "Cannot simulate purchase: products, sellers, or customers are empty.\n";
        return;
    }

    std::uniform_int_distribution<size_t> productDist(0, products.size() - 1);
    std::uniform_int_distribution<size_t> sellerDist(0, sellers.size() - 1);
    std::uniform_int_distribution<size_t> customerDist(0, customers.size() - 1);

    size_t productIndex = productDist(randomEngine);
    size_t sellerIndex = sellerDist(randomEngine);
    size_t customerIndex = customerDist(randomEngine);

    Product& selectedProduct = products[productIndex];
    Seller& selectedSeller = sellers[sellerIndex];
    Customer& selectedCustomer = const_cast<Customer&>(customers[customerIndex]);

    if (selectedProduct.getQuantity() == 0) {
        std::cout << "Product '" << selectedProduct.getName() << "' is out of stock.\n";
        return;
    }

    std::uniform_int_distribution<int> quantityDist(1, selectedProduct.getQuantity());
    int quantityToBuy = quantityDist(randomEngine);

    sellProduct(selectedProduct.getName(), quantityToBuy, selectedSeller, selectedCustomer);
}

// Симуляція поповнення складу
void Store::simulateRestock() {
    if (products.empty()) {
        std::cout << "No products to restock.\n";
        return;
    }

    std::uniform_int_distribution<size_t> productDist(0, products.size() - 1);
    std::uniform_int_distribution<int> restockDist(5, 20); // Поповнення від 5 до 20 одиниць

    size_t productIndex = productDist(randomEngine);
    int restockAmount = restockDist(randomEngine);

    products[productIndex].reduceQuantity(-restockAmount); // Додаємо кількість

    std::cout << "Restocked " << restockAmount << " units of '" << products[productIndex].getName() << "'.\n";
}

// Оновлення товару
bool Store::updateProduct(const std::string& name, double newPrice, int newQuantity) {
    for (auto& product : products) {
        if (product.getName() == name) {
            product = Product(name, newPrice, newQuantity, product.getCost());
            return true;
        }
    }
    return false; // Товар не знайдено
}

// Видалення товару
bool Store::removeProduct(const std::string& name) {
    auto it = std::remove_if(products.begin(), products.end(), [&name](const Product& product) {
        return product.getName() == name;
    });
    if (it != products.end()) {
        products.erase(it, products.end());
        return true;
    }
    return false; // Товар не знайдено
}

// Оновлення продавця
bool Store::updateSeller(const std::string& name, double newSalary) {
    for (auto& seller : sellers) {
        if (seller.getName() == name) {
            seller = Seller(name, newSalary);
            return true;
        }
    }
    return false; // Продавець не знайдений
}

// Видалення продавця
bool Store::removeSeller(const std::string& name) {
    auto it = std::remove_if(sellers.begin(), sellers.end(), [&name](const Seller& seller) {
        return seller.getName() == name;
    });
    if (it != sellers.end()) {
        sellers.erase(it, sellers.end());
        return true;
    }
    return false; // Продавець не знайдений
}

// Закупівля товару
void Store::restockProduct(const std::string& name, int quantity, double cost) {
    if (quantity <= 0 || cost <= 0) {
        std::cout << "Invalid quantity or cost for restocking.\n";
        return;
    }

    for (auto& product : products) {
        if (product.getName() == name) {
            product.reduceQuantity(-quantity); // Збільшуємо кількість товару
            std::cout << "Restocked " << quantity << " units of '" << name << "'.\n";
            return;
        }
    }

    // Якщо товару немає, додаємо новий
    products.emplace_back(name, cost * 1.2, quantity, cost); // Ціна = собівартість * 1.2
    std::cout << "Added new product: " << name << " (Quantity: " << quantity << ", Cost: $" << cost << ").\n";
}

// Збереження даних у файл
void Store::saveToFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Unable to open file for writing.");
    }

    size_t productCount = products.size();
    file.write(reinterpret_cast<const char*>(&productCount), sizeof(productCount));
    for (const auto& product : products) {
        size_t nameLength = product.getName().size();
        file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        file.write(product.getName().c_str(), nameLength);
        double price = product.getPrice();
        double cost = product.getCost();
        int quantity = product.getQuantity();
        file.write(reinterpret_cast<const char*>(&price), sizeof(price));
        file.write(reinterpret_cast<const char*>(&cost), sizeof(cost));
        file.write(reinterpret_cast<const char*>(&quantity), sizeof(quantity));
    }

    size_t sellerCount = sellers.size();
    file.write(reinterpret_cast<const char*>(&sellerCount), sizeof(sellerCount));
    for (const auto& seller : sellers) {
        size_t nameLength = seller.getName().size();
        file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        file.write(seller.getName().c_str(), nameLength);
        double salary = seller.getSalary();
        file.write(reinterpret_cast<const char*>(&salary), sizeof(salary));
    }

    file.close();
}

// Завантаження даних із файлу
void Store::loadFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Unable to open file for reading.");
    }

    size_t productCount;
    file.read(reinterpret_cast<char*>(&productCount), sizeof(productCount));
    products.clear();
    for (size_t i = 0; i < productCount; ++i) {
        size_t nameLength;
        file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        std::string name(nameLength, '\0');
        file.read(&name[0], nameLength);
        double price, cost;
        int quantity;
        file.read(reinterpret_cast<char*>(&price), sizeof(price));
        file.read(reinterpret_cast<char*>(&cost), sizeof(cost));
        file.read(reinterpret_cast<char*>(&quantity), sizeof(quantity));
        products.emplace_back(name, price, quantity, cost);
    }

    size_t sellerCount;
    file.read(reinterpret_cast<char*>(&sellerCount), sizeof(sellerCount));
    sellers.clear();
    for (size_t i = 0; i < sellerCount; ++i) {
        size_t nameLength;
        file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        std::string name(nameLength, '\0');
        file.read(&name[0], nameLength);
        double salary;
        file.read(reinterpret_cast<char*>(&salary), sizeof(salary));
        sellers.emplace_back(name, salary);
    }

    file.close();
}

std::vector<Product> Store::getProducts() const {
    return products;
}

// Повернення загального прибутку
double Store::getTotalProfit() const {
    return totalProfit;
}

std::vector<Seller> Store::getSellers() const {
    return sellers;
}