#include <iostream>
#include <cstdlib>
#include <ctime>
#include "FlightDatabase.h"
#include "Flight.h"
#include "Passenger.h"
#include "Booking.h"
#include "Admin.h"

using namespace std;

// Utility function for generating random IDs
int generateRandomID() {
    return rand() % 90000 + 10000;
}

// ==================== USER INTERFACE CLASS ====================
class UserInterface {
private:
    FlightDatabase* db;

public:
    UserInterface() {
        db = FlightDatabase::getInstance();
    }

    void passengerMenu() {
        while (true) {
            cout << "\n========================================" << endl;
            cout << "       PASSENGER MENU" << endl;
            cout << "========================================" << endl;
            cout << "1. Search Flights" << endl;
            cout << "2. Book a Flight" << endl;
            cout << "3. Cancel Booking" << endl;
            cout << "4. View My Bookings" << endl;
            cout << "5. Back to Main Menu" << endl;
            cout << "========================================" << endl;
            cout << "Enter your choice: ";

            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    searchFlights();
                    break;
                case 2:
                    bookFlight();
                    break;
                case 3:
                    cancelBooking();
                    break;
                case 4:
                    viewMyBookings();
                    break;
                case 5:
                    return;
                default:
                    cout << "Invalid option, please try again." << endl;
            }
        }
    }

    void searchFlights() {
        string origin, destination;
        cout << "\nEnter origin city: ";
        cin.ignore();
        getline(cin, origin);
        cout << "Enter destination city: ";
        getline(cin, destination);

        vector<Flight*> results = db->searchFlights(origin, destination);

        if (results.empty()) {
            cout << "\nNo flights found for the given route." << endl;
            return;
        }

        cout << "\n========== SEARCH RESULTS ==========" << endl;
        for (size_t i = 0; i < results.size(); i++) {
            cout << "\nOption " << (i + 1) << ":" << endl;
            results[i]->displayDetails();
        }
    }

    void bookFlight() {
        string flightNumber;
        cout << "\nEnter flight number to book: ";
        cin >> flightNumber;

        Flight* flight = db->findFlightByID(flightNumber);

        if (flight == nullptr) {
            cout << "Flight not found!" << endl;
            return;
        }

        if (flight->isFull()) {
            cout << "Sorry, this flight is fully booked!" << endl;
            return;
        }

        flight->displayDetails();

        string firstName, lastName, email, contact;
        cout << "\nEnter passenger details:" << endl;
        cout << "First Name: ";
        cin.ignore();
        getline(cin, firstName);
        cout << "Last Name: ";
        getline(cin, lastName);
        cout << "Email: ";
        getline(cin, email);
        cout << "Contact Number: ";
        getline(cin, contact);

        int passengerID = generateRandomID();
        Passenger passenger(passengerID, firstName, lastName, email, contact);

        string seatNumber;
        cout << "Enter preferred seat number (e.g., 12A): ";
        getline(cin, seatNumber);

        int bookingID = db->generateBookingID();
        Booking booking(bookingID, passenger, *flight, seatNumber);

        if (flight->bookSeat()) {
            booking.confirmBooking();
            db->addBooking(booking);
        } else {
            cout << "Booking failed. Flight is full." << endl;
        }
    }

    void cancelBooking() {
        int bookingID;
        cout << "\nEnter Booking ID to cancel: ";
        cin >> bookingID;

        Booking* booking = db->findBookingByID(bookingID);

        if (booking == nullptr) {
            cout << "Booking not found!" << endl;
            return;
        }

        if (booking->getBookingStatus() == "Cancelled") {
            cout << "This booking has already been cancelled." << endl;
            return;
        }

        Flight* flight = db->findFlightByID(booking->getFlight().getFlightNumber());
        if (flight != nullptr) {
            flight->cancelSeat();
        }

        booking->cancelBooking();
    }

    void viewMyBookings() {
        string firstName, lastName;
        cout << "\nEnter your first name: ";
        cin.ignore();
        getline(cin, firstName);
        cout << "Enter your last name: ";
        getline(cin, lastName);

        vector<Booking*> bookings = db->findBookingsByPassengerName(firstName, lastName);

        if (bookings.empty()) {
            cout << "\nNo bookings found for " << firstName << " " << lastName << endl;
            return;
        }

        cout << "\n========== YOUR BOOKINGS ==========" << endl;
        for (auto booking : bookings) {
            booking->displayBookingDetails();
        }
    }

    void adminMenu() {
        string password;
        cout << "\nEnter admin password: ";
        cin >> password;

        if (password != "admin123") {
            cout << "Incorrect password! Access denied." << endl;
            return;
        }

        Admin admin("admin", "admin123", "ADMIN001");

        while (true) {
            cout << "\n========================================" << endl;
            cout << "       ADMIN MENU" << endl;
            cout << "========================================" << endl;
            cout << "1. Add New Flight" << endl;
            cout << "2. Remove Flight" << endl;
            cout << "3. View All Flights" << endl;
            cout << "4. View All Bookings" << endl;
            cout << "5. Back to Main Menu" << endl;
            cout << "========================================" << endl;
            cout << "Enter your choice: ";

            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    admin.adminAddFlight();
                    break;
                case 2:
                    admin.adminRemoveFlight();
                    break;
                case 3:
                    admin.viewAllFlights();
                    break;
                case 4:
                    admin.viewAllBookings();
                    break;
                case 5:
                    return;
                default:
                    cout << "Invalid option, please try again." << endl;
            }
        }
    }

    void mainMenu() {
        srand(time(0));
        
        while (true) {
            cout << "\n========================================" << endl;
            cout << "   FLIGHT MANAGEMENT SYSTEM" << endl;
            cout << "========================================" << endl;
            cout << "1. Passenger Mode" << endl;
            cout << "2. Admin Mode" << endl;
            cout << "3. Exit" << endl;
            cout << "========================================" << endl;
            cout << "Enter your choice: ";

            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    passengerMenu();
                    break;
                case 2:
                    adminMenu();
                    break;
                case 3:
                    cout << "\nSaving data..." << endl;
                    db->saveDataToFile();
                    cout << "Thank you for using Flight Management System!" << endl;
                    return;
                default:
                    cout << "Invalid option, please try again." << endl;
            }
        }
    }
};

// ==================== MAIN FUNCTION ====================
int main() {
    UserInterface ui;
    ui.mainMenu();
    return 0;
}