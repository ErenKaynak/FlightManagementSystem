#include "../include/Admin.h"
#include <fstream>
#include <sstream>
using namespace std;

// File I/O Methods

void Admin::loadFlightsFromFile() {
    ifstream file("data/flights.txt");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        istringstream iss(line);
        string flightId, origin, destination, date, depTime, arrTime, pilotId, aircraftId;
        
        if (getline(iss, flightId, ',') &&
            getline(iss, origin, ',') &&
            getline(iss, destination, ',') &&
            getline(iss, date, ',') &&
            getline(iss, depTime, ',') &&
            getline(iss, arrTime, ',') &&
            getline(iss, pilotId, ',') &&
            getline(iss, aircraftId)) {
            
            Aircraft ac;
            int aircraftIdx = findAircraftIndex(aircraftId);
            if (aircraftIdx >= 0) {
                ac = aircrafts[aircraftIdx];
            }
            
            Flight flight(flightId, origin, destination, date, depTime, arrTime, pilotId, ac);
            flights.push_back(flight);
        }
    }
    file.close();
}

void Admin::saveFlightsToFile() {
    ofstream file("data/flights.txt");
    if (!file.is_open()) return;

    for (const auto& flight : flights) {
        file << flight.getFlightId() << ","
             << flight.getOrigin() << ","
             << flight.getDestination() << ","
             << flight.getDate() << ","
             << flight.getDepartureTime() << ","
             << flight.getArrivalTime() << ","
             << flight.getPilotId() << ","
             << flight.getAircraft().getAircraftId() << "\n";
    }
    file.close();
}

void Admin::loadAircraftsFromFile() {
    ifstream file("data/aircraft.txt");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        istringstream iss(line);
        string aircraftId, model, capacityStr;
        
        if (getline(iss, aircraftId, ',') &&
            getline(iss, model, ',') &&
            getline(iss, capacityStr)) {
            
            int capacity = stoi(capacityStr);
            Aircraft ac(aircraftId, model, capacity);
            aircrafts.push_back(ac);
        }
    }
    file.close();
}

void Admin::saveAircraftsToFile() {
    ofstream file("data/aircraft.txt");
    if (!file.is_open()) return;

    for (const auto& aircraft : aircrafts) {
        file << aircraft.getAircraftId() << ","
             << aircraft.getModel() << ","
             << aircraft.getCapacity() << "\n";
    }
    file.close();
}

void Admin::loadPilotsFromFile() {
    ifstream file("data/pilots.txt");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        istringstream iss(line);
        string pilotId, name, licenseNumber;
        
        if (getline(iss, pilotId, ',') &&
            getline(iss, name, ',') &&
            getline(iss, licenseNumber)) {
            
            Pilot pilot(pilotId, name, licenseNumber);
            pilots.push_back(pilot);
        }
    }
    file.close();
}

void Admin::savePilotsToFile() {
    ofstream file("data/pilots.txt");
    if (!file.is_open()) return;

    for (const auto& pilot : pilots) {
        file << pilot.getPilotId() << ","
             << pilot.getName() << ","
             << pilot.getLicenseNumber() << "\n";
    }
    file.close();
}

void Admin::loadWorkersFromFile() {
    ifstream file("data/workers.txt");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        istringstream iss(line);
        string workerId, name, task;
        
        if (getline(iss, workerId, ',') &&
            getline(iss, name, ',')) {
            getline(iss, task); // Task might be empty
            Worker worker(workerId, name, task);
            workers.push_back(worker);
        }
    }
    file.close();
}

void Admin::saveWorkersToFile() {
    ofstream file("data/workers.txt");
    if (!file.is_open()) return;

    for (const auto& worker : workers) {
        file << worker.getWorkerId() << ","
             << worker.getName() << ","
             << worker.getTask() << "\n";
    }
    file.close();
}

