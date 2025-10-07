#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "/Users/erenkaynak/Desktop/Documents/GitHub/FlightManagementSystem/include/User.h"
using namespace std;

// ===== Subclasses for different roles =====
class Passenger : public User {
public:
    Passenger(string u, string p) : User(u,p,"Passenger") {}
    void showMenu() override {
        cout << "\n--- Passenger Menu ---\n";
        cout << "1. Search Flights\n2. Book Ticket\n3. Logout\n";
    }
};

class Admin : public User {
public:
    Admin(string u, string p) : User(u,p,"Admin") {}
    void showMenu() override {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Manage Flights\n2. Manage Staff\n3. Reports\n4. Logout\n";
    }
};

class Staff : public User {
public:
    Staff(string u, string p) : User(u,p,"Staff") {}
    void showMenu() override {
        cout << "\n--- Staff Menu ---\n";
        cout << "1. Assigned Flights\n2. Logout\n";
    }
};

// ===== Load users from file =====
vector<User*> loadUsers(const string &filename) {
    vector<User*> users;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string uname, pwd, role;
        getline(ss, uname, ',');
        getline(ss, pwd, ',');
        getline(ss, role, ',');

        if (role == "Passenger") users.push_back(new Passenger(uname, pwd));
        else if (role == "Admin") users.push_back(new Admin(uname, pwd));
        else if (role == "Staff") users.push_back(new Staff(uname, pwd));
    }
    return users;
}

// ===== Login function =====
User* login(vector<User*> &users) {
    string uname, pwd;
    cout << "Username: "; cin >> uname;
    cout << "Password: "; cin >> pwd;

    for (auto u : users) {
        if (u->checkLogin(uname, pwd)) {
            cout << "Login successful as " << u->getRole() << "\n";
            return u;
        }
    }
    cout << "Invalid credentials!\n";
    return nullptr;
}

// ===== Main program =====
int main() {
    vector<User*> users = loadUsers("../data/users.txt");
    int choice;

    do {
        cout << "\n=== Flight Management System ===\n";
        cout << "1. Login\n";
        cout << "2. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        if (choice == 1) {
            User* u = login(users);
            if (u) {
                int dashboardChoice;
                do {
                    u->showMenu();  // polymorphic menu
                    cout << "Choose: ";
                    cin >> dashboardChoice;

                    switch(dashboardChoice) {
                        case 1: cout << "Feature coming soon...\n"; break;
                        case 2: cout << "Another feature...\n"; break;
                        case 3: cout << "Logging out...\n"; break;
                    }
                } while(dashboardChoice != 3); // 3 = logout
            }
        }
    } while(choice != 2);

    for (auto u : users) delete u;
    return 0;
}