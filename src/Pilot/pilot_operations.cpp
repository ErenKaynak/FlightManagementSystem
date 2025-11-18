#include "Admin.h"
#include "Person.h"
#include "Pilot.h"
#include <iostream>
#include <vector>

void Admin::addPilot() {
    std::string id, name, license;
    std::cout << "Enter Pilot ID: ";
    std::getline(std::cin, id);
    std::cout << "Enter Pilot Name: ";
    std::getline(std::cin, name);
    std::cout << "Enter License Number: ";
    std::getline(std::cin, license);
    people.push_back(new Pilot(id, name, license));
    savePeopleToFile();
    std::cout << "Pilot added successfully." << std::endl;
}

void Admin::assignPilotToFlight() {
    std::string flightId, pilotId;
    std::cout << "Enter Flight ID: ";
    std::getline(std::cin, flightId);
    int flightIndex = findFlightIndex(flightId);
    if (flightIndex == -1) {
        std::cout << "Flight not found." << std::endl;
        return;
    }

    std::cout << "Available Pilots:" << std::endl;
    for (Person* p : people) {
        if (Pilot* pilot = dynamic_cast<Pilot*>(p)) {
            if (isPilotAvailable(pilot->getId(), flights[flightIndex].getDepartureTime(), flights[flightIndex].getDepartureTime(), flights[flightIndex].getArrivalTime())) {
                pilot->display(true);
            }
        }
    }

    std::cout << "Enter Pilot ID to assign: ";
    std::getline(std::cin, pilotId);
    int personIndex = findPersonIndex(pilotId);
    if (personIndex == -1) {
        std::cout << "Pilot not found." << std::endl;
        return;
    }

    flights[flightIndex].setPilotId(pilotId);
    saveFlightsToFile();
    std::cout << "Pilot assigned to flight successfully." << std::endl;
}

void Admin::viewAllPilots() {
    std::cout << "--- All Pilots ---" << std::endl;
    for (Person* p : people) {
        if (Pilot* pilot = dynamic_cast<Pilot*>(p)) {
            pilot->display(true);
        }
    }
    std::cout << "--------------------" << std::endl;
}

