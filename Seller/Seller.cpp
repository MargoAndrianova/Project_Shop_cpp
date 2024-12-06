#include "Seller.h"

Seller::Seller(const std::string& name, double initialSalary)
    : Person(name), salary(initialSalary) {}

void Seller::updateSalary(double profit) {
    salary += profit * 0.1; // 10% від прибутку
}

double Seller::getSalary() const {
    return salary;
}