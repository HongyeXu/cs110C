#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <string>
using namespace std;

class Person
{
private:
    string name;
    string birthday;
    string birthdayMonth;

public:
    Person();
    Person(string personName, string personBirthday);
    string getName()
        {return name;}
    string getBirthday()
        {return birthday;}
    string getBirthdayMonth()
        {return birthdayMonth;}
    bool operator==(const Person& p);
    bool operator!=(const Person& p);
    bool operator<(const Person& p);
};

#endif