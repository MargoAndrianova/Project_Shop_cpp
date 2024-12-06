//Андріанова Маргарита Юріївна
//Комп'ютерна математика 2

#ifndef MANAGER_H
#define MANAGER_H

#include "D:\Project_Shop_cpp\Person\Person.h"
#include "D:\Project_Shop_cpp\Seller\Seller.h"
#include <vector>

class Manager : public Person {
private:
    std::vector<Seller> sellers;

public:
    Manager(const std::string& name);
    void addSeller(
        const Seller& seller);
    std::vector<Seller> getSellers() const;
};

#endif
