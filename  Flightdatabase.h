#ifndef FLIGHTDATABASE_H
#define FLIGHTDATABASE_H

#include <vector>
#include <string>
#include "Flight.h"
#include "Booking.h"

using namespace std;

class FlightDatabase {
private:
    static FlightDatabase* instance;
    vector<Flight> allFlights;
    vector<Booking> allBookings;

    // Private constructor for Singleton
    FlightDatabase();

public:
    // Singleton instance
    static FlightDatabase* getInstance();

    // Flight management
    void addFlight(const Flight& flight);
    bool removeFlight(const string& flightNumber);
    Flight* findFlightByID(const string& flightNumber);
    vector<Flight*> searchFlights(const string& origin, const string& destination);
    void displayAllFlights();

    // Booking management
    void addBooking(const Booking& booking);
    Booking* findBookingByID(int bookingID);
    vector<Booking*> findBookingsByPassengerName(const string& firstName, const string& lastName);
    void displayAllBookings();
    int generateBookingID();

    // File operations
    void saveDataToFile();
    void loadDataFromFile();
};

#endif