#pragma once
#include <string>
using namespace std;

class Aircraft {
private:
    string aircraftId;
    string model;
    int capacity;

public:
    Aircraft(string id="", string m="", int cap=0) : aircraftId(id), model(m), capacity(cap) {}

    void display() const;

    
    string getAircraftId() const { return aircraftId; }
    string getModel() const { return model; }
    int getCapacity() const { return capacity; }

    
    void setAircraftId(string id) { aircraftId = id; }
    void setModel(string m) { model = m; }
    void setCapacity(int cap) { capacity = cap; }
};
