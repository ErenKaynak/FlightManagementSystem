#include "../include/Admin.h"
#include "../include/Menu.h"
#include <iostream>
using namespace std;

Admin::Admin() {
    // Load data from files on initialization
    loadAircraftsFromFile();
    loadPilotsFromFile();
    loadWorkersFromFile();
    loadFlightsFromFile();
}

Admin::~Admin() {
    // Save data to files on destruction
    saveFlightsToFile();
    saveAircraftsToFile();
    savePilotsToFile();
    saveWorkersToFile();
}

// Menu System

void Admin::showMenu() {
    int choice;
    while (true) {
        Menu::showMainMenu();
        cin >> choice;
        cin.ignore(); // Clear newline

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
            case 0:
                cout << "Exiting Flight Management System. Goodbye!\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Admin::handleFlightMenu() {
    int choice;
    while (true) {
        Menu::showFlightMenu();
        cin >> choice;
        cin.ignore(); // Clear newline

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
            case 8:
                assignFlightTimes();
                break;
            case 0:
                return; // Go to Main Menu
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Admin::handleViewMenu() {
    int choice;
    while (true) {
        Menu::showViewMenu();
        cin >> choice;
        cin.ignore(); // Clear newline

        switch (choice) {
            case 1:
                viewAllFlights();
                pause();
                return; // Return to Main Menu after pause
            case 2:
                viewAllPilots();
                pause();
                return; // Return to Main Menu after pause
            case 3:
                viewAllWorkers();
                pause();
                return; // Return to Main Menu after pause
            case 4:
                viewAllAircrafts();
                pause();
                return; // Return to Main Menu after pause
            case 0:
                return; // Go to Main Menu
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Admin::handleWorkersMenu() {
    int choice;
    while (true) {
        Menu::showWorkersMenu();
        cin >> choice;
        cin.ignore(); // Clear newline

        switch (choice) {
            case 1:
                addWorker();
                break;
            case 2:
                assignTaskToWorker();
                break;
            case 0:
                return; // Go to Main Menu
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
