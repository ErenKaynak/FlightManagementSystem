#pragma once
#include <vector>
#include <string>
#include "Flight.h"
#include "Aircraft.h"
#include "Person.h"
#include "Menu.h"

class Admin {
private:
    std::vector<Flight> flights;
    std::vector<Aircraft> aircrafts;
    std::vector<Person*> people;

    
    void loadFlightsFromFile();
    void loadAircraftsFromFile();
    void loadPeopleFromFile();
    void saveFlightsToFile();
    void saveAircraftsToFile();
    void savePeopleToFile();

    
    std::string generateFlightId();
    int findFlightIndex(std::string flightId);
    int findAircraftIndex(std::string aircraftId);
    int findPersonIndex(std::string personId);
    void pause();
    bool isDateValid(std::string date);
    bool isDateExpired(std::string date);
    bool isAircraftAvailable(std::string aircraftId, std::string date, std::string depTime, std::string arrTime, int excludeFlightIndex = -1);
    bool isPilotAvailable(std::string pilotId, std::string date, std::string depTime, std::string arrTime, int excludeFlightIndex = -1);
    int compareTimes(std::string time1, std::string time2);
    
    
    
    int partition(std::vector<Flight>& arr, int low, int high, bool sortByPrice);
    void quickSortHelper(std::vector<Flight>& arr, int low, int high, bool sortByPrice);
    
    
    int binarySearchById(const std::vector<Flight>& sortedFlights, const std::string& flightId);

public:
    Admin();
    ~Admin();
    void showMenu();
    void handleFlightMenu();
    void handleViewMenu();
    void handleWorkersMenu();
    void handleAlgorithmsMenu();  

    
    void addFlight();
    void removeFlight();
    std::string createFlightId();
    void viewAllFlights();

    
    void assignAircraftToFlight();
    void addAircraft();
    void viewAllAircrafts();

    
    void addPilot();
    void addWorker();
    void assignPilotToFlight();
    void viewAllPilots();
    void viewAllWorkers();
    void viewAllPeople();
    void assignTaskToWorker();
    
    
    
    
    double calculateTotalRevenue() const;
    
    
    void sortFlightsByPrice();      
    void sortFlightsByDuration();   
    
    
    Flight* searchFlightById(const std::string& flightId);
    
    
    void displayStatistics() const;  
    void demonstrateAlgorithms();    
};
