#include "Admin.h"
#include "Menu.h"
#include "Person.h"
#include "Pilot.h"
#include "Worker.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

Admin::Admin() {
    
    loadAircraftsFromFile();
    loadPeopleFromFile();
    loadFlightsFromFile();
}

Admin::~Admin() {
    
    saveFlightsToFile();
    saveAircraftsToFile();
    savePeopleToFile();
    for (Person* person : people) {
        delete person;
    }
}



void Admin::showMenu() {
    int choice;
    while (true) {
        Menu::showMainMenu();
        std::cin >> choice;
        std::cin.ignore(); 

        switch (choice) {
            case 1:
                handleFlightMenu();
                break;
            case 2:
                handleViewMenu();
                break;
            case 3:
                handleWorkersMenu();
                break;
            case 4:
                handleAlgorithmsMenu();
                break;
            case 0:
                std::cout << "Exiting Flight Management System. Goodbye!\n";
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Admin::handleFlightMenu() {
    int choice;
    while (true) {
        Menu::showFlightMenu();
        std::cin >> choice;
        std::cin.ignore(); 

        switch (choice) {
            case 1:
                addFlight();
                break;
            case 2:
                addAircraft();
                break;
            case 3:
                addPilot();
                break;
            case 4:
                removeFlight();
                break;
            case 5:
                createFlightId();
                break;
            case 6:
                assignAircraftToFlight();
                break;
            case 7:
                assignPilotToFlight();
                break;
            case 0:
                return; 
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Admin::handleViewMenu() {
    int choice;
    while (true) {
        Menu::showViewMenu();
        std::cin >> choice;
        std::cin.ignore(); 

        switch (choice) {
            case 1:
                viewAllFlights();
                pause();
                break;
            case 2:
                viewAllPilots();
                pause();
                break;
            case 3:
                viewAllWorkers();
                pause();
                break;
            case 4:
                viewAllAircrafts();
                pause();
                break;
            case 5:
                viewAllPeople();
                pause();
                break;
            case 0:
                return; 
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Admin::handleWorkersMenu() {
    int choice;
    while (true) {
        Menu::showWorkersMenu();
        std::cin >> choice;
        std::cin.ignore(); 

        switch (choice) {
            case 1:
                addWorker();
                break;
            case 2:
                assignTaskToWorker();
                break;
            case 0:
                return; 
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Admin::handleAlgorithmsMenu() {
    int choice;
    while (true) {
        Menu::showAlgorithmsMenu();
        std::cin >> choice;
        std::cin.ignore(); 

        switch (choice) {
            case 1:
                displayStatistics();
                pause();
                break;
            case 2: {
                std::cout << "\n--- Calculate Total Revenue ---\n";
                double revenue = calculateTotalRevenue();
                std::cout << "Total Revenue from all flights: $" 
                         << std::fixed << std::setprecision(2) << revenue << std::endl;
                pause();
                break;
            }
            case 3:
                sortFlightsByPrice();
                pause();
                break;
            case 4:
                sortFlightsByDuration();
                pause();
                break;
            case 5: {
                std::string flightId;
                std::cout << "\nEnter Flight ID to search: ";
                std::getline(std::cin, flightId);
                searchFlightById(flightId);
                pause();
                break;
            }
            case 6:
                demonstrateAlgorithms();
                pause();
                break;
            case 0:
                return; 
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}


void Admin::viewAllPeople() {
    std::cout << "--- All People ---\n";
    for (const auto& person : people) {
        person->display();
    }
    std::cout << "--------------------\n";
}

void Admin::loadPeopleFromFile() {
    std::ifstream file("data/people.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening people.txt for reading.\n";
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string type, id, name, extra;
        std::getline(ss, type, ',');
        std::getline(ss, id, ',');
        std::getline(ss, name, ',');
        std::getline(ss, extra, ',');
        if (type == "Pilot") {
            people.push_back(new Pilot(id, name, extra));
        } else if (type == "Worker") {
            people.push_back(new Worker(id, name, extra));
        }
    }
    file.close();
}

void Admin::savePeopleToFile() {
    std::ofstream file("data/people.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening people.txt for writing.\n";
        return;
    }
    for (const auto& person : people) {
        file << person->getId() << "," << person->getName();
        if (Pilot* p = dynamic_cast<Pilot*>(person)) {
            file << ",Pilot," << p->getLicenseNumber() << "\n";
        } else if (Worker* w = dynamic_cast<Worker*>(person)) {
            file << ",Worker," << w->getTask() << "\n";
        }
    }
    file.close();
}

int Admin::findPersonIndex(std::string personId) {
    for (size_t i = 0; i < people.size(); ++i) {
        if (people[i]->getId() == personId) {
            return i;
        }
    }
    return -1;
}

