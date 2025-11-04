#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
private:
    string username;
    string password;

public:
    // Constructors
    User();
    User(string uname, string pass);

    // Getters
    string getUsername() const;
    string getPassword() const;

    // Setters
    void setUsername(string uname);
    void setPassword(string pass);

    // Virtual methods
    virtual void displayDetails() const;
    virtual bool login(string uname, string pass);
    virtual void logout();
};

#endif