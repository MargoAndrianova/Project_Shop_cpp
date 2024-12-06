//Андріанова Маргарита Юріївна
//Комп'ютерна математика 2

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "D:\Project_Shop_cpp\Person\Person.h"
#include <chrono>

class Customer : public Person {
private:
    bool isRegularCustomer;
    double discount; // Поточна знижка
    std::chrono::time_point<std::chrono::system_clock> lastPurchaseTime;

public:
    Customer(const std::string& name, bool regular, double initialDiscount = 0.1);

    double getDiscount(); // Повертає актуальну знижку
    void updateLastPurchaseTime();
    void reduceDiscount(double reductionRate);
};

#endif