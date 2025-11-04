#pragma once
#include <string>
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

public:
    Flight(string id="", string org="", string dest="", string dt="", string depTime="", string arrTime="", string pId="", Aircraft ac=Aircraft())
        : flightId(id), origin(org), destination(dest), date(dt), departureTime(depTime), arrivalTime(arrTime), pilotId(pId), aircraft(ac) {}

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

    // Setters
    void setFlightId(string id) { flightId = id; }
    void setOrigin(string org) { origin = org; }
    void setDestination(string dest) { destination = dest; }
    void setDate(string dt) { date = dt; }
    void setDepartureTime(string depTime) { departureTime = depTime; }
    void setArrivalTime(string arrTime) { arrivalTime = arrTime; }
    void setPilotId(string pId) { pilotId = pId; }
    void setAircraft(Aircraft ac) { aircraft = ac; }
};
