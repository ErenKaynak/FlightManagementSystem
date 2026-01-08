#include "Person.h"
#include <iostream>


int Person::totalPeople = 0;

Person::Person(std::string id, std::string name) : id(id), name(name) {
    totalPeople++; 
}

Person::~Person() {
    totalPeople--; 
}

std::string Person::getId() const {
    return id;
}

std::string Person::getName() const {
    return name;
}

void Person::setId(std::string id) {
    this->id = id;
}

void Person::setName(std::string name) {
    this->name = name;
}

void Person::display() const {
    std::cout << "ID: " << id << ", Name: " << name << std::endl;
}
