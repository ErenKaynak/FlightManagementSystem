#pragma once
#include <string>
using namespace std;

class Worker {
private:
    string workerId;
    string name;
    string task;

public:
    Worker(string id="", string n="", string t="") 
        : workerId(id), name(n), task(t) {}

    void display() const;
    void assignTask(string t) { task = t; }

    // Getters
    string getWorkerId() const { return workerId; }
    string getName() const { return name; }
    string getTask() const { return task; }

    // Setters
    void setWorkerId(string id) { workerId = id; }
    void setName(string n) { name = n; }
    void setTask(string t) { task = t; }
};

