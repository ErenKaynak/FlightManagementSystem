#include "../include/Admin.h"
#include <iostream>
using namespace std;

// Worker Management Functions

void Admin::addWorker() {
    string workerId, name;
    cout << "\n--- Add New Worker ---\n";
    cout << "Enter Worker ID: ";
    getline(cin, workerId);
    cout << "Enter worker name: ";
    getline(cin, name);

    Worker worker(workerId, name, "");
    workers.push_back(worker);
    saveWorkersToFile();
    cout << "Worker added successfully!\n";
}

void Admin::viewAllWorkers() {
    cout << "\n--- All Workers ---\n";
    if (workers.empty()) {
        cout << "No workers found.\n";
        return;
    }
    for (const auto& worker : workers) {
        worker.display();
    }
}

void Admin::assignTaskToWorker() {
    int workerChoice;
    string task;
    cout << "\n--- Assign Task to Worker ---\n";
    
    if (workers.empty()) {
        cout << "No workers available. Please add workers first.\n";
        return;
    }

    cout << "\n--- Available Workers ---\n";
    for (size_t i = 0; i < workers.size(); i++) {
        cout << (i + 1) << ". ";
        workers[i].display();
    }
    cout << "Select worker number: ";
    cin >> workerChoice;
    cin.ignore(); // Clear newline

    if (workerChoice < 1 || workerChoice > static_cast<int>(workers.size())) {
        cout << "Invalid worker selection!\n";
        return;
    }

    cout << "Enter task description: ";
    getline(cin, task);

    workers[workerChoice - 1].assignTask(task);
    saveWorkersToFile();
    cout << "Task assigned successfully!\n";
}

