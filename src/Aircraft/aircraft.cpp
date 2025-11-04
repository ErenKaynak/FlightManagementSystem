#include "../include/Aircraft.h"
#include <iostream>

void Aircraft::display() const {
    cout << "Aircraft ID: " << aircraftId 
         << ", Model: " << model 
         << ", Capacity: " << capacity << endl;
}
