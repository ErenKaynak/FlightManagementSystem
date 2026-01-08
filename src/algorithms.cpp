#include "Admin.h"
#include <algorithm>
#include <iomanip>
#include <iostream>

using namespace std;

double Admin::calculateTotalRevenue() const {
  double totalRevenue = 0.0;

  for (const auto &flight : flights) {
    double price = flight.getPrice();

    if (price >= 0) {
      totalRevenue += price;
    }
  }

  return totalRevenue;
}

int Admin::partition(vector<Flight> &arr, int low, int high, bool sortByPrice) {

  Flight pivot = arr[high];

  int i = low - 1;

  for (int j = low; j < high; j++) {

    bool isSmaller;
    if (sortByPrice) {
      isSmaller = arr[j].getPrice() < pivot.getPrice();
    } else {
      isSmaller = arr[j].getDurationMinutes() < pivot.getDurationMinutes();
    }

    if (isSmaller) {
      i++;
      swap(arr[i], arr[j]);
    }
  }

  swap(arr[i + 1], arr[high]);
  return i + 1;
}

void Admin::quickSortHelper(vector<Flight> &arr, int low, int high,
                            bool sortByPrice) {
  if (low < high) {

    int pi = partition(arr, low, high, sortByPrice);

    quickSortHelper(arr, low, pi - 1, sortByPrice);
    quickSortHelper(arr, pi + 1, high, sortByPrice);
  }
}

void Admin::sortFlightsByPrice() {
  if (flights.empty()) {
    cout << "No flights to sort." << endl;
    return;
  }

  cout << "\n--- Sorting Flights by Price (QuickSort Algorithm) ---" << endl;
  cout << "Before sorting:" << endl;
  Flight::printHeader();
  for (const auto &flight : flights) {
    flight.printRow();
  }

  quickSortHelper(flights, 0, flights.size() - 1, true);

  cout << "\nAfter sorting (by price - ascending):" << endl;
  Flight::printHeader();
  for (const auto &flight : flights) {
    flight.printRow();
  }

  saveFlightsToFile();
  cout << "\nFlights sorted successfully!" << endl;
}

void Admin::sortFlightsByDuration() {
  if (flights.empty()) {
    cout << "No flights to sort." << endl;
    return;
  }

  cout << "\n--- Sorting Flights by Duration (QuickSort Algorithm) ---" << endl;
  cout << "Before sorting:" << endl;
  Flight::printHeader();
  for (const auto &flight : flights) {
    flight.printRow();
  }

  quickSortHelper(flights, 0, flights.size() - 1, false);

  cout << "\nAfter sorting (by duration - ascending):" << endl;
  Flight::printHeader();
  for (const auto &flight : flights) {
    flight.printRow();
  }

  saveFlightsToFile();
  cout << "\nFlights sorted successfully!" << endl;
}

int Admin::binarySearchById(const vector<Flight> &sortedFlights,
                            const string &flightId) {

  if (sortedFlights.empty()) {
    return -1;
  }

  int left = 0;
  int right = sortedFlights.size() - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2;

    string midId = sortedFlights[mid].getFlightId();

    if (midId == flightId) {
      return mid;
    }

    if (midId < flightId) {
      left = mid + 1;
    }

    else {
      right = mid - 1;
    }
  }

  return -1;
}

Flight *Admin::searchFlightById(const string &flightId) {
  if (flights.empty()) {
    cout << "No flights available to search." << endl;
    return nullptr;
  }

  cout << "\n--- Searching for Flight (Binary Search Algorithm) ---" << endl;
  cout << "Searching for Flight ID: " << flightId << endl;

  vector<Flight> sortedFlights = flights;

  sort(sortedFlights.begin(), sortedFlights.end(),
       [](const Flight &a, const Flight &b) {
         return a.getFlightId() < b.getFlightId();
       });

  cout << "Sorted flights by ID for binary search:" << endl;
  for (const auto &flight : sortedFlights) {
    cout << "  " << flight.getFlightId() << endl;
  }

  int index = binarySearchById(sortedFlights, flightId);

  if (index != -1) {
    cout << "\nFlight FOUND!" << endl;
    cout << "\nFlight FOUND!" << endl;
    Flight::printHeader();
    sortedFlights[index].printRow();

    for (auto &flight : flights) {
      if (flight.getFlightId() == flightId) {
        return &flight;
      }
    }
  } else {
    cout << "\nFlight NOT FOUND!" << endl;
    return nullptr;
  }

  return nullptr;
}

void Admin::displayStatistics() const {
  cout << "\n========================================" << endl;
  cout << "   FLIGHT MANAGEMENT SYSTEM STATISTICS   " << endl;
  cout << "========================================" << endl;

  cout << "\nStatic Counters:" << endl;
  cout << "  Total Flights Created: " << Flight::getTotalFlights() << endl;
  cout << "  Total People Created: " << Person::getTotalPeople() << endl;

  cout << "\nCurrent Data:" << endl;
  cout << "  Flights in System: " << flights.size() << endl;
  cout << "  Aircraft in System: " << aircrafts.size() << endl;
  cout << "  People in System: " << people.size() << endl;

  double revenue = calculateTotalRevenue();
  cout << "\nFinancial Information:" << endl;
  cout << "  Total Revenue: $" << fixed << setprecision(2) << revenue << endl;

  if (!flights.empty()) {
    double avgPrice = revenue / flights.size();
    cout << "  Average Flight Price: $" << fixed << setprecision(2) << avgPrice
         << endl;
  }

  cout << "========================================\n" << endl;
}

void Admin::demonstrateAlgorithms() {
  cout << "\n========================================" << endl;
  cout << "  PHASE 2 FEATURES DEMONSTRATION" << endl;
  cout << "========================================" << endl;

  displayStatistics();

  if (flights.size() >= 2) {
    cout << "\n--- DEMONSTRATION: Friend Function (compareFlights) ---" << endl;

    compareFlights(flights[0], flights[1]);
  }

  if (flights.size() >= 2) {
    cout << "\n--- DEMONSTRATION: Operator Overloading ---" << endl;

    cout << "Testing == operator:" << endl;
    if (flights[0] == flights[1]) {
      cout << "  Flights are the same" << endl;
    } else {
      cout << "  Flights are different" << endl;
    }

    cout << "\nTesting < operator (comparing by price):" << endl;
    if (flights[0] < flights[1]) {
      cout << "  Flight " << flights[0].getFlightId() << " is cheaper than "
           << flights[1].getFlightId() << endl;
    } else {
      cout << "  Flight " << flights[1].getFlightId() << " is cheaper than "
           << flights[0].getFlightId() << endl;
    }

    cout << "\nTesting << operator (stream output):" << endl;
    cout << "  " << flights[0] << endl;
    cout << "  " << flights[1] << endl;
  }

  cout << "\n========================================" << endl;
  cout << "For sorting and searching demonstrations," << endl;
  cout << "please use the dedicated menu options." << endl;
  cout << "========================================\n" << endl;
}
