#include "Worker.h"
#include <iostream>

Worker::Worker(std::string id, std::string n, std::string t)
    : Person(id, n), task(t) {}

void Worker::display(bool detailed) const {
    if (detailed) {
        std::cout << "Worker ID: " << getId() << ", Name: " << getName();
        if (!task.empty()) {
            std::cout << ", Task: " << task;
        }
        std::cout << std::endl;
    } else {
        std::cout << "Worker ID: " << getId() << ", Name: " << getName() << std::endl;
    }
}

void Worker::assignTask(std::string t) {
    task = t;
}

std::string Worker::getTask() const {
    return task;
}

void Worker::setTask(std::string t) {
    task = t;
}

