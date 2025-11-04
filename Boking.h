#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include "Passenger.h"
#include "Flight.h"

using namespace std;

class Booking {
private:
    int bookingID;
    Passenger passenger;
    Flight flight;
    string seatNumber;
    string bookingStatus;

public:
    // Constructors
    Booking();
    Booking(int id, Passenger p, Flight f, string seat);

    // Getters
    int getBookingID() const;
    Passenger getPassenger() const;
    Flight getFlight() const;
    string getSeatNumber() const;
    string getBookingStatus() const;

    // Setters
    void setBookingStatus(string status);

    // Methods
    void confirmBooking();
    void cancelBooking();
    void displayBookingDetails() const;
    
    // File operations
    string toFileString() const;
    static Booking fromFileString(const string& line);
    
    // Friend class to allow setting status
    friend class FlightDatabase;
};

#endif