//Андріанова Маргарита Юріївна
//Комп'ютерна математика 2

#include "Customer.h"

Customer::Customer(const std::string& name, bool regular, double initialDiscount)
    : Person(name), isRegularCustomer(regular), discount(initialDiscount) {
    lastPurchaseTime = std::chrono::system_clock::now();
}

double Customer::getDiscount() {
    auto now = std::chrono::system_clock::now();
    auto timeSinceLastPurchase = std::chrono::duration_cast<std::chrono::hours>(now - lastPurchaseTime).count();

    // Якщо минуло більше ніж 24 години, знижка зменшується
    if (timeSinceLastPurchase >= 24 && isRegularCustomer) {
        reduceDiscount(0.01); // Знижка зменшується на 1% кожні 24 години
        lastPurchaseTime = now;
    }

    return discount;
}

void Customer::updateLastPurchaseTime() {
    lastPurchaseTime = std::chrono::system_clock::now();
}

void Customer::reduceDiscount(double reductionRate) {
    discount = std::max(0.0, discount - reductionRate); // Знижка не може бути меншою за 0
}