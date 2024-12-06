//Андріанова Маргарита Юріївна
//Комп'ютерна математика 2

#include "Person.h"

Person::Person(const std::string& name) : name(name) {}

std::string Person::getName() const {
    return name;
}
