#pragma once
#include "Person.h"
#include <string>

class Pilot : public Person {
private:
    std::string licenseNumber;

public:
    using Person::display;
    Pilot(std::string id = "", std::string n = "", std::string license = "");

    void display(bool detailed = true) const;

    // Getter
    std::string getLicenseNumber() const;

    // Setter
    void setLicenseNumber(std::string license);
};

