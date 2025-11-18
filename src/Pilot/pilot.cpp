#include "Pilot.h"
#include <iostream>

Pilot::Pilot(std::string id, std::string n, std::string license)
    : Person(id, n), licenseNumber(license) {}

void Pilot::display(bool detailed) const {
    if (detailed) {
        std::cout << "Pilot ID: " << getId() << ", Name: " << getName()
                  << ", License: " << licenseNumber << std::endl;
    } else {
        std::cout << "Pilot ID: " << getId() << ", Name: " << getName() << std::endl;
    }
}

std::string Pilot::getLicenseNumber() const {
    return licenseNumber;
}

void Pilot::setLicenseNumber(std::string license) {
    licenseNumber = license;
}

