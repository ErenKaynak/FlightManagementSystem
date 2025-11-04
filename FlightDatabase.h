#include "FlightDatabase.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// Initialize static instance
FlightDatabase* FlightDatabase::instance = nullptr;

// Private constructor
FlightDatabase::FlightDatabase() {
    loadDataFromFile();
}

// Singleton getInstance
FlightDatabase* FlightDatabase::getInstance() {
    if (instance == nullptr) {
        instance = new FlightDatabase();
    }
    return instance;
}

// Flight management methods
void FlightDatabase::addFlight(const Flight& flight) {
    allFlights.push_back(flight);
    cout << "Flight added successfully!" << endl;
}

bool FlightDatabase::removeFlight(const string& flightNumber) {
    auto it = find_if(allFlights.begin(), allFlights.end(),
        [&flightNumber](const Flight& f) { return f.getFlightNumber() == flightNumber; });
    
    if (it != allFlights.end()) {
        allFlights.erase(it);
        cout << "Flight removed successfully!" << endl;
        return true;
    }
    cout << "Flight not found!" << endl;
    return false;
}

Flight* FlightDatabase::findFlightByID(const string& flightNumber) {
    for (auto& flight : allFlights) {
        if (flight.getFlightNumber() == flightNumber) {
            return &flight;
        }
    }
    return nullptr;
}

vector<Flight*> FlightDatabase::searchFlights(const string& origin, const string& destination) {
    vector<Flight*> results;
    for (auto& flight : allFlights) {
        if (flight.getOrigin() == origin && flight.getDestination() == destination) {
            results.push_back(&flight);
        }
    }
    return results;
}

void FlightDatabase::displayAllFlights() {
    if (allFlights.empty()) {
        cout << "No flights available." << endl;
        return;
    }
    cout << "\n========== ALL FLIGHTS ==========" << endl;
    for (const auto& flight : allFlights) {
        flight.displayDetails();
    }
}

// Booking management methods
void FlightDatabase::addBooking(const Booking& booking) {
    allBookings.push_back(booking);
}

Booking* FlightDatabase::findBookingByID(int bookingID) {
    for (auto& booking : allBookings) {
        if (booking.getBookingID() == bookingID) {
            return &booking;
        }
    }
    return nullptr;
}

vector<Booking*> FlightDatabase::findBookingsByPassengerName(const string& firstName, const string& lastName) {
    vector<Booking*> results;
    for (auto& booking : allBookings) {
        if (booking.getPassenger().getFirstName() == firstName && 
            booking.getPassenger().getLastName() == lastName &&
            booking.getBookingStatus() != "Cancelled") {
            results.push_back(&booking);
        }
    }
    return results;
}

void FlightDatabase::displayAllBookings() {
    if (allBookings.empty()) {
        cout << "No bookings found." << endl;
        return;
    }
    cout << "\n========== ALL BOOKINGS ==========" << endl;
    for (const auto& booking : allBookings) {
        booking.displayBookingDetails();
    }
}

int FlightDatabase::generateBookingID() {
    return rand() % 90000 + 10000;
}

// File operations
void FlightDatabase::saveDataToFile() {
    ofstream flightsFile("flights.txt");
    for (const auto& flight : allFlights) {
        flightsFile << flight.toFileString() << endl;
    }
    flightsFile.close();

    ofstream bookingsFile("bookings.txt");
    for (const auto& booking : allBookings) {
        bookingsFile << booking.toFileString() << endl;
    }
    bookingsFile.close();
}

void FlightDatabase::loadDataFromFile() {
    ifstream flightsFile("flights.txt");
    if (flightsFile.is_open()) {
        string line;
        while (getline(flightsFile, line)) {
            if (!line.empty()) {
                allFlights.push_back(Flight::fromFileString(line));
            }
        }
        flightsFile.close();
    }

    ifstream bookingsFile("bookings.txt");
    if (bookingsFile.is_open()) {
        string line;
        while (getline(bookingsFile, line)) {
            if (!line.empty()) {
                allBookings.push_back(Booking::fromFileString(line));
            }
        }
        bookingsFile.close();
    }
}