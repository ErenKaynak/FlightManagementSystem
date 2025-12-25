#include "../include/Admin.h"
#include <iostream>
using namespace std;

// Flight Management Functions

void Admin::addFlight() {
    string flightId = generateFlightId();
    string origin, destination, date;
    double price = 0.0;
    int duration = 0;

    cout << "\n--- Add New Flight ---\n";
    cout << "Generated Flight ID: " << flightId << endl;
    cout << "Enter origin: ";
    getline(cin, origin);
    cout << "Enter destination: ";
    getline(cin, destination);
    cout << "Enter date (YYYY-MM-DD): ";
    getline(cin, date);

    if (!isDateValid(date)) {
        cout << "Invalid date format. Please use YYYY-MM-DD format.\n";
        return;
    }

    if (isDateExpired(date)) {
        cout << "Error: Cannot add flight with expired date. Please enter a future date.\n";
        return;
    }
    
    // PHASE 2: Get price and duration for algorithmic problems
    cout << "Enter flight price (in USD): $";
    cin >> price;
    cin.ignore();
    
    cout << "Enter flight duration (in minutes): ";
    cin >> duration;
    cin.ignore();

    Flight flight(flightId, origin, destination, date, "", "", "", Aircraft(), price, duration);
    flights.push_back(flight);
    saveFlightsToFile();
    
    cout << "Flight added successfully!\n";
    cout << "Total flights in system: " << Flight::getTotalFlights() << endl;
}

void Admin::removeFlight() {
    int choice;
    cout << "\n--- Remove Flight ---\n";
    
    if (flights.empty()) {
        cout << "No flights available.\n";
        return;
    }

    cout << "\n--- Available Flights ---\n";
    for (size_t i = 0; i < flights.size(); i++) {
        cout << (i + 1) << ". ";
        flights[i].display();
    }
    cout << "Select flight number to remove: ";
    cin >> choice;
    cin.ignore(); // Clear newline

    if (choice < 1 || choice > static_cast<int>(flights.size())) {
        cout << "Invalid flight selection!\n";
        return;
    }

    flights.erase(flights.begin() + choice - 1);
    saveFlightsToFile();
    cout << "Flight removed successfully!\n";
}

string Admin::createFlightId() {
    string id = generateFlightId();
    cout << "Generated Flight ID: " << id << endl;
    return id;
}

void Admin::viewAllFlights() {
    cout << "\n--- All Flights ---\n";
    if (flights.empty()) {
        cout << "No flights found.\n";
        return;
    }
    for (const auto& flight : flights) {
        flight.display();
    }
}



