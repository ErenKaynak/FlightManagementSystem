#include "../include/Admin.h"
#include <iostream>
#include <vector>
using namespace std;

// Aircraft Management Functions

void Admin::assignAircraftToFlight() {
    int flightChoice, aircraftChoice;
    cout << "\n--- Assign Aircraft to Flight ---\n";
    
    if (flights.empty()) {
        cout << "No flights available. Please add flights first.\n";
        return;
    }

    if (aircrafts.empty()) {
        cout << "No aircrafts available. Please add aircrafts first.\n";
        return;
    }

    cout << "\n--- Available Flights ---\n";
    for (size_t i = 0; i < flights.size(); i++) {
        cout << (i + 1) << ". ";
        flights[i].display();
    }
    cout << "Select flight number: ";
    cin >> flightChoice;
    cin.ignore(); // Clear newline

    if (flightChoice < 1 || flightChoice > static_cast<int>(flights.size())) {
        cout << "Invalid flight selection!\n";
        return;
    }

    int flightIdx = flightChoice - 1;
    Flight& selectedFlight = flights[flightIdx];
    
    // Check if flight date is expired
    if (isDateExpired(selectedFlight.getDate())) {
        cout << "Error: Cannot assign aircraft to an expired flight.\n";
        return;
    }

    cout << "\n--- Available Aircrafts ---\n";
    vector<int> availableAircrafts;
    for (size_t i = 0; i < aircrafts.size(); i++) {
        if (isAircraftAvailable(aircrafts[i].getAircraftId(), 
                                 selectedFlight.getDate(), 
                                 selectedFlight.getDepartureTime(), 
                                 selectedFlight.getArrivalTime(), 
                                 flightIdx)) {
            cout << (availableAircrafts.size() + 1) << ". ";
            aircrafts[i].display();
            availableAircrafts.push_back(i);
        }
    }

    if (availableAircrafts.empty()) {
        cout << "No aircrafts available at this time. All aircrafts are already assigned to other flights.\n";
        return;
    }

    cout << "Select aircraft number: ";
    cin >> aircraftChoice;
    cin.ignore(); // Clear newline

    if (aircraftChoice < 1 || aircraftChoice > static_cast<int>(availableAircrafts.size())) {
        cout << "Invalid aircraft selection!\n";
        return;
    }

    int aircraftIdx = availableAircrafts[aircraftChoice - 1];
    selectedFlight.setAircraft(aircrafts[aircraftIdx]);
    saveFlightsToFile();
    cout << "Aircraft assigned successfully!\n";
}

void Admin::addAircraft() {
    string aircraftId, model, capacityStr;
    int capacity;

    cout << "\n--- Add New Aircraft ---\n";
    cout << "Enter Aircraft ID: ";
    getline(cin, aircraftId);
    cout << "Enter model: ";
    getline(cin, model);
    cout << "Enter capacity: ";
    getline(cin, capacityStr);

    try {
        capacity = stoi(capacityStr);
        Aircraft aircraft(aircraftId, model, capacity);
        aircrafts.push_back(aircraft);
        saveAircraftsToFile();
        cout << "Aircraft added successfully!\n";
    } catch (...) {
        cout << "Invalid capacity. Aircraft not added.\n";
    }
}

void Admin::viewAllAircrafts() {
    cout << "\n--- All Aircrafts ---\n";
    if (aircrafts.empty()) {
        cout << "No aircrafts found.\n";
        return;
    }
    for (const auto& aircraft : aircrafts) {
        aircraft.display();
    }
}

