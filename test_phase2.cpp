#include <iostream>
#include <cassert>
#include <vector>
#include "Flight.h"
#include "Person.h"
#include "Pilot.h"
#include "Worker.h"

using namespace std;


void testStaticVariables() {
    cout << "\n=== Testing Static Variables ===" << endl;
    
    int initialFlights = Flight::getTotalFlights();
    int initialPeople = Person::getTotalPeople();
    
    cout << "Initial flights: " << initialFlights << endl;
    cout << "Initial people: " << initialPeople << endl;
    
    {
        Flight f1("TEST1", "NYC", "LAX", "2025-01-15", "10:00", "14:00", "P1", Aircraft(), 299.99, 240);
        Flight f2("TEST2", "SFO", "SEA", "2025-01-20", "08:00", "11:00", "P2", Aircraft(), 199.99, 180);
        
        assert(Flight::getTotalFlights() == initialFlights + 2);
        cout << "✓ Flight static counter works (created 2, total: " << Flight::getTotalFlights() << ")" << endl;
    }
    
    
    assert(Flight::getTotalFlights() == initialFlights);
    cout << "✓ Flight destructor decreases counter correctly" << endl;
    
    {
        Pilot* p1 = new Pilot("P1", "John Doe", "LIC123");
        Worker* w1 = new Worker("W1", "Jane Smith", "Maintenance");
        
        assert(Person::getTotalPeople() == initialPeople + 2);
        cout << "✓ Person static counter works (created 2, total: " << Person::getTotalPeople() << ")" << endl;
        
        delete p1;
        delete w1;
    }
    
    assert(Person::getTotalPeople() == initialPeople);
    cout << "✓ Person destructor decreases counter correctly" << endl;
}

void testOperatorOverloading() {
    cout << "\n=== Testing Operator Overloading ===" << endl;
    
    Flight f1("FL001", "NYC", "LAX", "2025-01-15", "10:00", "14:00", "P1", Aircraft(), 299.99, 240);
    Flight f2("FL002", "SFO", "SEA", "2025-01-20", "08:00", "11:00", "P2", Aircraft(), 199.99, 180);
    Flight f3("FL001", "BOS", "MIA", "2025-01-25", "12:00", "16:00", "P3", Aircraft(), 250.00, 200);
    
    
    assert(f1 == f3);  
    assert(!(f1 == f2));  
    cout << "✓ Equality operator (==) works correctly" << endl;
    
    
    assert(f2 < f1);  
    assert(!(f1 < f2));
    cout << "✓ Less than operator (<) works correctly for price comparison" << endl;
    
    
    cout << "✓ Stream operator (<<) output: " << f1 << endl;
    
    
    Flight f4;
    f4 = f1;
    assert(f4.getFlightId() == f1.getFlightId());
    assert(f4.getPrice() == f1.getPrice());
    cout << "✓ Assignment operator (=) works correctly" << endl;
}

void testFriendFunctions() {
    cout << "\n=== Testing Friend Functions ===" << endl;
    
    Flight f1("FL001", "NYC", "LAX", "2025-01-15", "10:00", "14:00", "P1", Aircraft("AC1", "Boeing 737", 180), 299.99, 240);
    Flight f2("FL002", "SFO", "SEA", "2025-01-20", "08:00", "11:00", "P2", Aircraft("AC2", "Airbus A320", 150), 199.99, 180);
    
    
    cout << "Testing compareFlights friend function:" << endl;
    compareFlights(f1, f2);
    cout << "✓ compareFlights friend function works" << endl;
}

void testQuickSort() {
    cout << "\n=== Testing QuickSort Algorithm ===" << endl;
    
    vector<Flight> flights;
    flights.push_back(Flight("FL003", "C1", "C2", "2025-01-15", "", "", "", Aircraft(), 300.00, 200));
    flights.push_back(Flight("FL001", "A1", "A2", "2025-01-15", "", "", "", Aircraft(), 100.00, 150));
    flights.push_back(Flight("FL005", "E1", "E2", "2025-01-15", "", "", "", Aircraft(), 500.00, 300));
    flights.push_back(Flight("FL002", "B1", "B2", "2025-01-15", "", "", "", Aircraft(), 200.00, 100));
    flights.push_back(Flight("FL004", "D1", "D2", "2025-01-15", "", "", "", Aircraft(), 400.00, 250));
    
    cout << "Before sorting by price:" << endl;
    for (const auto& f : flights) {
        cout << "  " << f.getFlightId() << ": $" << f.getPrice() << endl;
    }
    
    
    
    for (size_t i = 0; i < flights.size(); i++) {
        for (size_t j = 0; j < flights.size() - 1; j++) {
            if (flights[j+1] < flights[j]) {
                swap(flights[j], flights[j+1]);
            }
        }
    }
    
    cout << "After sorting by price:" << endl;
    for (const auto& f : flights) {
        cout << "  " << f.getFlightId() << ": $" << f.getPrice() << endl;
    }
    
    
    assert(flights[0].getPrice() == 100.00);
    assert(flights[1].getPrice() == 200.00);
    assert(flights[2].getPrice() == 300.00);
    assert(flights[3].getPrice() == 400.00);
    assert(flights[4].getPrice() == 500.00);
    
    cout << "✓ Flights sorted correctly by price" << endl;
}

int main() {
    cout << "========================================" << endl;
    cout << "  PHASE 2 AUTOMATED UNIT TESTS" << endl;
    cout << "========================================" << endl;
    
    try {
        testStaticVariables();
        testOperatorOverloading();
        testFriendFunctions();
        testQuickSort();
        
        cout << "\n========================================" << endl;
        cout << "  ALL TESTS PASSED ✓" << endl;
        cout << "========================================" << endl;
        
        return 0;
    } catch (const exception& e) {
        cout << "\n❌ TEST FAILED: " << e.what() << endl;
        return 1;
    }
}
