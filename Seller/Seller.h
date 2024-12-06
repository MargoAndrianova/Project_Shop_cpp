#ifndef SELLER_H
#define SELLER_H

#include "D:\Project_Shop_cpp\Person\Person.h"

class Seller : public Person {
private:
    double salary;

public:
    Seller(const std::string& name, double initialSalary);
    void updateSalary(double profit);
    double getSalary() const;
};

#endif
