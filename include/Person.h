#pragma once
#include <string>

class Person {
protected:
    std::string id;
    std::string name;

public:
    Person(std::string id = "", std::string name = "");
    virtual ~Person();

    std::string getId() const;
    std::string getName() const;

    void setId(std::string id);
    void setName(std::string name);

    virtual void display() const;
};
