#include "User.h"
#include <iostream>

using namespace std;

// Constructors
User::User() : username(""), password("") {}

User::User(string uname, string pass) : username(uname), password(pass) {}

// Getters
string User::getUsername() const { return username; }
string User::getPassword() const { return password; }

// Setters
void User::setUsername(string uname) { username = uname; }
void User::setPassword(string pass) { password = pass; }

// Methods
void User::displayDetails() const {
    cout << "Username: " << username << endl;
}

bool User::login(string uname, string pass) {
    if (username == uname && password == pass) {
        cout << "Login successful!" << endl;
        return true;
    }
    cout << "Login failed. Invalid credentials." << endl;
    return false;
}

void User::logout() {
    cout << "User logged out successfully." << endl;
}