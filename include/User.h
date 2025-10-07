#pragma once
#include <string>
using namespace std;

class User {
protected:
    string username;
    string password;
    string role;
public:
    User(string uname="", string pwd="", string r="") 
        : username(uname), password(pwd), role(r) {}

    virtual ~User() {} // 👈 important for polymorphic deletion

    bool checkLogin(string uname, string pwd); 
    string getRole() const { return role; }
    string getUsername() const { return username; }

    virtual void showMenu() = 0; 
};