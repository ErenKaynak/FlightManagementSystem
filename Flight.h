#include "Flight.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

// Constructors
Flight::Flight() : flightNumber(""), origin(""), destination(""), departureTime(""), 
           arrivalTime(""), totalSeats(0), availableSeats(0), price(0.0) {}

Flight::Flight(string fNum, string org, string dest, string depTime, string arrTime, 
       int totSeats, double pr)
    : flightNumber(fNum), origin(org), destination(dest), departureTime(depTime),
      arrivalTime(arrTime), totalSeats(totSeats), availableSeats(totSeats), price(pr) {}

// Getters
string Flight::getFlightNumber() const { return flightNumber; }
string Flight::getOrigin() const { return origin; }
string Flight::getDestination() const { return destination; }
string Flight::getDepartureTime() const { return departureTime; }
string Flight::getArrivalTime() const { return arrivalTime; }
int Flight::getTotalSeats() const { return totalSeats; }
int Flight::getAvailableSeats() const { return availableSeats; }
double Flight::getPrice() const { return price; }

// Setters
void Flight::setAvailableSeats(int seats) { availableSeats = seats; }

// Methods
void Flight::displayDetails() const {
    cout << "\n========================================" << endl;
    cout << "Flight Number: " << flightNumber << endl;
    cout << "Route: " << origin << " -> " << destination << endl;
    cout << "Departure: " << departureTime << endl;
    cout << "Arrival: " << arrivalTime << endl;
    cout << "Available Seats: " << availableSeats << "/" << totalSeats << endl;
    cout << "Price: $" << fixed << setprecision(2) << price << endl;
    cout << "========================================" << endl;
}

bool Flight::bookSeat() {
    if (availableSeats > 0) {
        availableSeats--;
        return true;
    }
    return false;
}

void Flight::cancelSeat() {
    if (availableSeats < totalSeats) {
        availableSeats++;
    }
}

bool Flight::isFull() const {
    return availableSeats == 0;
}

string Flight::toFileString() const {
    return flightNumber + "," + origin + "," + destination + "," + 
           departureTime + "," + arrivalTime + "," + 
           to_string(totalSeats) + "," + to_string(availableSeats) + "," + 
           to_string(price);
}

Flight Flight::fromFileString(const string& line) {
    stringstream ss(line);
    string fNum, org, dest, depTime, arrTime, totSeatsStr, availSeatsStr, priceStr;
    
    getline(ss, fNum, ',');
    getline(ss, org, ',');
    getline(ss, dest, ',');
    getline(ss, depTime, ',');
    getline(ss, arrTime, ',');
    getline(ss, totSeatsStr, ',');
    getline(ss, availSeatsStr, ',');
    getline(ss, priceStr, ',');

    Flight f(fNum, org, dest, depTime, arrTime, stoi(totSeatsStr), stod(priceStr));
    f.setAvailableSeats(stoi(availSeatsStr));
    return f;
}