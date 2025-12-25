#include "../include/Flight.h"
#include <iostream>
#include <iomanip>

// REQUIREMENT: Static Variable - Initialize static member
int Flight::totalFlights = 0;

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
    if (price > 0) {
        cout << ", Price: $" << fixed << setprecision(2) << price;
    }
    if (durationMinutes > 0) {
        cout << ", Duration: " << durationMinutes << " mins";
    }
    cout << endl;
}

// REQUIREMENT: Friend Function - Stream output operator implementation
ostream& operator<<(ostream& os, const Flight& flight) {
    os << "Flight[ID: " << flight.flightId 
       << ", Route: " << flight.origin << " -> " << flight.destination
       << ", Date: " << flight.date;
    
    if (!flight.departureTime.empty()) {
        os << ", Departure: " << flight.departureTime;
    }
    if (!flight.arrivalTime.empty()) {
        os << ", Arrival: " << flight.arrivalTime;
    }
    if (flight.price > 0) {
        os << ", Price: $" << fixed << setprecision(2) << flight.price;
    }
    if (flight.durationMinutes > 0) {
        os << ", Duration: " << flight.durationMinutes << " mins";
    }
    os << "]";
    return os;
}

// REQUIREMENT: Friend Function - Utility function to compare two flights
void compareFlights(const Flight& f1, const Flight& f2) {
    cout << "\n=== Flight Comparison ===" << endl;
    cout << "Flight 1: " << f1 << endl;
    cout << "Flight 2: " << f2 << endl;
    cout << "\nComparison Results:" << endl;
    
    if (f1 == f2) {
        cout << "- These are the same flight (same ID)" << endl;
    } else {
        cout << "- These are different flights" << endl;
    }
    
    if (f1.price > 0 && f2.price > 0) {
        if (f1.price < f2.price) {
            cout << "- Flight 1 is cheaper by $" << fixed << setprecision(2) 
                 << (f2.price - f1.price) << endl;
        } else if (f1.price > f2.price) {
            cout << "- Flight 2 is cheaper by $" << fixed << setprecision(2) 
                 << (f1.price - f2.price) << endl;
        } else {
            cout << "- Both flights have the same price" << endl;
        }
    }
    
    if (f1.durationMinutes > 0 && f2.durationMinutes > 0) {
        if (f1.durationMinutes < f2.durationMinutes) {
            cout << "- Flight 1 is faster by " << (f2.durationMinutes - f1.durationMinutes) 
                 << " minutes" << endl;
        } else if (f1.durationMinutes > f2.durationMinutes) {
            cout << "- Flight 2 is faster by " << (f1.durationMinutes - f2.durationMinutes) 
                 << " minutes" << endl;
        } else {
            cout << "- Both flights have the same duration" << endl;
        }
    }
    cout << "========================\n" << endl;
}
