#include "../include/Flight.h"
#include <iostream>

void Flight::display() const {
    cout << "Flight ID: " << flightId
         << ", Origin: " << origin
         << ", Destination: " << destination
         << ", Date: " << date;
    if (!departureTime.empty()) {
        cout << ", Departure: " << departureTime;
    }
    if (!arrivalTime.empty()) {
        cout << ", Arrival: " << arrivalTime;
    }
    cout << ", Aircraft: " << aircraft.getModel() << " (" << aircraft.getAircraftId() << ")";
    if (!pilotId.empty()) {
        cout << ", Pilot ID: " << pilotId;
    }
    cout << endl;
}
