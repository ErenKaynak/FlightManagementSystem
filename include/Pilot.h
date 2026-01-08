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

    
    std::string getLicenseNumber() const;

    
    void setLicenseNumber(std::string license);
};

