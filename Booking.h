#include "Booking.h"
#include <iostream>
#include <sstream>

using namespace std;

// Constructors
Booking::Booking() : bookingID(0), seatNumber(""), bookingStatus("Pending") {}

Booking::Booking(int id, Passenger p, Flight f, string seat)
    : bookingID(id), passenger(p), flight(f), seatNumber(seat), bookingStatus("Confirmed") {}

// Getters
int Booking::getBookingID() const { return bookingID; }
Passenger Booking::getPassenger() const { return passenger; }
Flight Booking::getFlight() const { return flight; }
string Booking::getSeatNumber() const { return seatNumber; }
string Booking::getBookingStatus() const { return bookingStatus; }

// Setters
void Booking::setBookingStatus(string status) { bookingStatus = status; }

// Methods
void Booking::confirmBooking() {
    bookingStatus = "Confirmed";
    cout << "\n*** Booking Confirmed! ***" << endl;
    cout << "Booking ID: " << bookingID << endl;
    cout << "Please save this ID for future reference." << endl;
}

void Booking::cancelBooking() {
    bookingStatus = "Cancelled";
    cout << "\nBooking cancelled successfully!" << endl;
}

void Booking::displayBookingDetails() const {
    cout << "\n========================================" << endl;
    cout << "Booking ID: " << bookingID << endl;
    cout << "Status: " << bookingStatus << endl;
    cout << "Seat Number: " << seatNumber << endl;
    cout << "\nPassenger Details:" << endl;
    passenger.displayDetails();
    cout << "\nFlight Details:" << endl;
    flight.displayDetails();
}

string Booking::toFileString() const {
    return to_string(bookingID) + "," + passenger.toFileString() + "," + 
           flight.toFileString() + "," + seatNumber + "," + bookingStatus;
}

Booking Booking::fromFileString(const string& line) {
    stringstream ss(line);
    string bookingIDStr, passIDStr, fName, lName, email, contact;
    string fNum, org, dest, depTime, arrTime, totSeatsStr, availSeatsStr, priceStr;
    string seat, status;

    getline(ss, bookingIDStr, ',');
    getline(ss, passIDStr, ',');
    getline(ss, fName, ',');
    getline(ss, lName, ',');
    getline(ss, email, ',');
    getline(ss, contact, ',');
    getline(ss, fNum, ',');
    getline(ss, org, ',');
    getline(ss, dest, ',');
    getline(ss, depTime, ',');
    getline(ss, arrTime, ',');
    getline(ss, totSeatsStr, ',');
    getline(ss, availSeatsStr, ',');
    getline(ss, priceStr, ',');
    getline(ss, seat, ',');
    getline(ss, status, ',');

    Passenger p(stoi(passIDStr), fName, lName, email, contact);
    Flight f(fNum, org, dest, depTime, arrTime, stoi(totSeatsStr), stod(priceStr));
    f.setAvailableSeats(stoi(availSeatsStr));
    
    Booking b(stoi(bookingIDStr), p, f, seat);
    b.bookingStatus = status;
    return b;
}