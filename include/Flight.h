#pragma once
#include "Aircraft.h"
#include <iostream>
#include <string>
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

  double price;
  int durationMinutes;

  static int totalFlights;

public:
  Flight(string id = "", string org = "", string dest = "", string dt = "",
         string depTime = "", string arrTime = "", string pId = "",
         Aircraft ac = Aircraft(), double pr = 0.0, int dur = 0)
      : flightId(id), origin(org), destination(dest), date(dt),
        departureTime(depTime), arrivalTime(arrTime), pilotId(pId),
        aircraft(ac), price(pr), durationMinutes(dur) {
    totalFlights++;
  }

  Flight(const Flight &other)
      : flightId(other.flightId), origin(other.origin),
        destination(other.destination), date(other.date),
        departureTime(other.departureTime), arrivalTime(other.arrivalTime),
        pilotId(other.pilotId), aircraft(other.aircraft), price(other.price),
        durationMinutes(other.durationMinutes) {
    totalFlights++;
  }

  ~Flight() { totalFlights--; }

  void display() const;
  static void printHeader();
  void printRow() const;

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

  static int getTotalFlights() { return totalFlights; }

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

  bool operator==(const Flight &other) const {
    return this->flightId == other.flightId;
  }

  bool operator<(const Flight &other) const {
    return this->price < other.price;
  }

  Flight &operator=(const Flight &other) {
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
    }
    return *this;
  }

  friend ostream &operator<<(ostream &os, const Flight &flight);

  friend void compareFlights(const Flight &f1, const Flight &f2);
};
