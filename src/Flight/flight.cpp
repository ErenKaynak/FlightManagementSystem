#include "Flight.h"
#include <iomanip>
#include <iostream>

int Flight::totalFlights = 0;

void Flight::display() const {
  cout << "Flight ID: " << flightId << ", Origin: " << origin
       << ", Destination: " << destination << ", Date: " << date;
  if (!departureTime.empty()) {
    cout << ", Departure: " << departureTime;
  }
  if (!arrivalTime.empty()) {
    cout << ", Arrival: " << arrivalTime;
  }
  cout << ", Aircraft: " << aircraft.getModel() << " ("
       << aircraft.getAircraftId() << ")";
  if (!pilotId.empty()) {
    cout << ", Pilot ID: " << pilotId;
  }
  if (price > 0) {
    cout << ", Price: $" << fixed << setprecision(2) << price;
  }
  if (durationMinutes > 0) {
    cout << ", Duration: " << durationMinutes << " mins";
  }
  cout << endl;
}

void Flight::printHeader() {
  cout << left << setw(8) << "ID" << setw(26) << "Route" << setw(12) << "Date"
       << setw(10) << "Dep" << setw(10) << "Arr" << setw(10) << "Price($)"
       << setw(8) << "Dur(m)" << setw(15) << "Aircraft" << setw(10) << "Pilot"
       << endl;
  cout << string(115, '-') << endl;
}

void Flight::printRow() const {
  string route = origin + "->" + destination;
  string ac = aircraft.getAircraftId();
  cout << left << setw(8) << flightId << setw(26) << route.substr(0, 25)
       << setw(12) << date << setw(10) << departureTime << setw(10)
       << arrivalTime << "$" << fixed << setprecision(2) << setw(9) << price
       << setw(8) << durationMinutes << setw(15) << ac.substr(0, 14) << setw(10)
       << pilotId << endl;
}

ostream &operator<<(ostream &os, const Flight &flight) {
  os << "Flight[ID: " << flight.flightId << ", Route: " << flight.origin
     << " -> " << flight.destination << ", Date: " << flight.date;

  if (!flight.departureTime.empty()) {
    os << ", Departure: " << flight.departureTime;
  }
  if (!flight.arrivalTime.empty()) {
    os << ", Arrival: " << flight.arrivalTime;
  }
  if (flight.price > 0) {
    os << ", Price: $" << fixed << setprecision(2) << flight.price;
  }
  if (flight.durationMinutes > 0) {
    os << ", Duration: " << flight.durationMinutes << " mins";
  }
  os << "]";
  return os;
}

void compareFlights(const Flight &f1, const Flight &f2) {
  cout << "\n=== Flight Comparison ===" << endl;
  cout << "Flight 1: " << f1 << endl;
  cout << "Flight 2: " << f2 << endl;
  cout << "\nComparison Results:" << endl;

  if (f1 == f2) {
    cout << "- These are the same flight (same ID)" << endl;
  } else {
    cout << "- These are different flights" << endl;
  }

  if (f1.price > 0 && f2.price > 0) {
    if (f1.price < f2.price) {
      cout << "- Flight 1 is cheaper by $" << fixed << setprecision(2)
           << (f2.price - f1.price) << endl;
    } else if (f1.price > f2.price) {
      cout << "- Flight 2 is cheaper by $" << fixed << setprecision(2)
           << (f1.price - f2.price) << endl;
    } else {
      cout << "- Both flights have the same price" << endl;
    }
  }

  if (f1.durationMinutes > 0 && f2.durationMinutes > 0) {
    if (f1.durationMinutes < f2.durationMinutes) {
      cout << "- Flight 1 is faster by "
           << (f2.durationMinutes - f1.durationMinutes) << " minutes" << endl;
    } else if (f1.durationMinutes > f2.durationMinutes) {
      cout << "- Flight 2 is faster by "
           << (f1.durationMinutes - f2.durationMinutes) << " minutes" << endl;
    } else {
      cout << "- Both flights have the same duration" << endl;
    }
  }
  cout << "========================\n" << endl;
}
