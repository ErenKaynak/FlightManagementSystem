#pragma once
#include <vector>
#include <string>
#include "Flight.h"
#include "Aircraft.h"
#include "Pilot.h"
#include "Worker.h"
#include "Menu.h"
using namespace std;

class Admin {
private:
    vector<Flight> flights;
    vector<Aircraft> aircrafts;
    vector<Pilot> pilots;
    vector<Worker> workers;

    // File I/O methods
    void loadFlightsFromFile();
    void loadAircraftsFromFile();
    void loadPilotsFromFile();
    void loadWorkersFromFile();
    void saveFlightsToFile();
    void saveAircraftsToFile();
    void savePilotsToFile();
    void saveWorkersToFile();

    // Helper methods
    string generateFlightId();
    int findFlightIndex(string flightId);
    int findAircraftIndex(string aircraftId);
    int findPilotIndex(string pilotId);
    int findWorkerIndex(string workerId);
    void pause();
    bool isDateValid(string date);
    bool isDateExpired(string date);
    bool isAircraftAvailable(string aircraftId, string date, string depTime, string arrTime, int excludeFlightIndex = -1);
    bool isPilotAvailable(string pilotId, string date, string depTime, string arrTime, int excludeFlightIndex = -1);
    int compareTimes(string time1, string time2);

public:
    Admin();
    ~Admin();
    void showMenu();
    void handleFlightMenu();
    void handleViewMenu();
    void handleWorkersMenu();

    // Flight management
    void addFlight();
    void removeFlight();
    string createFlightId();
    void viewAllFlights();

    // Aircraft management
    void assignAircraftToFlight();
    void addAircraft();
    void viewAllAircrafts();

    // Pilot management
    void addPilot();
    void assignPilotToFlight();
    void viewAllPilots();

    // Flight time management
    void assignFlightTimes();

    // Worker management
    void addWorker();
    void viewAllWorkers();
    void assignTaskToWorker();
};
