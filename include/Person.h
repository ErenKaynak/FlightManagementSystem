#pragma once
#include <string>

class Person {
protected:
    std::string id;
    std::string name;
    
    // REQUIREMENT: Static Variable - Track total number of people (pilots + workers + others)
    static int totalPeople;

public:
    Person(std::string id = "", std::string name = "");
    virtual ~Person();

    std::string getId() const;
    std::string getName() const;

    void setId(std::string id);
    void setName(std::string name);

    virtual void display() const;
    
    // REQUIREMENT: Static method to get total people count
    static int getTotalPeople() { return totalPeople; }
};
