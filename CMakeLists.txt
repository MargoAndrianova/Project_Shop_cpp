cmake_minimum_required(VERSION 3.29)
project(Project_Shop_cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(Project_Shop_cpp main.cpp
        Customer/Customer.cpp
        Customer/Customer.h
        Manager/Manager.cpp
        Manager/Manager.h
        Person/Person.cpp
        Person/Person.h
        Product/Product.cpp
        Product/Product.h
        Seller/Seller.cpp
        Seller/Seller.h
        Store/Store.cpp
        Store/Store.h)
