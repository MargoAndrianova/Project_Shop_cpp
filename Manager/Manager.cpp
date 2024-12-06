//Андріанова Маргарита Юріївна
//Комп'ютерна математика 2

#include "Manager.h"

Manager::Manager(const std::string& name) : Person(name) {}

void Manager::addSeller(const Seller& seller) {
    sellers.push_back(seller);
}

std::vector<Seller> Manager::getSellers() const {
    return sellers;
}
