#include "../include/Menu.h"

void Menu::showMainMenu() {
    cout << "\nMain Menu\n";
    cout << "——————\n";
    cout << "1. Flight\n";
    cout << "2. View\n";
    cout << "3. Workers\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

void Menu::showFlightMenu() {
    cout << "\nFlight\n";
    cout << "———————\n";
    cout << "1. Add Flight\n";
    cout << "2. Add Aircraft\n";
    cout << "3. Add Pilot\n";
    cout << "4. Remove Flight\n";
    cout << "5. Create Flight ID\n";
    cout << "6. Assign Aircraft to Flight\n";
    cout << "7. Assign Pilot to Flight\n";
    cout << "8. Assign Flight Times (Departure/Arrival)\n";
    cout << "0. Go to Main Menu\n";
    cout << "Enter your choice: ";
}

void Menu::showViewMenu() {
    cout << "\nView\n";
    cout << "———————\n";
    cout << "1. View All Flights\n";
    cout << "2. View All Pilots\n";
    cout << "3. View All Workers\n";
    cout << "4. View All Aircrafts\n";
    cout << "0. Go to Main Menu\n";
    cout << "Enter your choice: ";
}

void Menu::showWorkersMenu() {
    cout << "\nWorkers\n";
    cout << "——————\n";
    cout << "1. Add Worker\n";
    cout << "2. Assign Task to Worker\n";
    cout << "0. Go to Main Menu\n";
    cout << "Enter your choice: ";
}

