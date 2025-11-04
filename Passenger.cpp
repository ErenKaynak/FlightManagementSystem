#include "Passenger.h"
#include <iostream>

using namespace std;

// Constructors
Passenger::Passenger() : passengerID(0), firstName(""), lastName(""), email(""), contactNumber("") {}

Passenger::Passenger(int id, string fName, string lName, string mail, string contact)
    : passengerID(id), firstName(fName), lastName(lName), email(mail), contactNumber(contact) {}

// Getters
int Passenger::getPassengerID() const { return passengerID; }
string Passenger::getFirstName() const { return firstName; }
string Passenger::getLastName() const { return lastName; }
string Passenger::getEmail() const { return email; }
string Passenger::getContactNumber() const { return contactNumber; }

// Setters
void Passenger::setPassengerID(int id) { passengerID = id; }
void Passenger::setFirstName(string fName) { firstName = fName; }
void Passenger::setLastName(string lName) { lastName = lName; }
void Passenger::setEmail(string mail) { email = mail; }
void Passenger::setContactNumber(string contact) { contactNumber = contact; }

// Methods
void Passenger::displayDetails() const {
    cout << "Passenger ID: " << passengerID << endl;
    cout << "Name: " << firstName << " " << lastName << endl;
    cout << "Email: " << email << endl;
    cout << "Contact: " << contactNumber << endl;
}

void Passenger::updateContactInfo() {
    cout << "Enter new email: ";
    cin.ignore();
    getline(cin, email);
    cout << "Enter new contact number: ";
    getline(cin, contactNumber);
    cout << "Contact information updated successfully!" << endl;
}

string Passenger::toFileString() const {
    return to_string(passengerID) + "," + firstName + "," + lastName + "," + email + "," + contactNumber;
}