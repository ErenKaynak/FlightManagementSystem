#pragma once
#include "Person.h"
#include <string>

class Worker : public Person {
private:
    std::string task;

public:
    using Person::display;
    Worker(std::string id = "", std::string n = "", std::string t = "");

    void display(bool detailed = true) const;
    void assignTask(std::string t);

    // Getter
    std::string getTask() const;

    // Setter
    void setTask(std::string t);
};

