#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include "User.h"

using namespace std;

class Admin : public User {
private:
    string adminID;
    
public:
    // Constructors
    Admin();
    Admin(string username, string password, string id);
    
    // Getters
    string getAdminID() const;
    
    // Setters
    void setAdminID(string id);
    
    // Admin functions
    void adminAddFlight();
    void adminRemoveFlight();
    void viewAllFlights();
    void viewAllBookings();
    
    // Override from User class
    void displayDetails() const override;
    bool authenticate(string password) const;
};

#endifß