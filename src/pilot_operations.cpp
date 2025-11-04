#include "../include/Admin.h"
#include <iostream>
#include <vector>
using namespace std;

// Pilot Management Functions

void Admin::addPilot() {
    string pilotId, name, licenseNumber;
    cout << "\n--- Add New Pilot ---\n";
    cout << "Enter Pilot ID: ";
    getline(cin, pilotId);
    cout << "Enter pilot name: ";
    getline(cin, name);
    cout << "Enter license number: ";
    getline(cin, licenseNumber);

    Pilot pilot(pilotId, name, licenseNumber);
    pilots.push_back(pilot);
    savePilotsToFile();
    cout << "Pilot added successfully!\n";
}

void Admin::assignPilotToFlight() {
    int flightChoice, pilotChoice;
    cout << "\n--- Assign Pilot to Flight ---\n";
    
    if (flights.empty()) {
        cout << "No flights available. Please add flights first.\n";
        return;
    }

    if (pilots.empty()) {
        cout << "No pilots available. Please add pilots first.\n";
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
        cout << "Error: Cannot assign pilot to an expired flight.\n";
        return;
    }

    cout << "\n--- Available Pilots ---\n";
    vector<int> availablePilots;
    for (size_t i = 0; i < pilots.size(); i++) {
        if (isPilotAvailable(pilots[i].getPilotId(), 
                            selectedFlight.getDate(), 
                            selectedFlight.getDepartureTime(), 
                            selectedFlight.getArrivalTime(), 
                            flightIdx)) {
            cout << (availablePilots.size() + 1) << ". ";
            pilots[i].display();
            availablePilots.push_back(i);
        }
    }

    if (availablePilots.empty()) {
        cout << "No pilots available at this time. All pilots are already assigned to other flights.\n";
        return;
    }

    cout << "Select pilot number: ";
    cin >> pilotChoice;
    cin.ignore(); // Clear newline

    if (pilotChoice < 1 || pilotChoice > static_cast<int>(availablePilots.size())) {
        cout << "Invalid pilot selection!\n";
        return;
    }

    int pilotIdx = availablePilots[pilotChoice - 1];
    selectedFlight.setPilotId(pilots[pilotIdx].getPilotId());
    saveFlightsToFile();
    cout << "Pilot assigned successfully!\n";
}

void Admin::viewAllPilots() {
    cout << "\n--- All Pilots ---\n";
    if (pilots.empty()) {
        cout << "No pilots found.\n";
        return;
    }
    for (const auto& pilot : pilots) {
        pilot.display();
    }
}

