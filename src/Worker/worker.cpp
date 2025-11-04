#include "../include/Worker.h"
#include <iostream>

void Worker::display() const {
    cout << "Worker ID: " << workerId 
         << ", Name: " << name;
    if (!task.empty()) {
        cout << ", Task: " << task;
    }
    cout << endl;
}

