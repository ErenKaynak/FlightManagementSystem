#pragma once
#include <string>
#include <iostream>
#include "Aircraft.h"
using namespace std;

class Flight {
private:
    string flightId;
    string origin;
    string destination;
    string date;
    string departureTime;
    string arrivalTime;
    string pilotId;
    Aircraft aircraft;
    
    // REQUIREMENT: Additional fields for algorithmic problems
    double price;           // Price of the flight ticket
    int durationMinutes;    // Flight duration in minutes

    // REQUIREMENT: Static Variable - Track total number of flights created
    static int totalFlights;

public:
    Flight(string id="", string org="", string dest="", string dt="", string depTime="", string arrTime="", string pId="", Aircraft ac=Aircraft(), double pr=0.0, int dur=0)
        : flightId(id), origin(org), destination(dest), date(dt), departureTime(depTime), arrivalTime(arrTime), pilotId(pId), aircraft(ac), price(pr), durationMinutes(dur) {
        totalFlights++; // Increment static counter when flight is created
    }
    
    // Copy constructor to properly handle static counter
    Flight(const Flight& other)
        : flightId(other.flightId), origin(other.origin), destination(other.destination),
          date(other.date), departureTime(other.departureTime), arrivalTime(other.arrivalTime),
          pilotId(other.pilotId), aircraft(other.aircraft), price(other.price), 
          durationMinutes(other.durationMinutes) {
        totalFlights++;
    }
    
    // Destructor to decrement counter
    ~Flight() {
        totalFlights--;
    }

    void display() const;

    // Getters
    string getFlightId() const { return flightId; }
    string getOrigin() const { return origin; }
    string getDestination() const { return destination; }
    string getDate() const { return date; }
    string getDepartureTime() const { return departureTime; }
    string getArrivalTime() const { return arrivalTime; }
    string getPilotId() const { return pilotId; }
    Aircraft getAircraft() const { return aircraft; }
    double getPrice() const { return price; }
    int getDurationMinutes() const { return durationMinutes; }
    
    // REQUIREMENT: Static method to get total flights count
    static int getTotalFlights() { return totalFlights; }

    // Setters
    void setFlightId(string id) { flightId = id; }
    void setOrigin(string org) { origin = org; }
    void setDestination(string dest) { destination = dest; }
    void setDate(string dt) { date = dt; }
    void setDepartureTime(string depTime) { departureTime = depTime; }
    void setArrivalTime(string arrTime) { arrivalTime = arrTime; }
    void setPilotId(string pId) { pilotId = pId; }
    void setAircraft(Aircraft ac) { aircraft = ac; }
    void setPrice(double pr) { price = pr; }
    void setDurationMinutes(int dur) { durationMinutes = dur; }
    
    // REQUIREMENT: Operator Overloading - Equality operator to compare flights by ID
    bool operator==(const Flight& other) const {
        return this->flightId == other.flightId;
    }
    
    // REQUIREMENT: Operator Overloading - Less than operator for sorting (by price)
    bool operator<(const Flight& other) const {
        return this->price < other.price;
    }
    
    // REQUIREMENT: Operator Overloading - Assignment operator
    Flight& operator=(const Flight& other) {
        if (this != &other) {
            flightId = other.flightId;
            origin = other.origin;
            destination = other.destination;
            date = other.date;
            departureTime = other.departureTime;
            arrivalTime = other.arrivalTime;
            pilotId = other.pilotId;
            aircraft = other.aircraft;
            price = other.price;
            durationMinutes = other.durationMinutes;
            // Note: Static counter not affected by assignment
        }
        return *this;
    }
    
    // REQUIREMENT: Friend Function - Stream output operator for easy printing
    friend ostream& operator<<(ostream& os, const Flight& flight);
    
    // REQUIREMENT: Friend Function - Utility function to display detailed flight comparison
    friend void compareFlights(const Flight& f1, const Flight& f2);
};
