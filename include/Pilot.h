#pragma once
#include <string>
using namespace std;

class Pilot {
private:
    string pilotId;
    string name;
    string licenseNumber;

public:
    Pilot(string id="", string n="", string license="") 
        : pilotId(id), name(n), licenseNumber(license) {}

    void display() const;

    // Getters
    string getPilotId() const { return pilotId; }
    string getName() const { return name; }
    string getLicenseNumber() const { return licenseNumber; }

    // Setters
    void setPilotId(string id) { pilotId = id; }
    void setName(string n) { name = n; }
    void setLicenseNumber(string license) { licenseNumber = license; }
};

