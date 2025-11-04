#include "../include/Pilot.h"
#include <iostream>

void Pilot::display() const {
    cout << "Pilot ID: " << pilotId 
         << ", Name: " << name 
         << ", License: " << licenseNumber << endl;
}

