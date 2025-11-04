#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>
using namespace std;

class Passenger {
private:
    int passengerID;
    string firstName;
    string lastName;
    string email;
    string contactNumber;

public:
    // Constructors
    Passenger();
    Passenger(int id, string fName, string lName, string mail, string contact);

    // Getters
    int getPassengerID() const;
    string getFirstName() const;
    string getLastName() const;
    string getEmail() const;
    string getContactNumber() const;

    // Setters
    void setPassengerID(int id);
    void setFirstName(string fName);
    void setLastName(string lName);
    void setEmail(string mail);
    void setContactNumber(string contact);

    // Methods
    void displayDetails() const;
    void updateContactInfo();
    
    // File operations
    string toFileString() const;
};

#endif