#include "Admin.h"
#include "Person.h"
#include "Worker.h"
#include <iostream>
#include <vector>

void Admin::addWorker() {
    std::string id, name, task;
    std::cout << "Enter Worker ID: ";
    std::getline(std::cin, id);
    std::cout << "Enter Worker Name: ";
    std::getline(std::cin, name);
    people.push_back(new Worker(id, name, ""));
    savePeopleToFile();
    std::cout << "Worker added successfully." << std::endl;
}

void Admin::assignTaskToWorker() {
    std::string workerId, task;
    std::cout << "Enter Worker ID: ";
    std::getline(std::cin, workerId);
    int personIndex = findPersonIndex(workerId);
    if (personIndex == -1) {
        std::cout << "Worker not found." << std::endl;
        return;
    }

    if (Worker* worker = dynamic_cast<Worker*>(people[personIndex])) {
        std::cout << "Enter task: ";
        std::getline(std::cin, task);
        worker->setTask(task);
        savePeopleToFile();
        std::cout << "Task assigned successfully." << std::endl;
    } else {
        std::cout << "This person is not a worker." << std::endl;
    }
}

void Admin::viewAllWorkers() {
    std::cout << "--- All Workers ---" << std::endl;
    for (Person* p : people) {
        if (Worker* worker = dynamic_cast<Worker*>(p)) {
            worker->display(true);
        }
    }
    std::cout << "---------------------" << std::endl;
}

