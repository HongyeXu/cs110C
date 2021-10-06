#include "Person.h"
#include <iostream>
using namespace std;

Person::Person()
{
    name = "";
    birthday = "";
    birthdayMonth = "";
}

Person::Person(string personName, string personBirthday)
{
    name = personName;
    birthday = personBirthday;
    birthdayMonth = personBirthday.substr(0, 3);
}

bool Person::operator==(const Person& p)
{
    if (name == p.name && birthday == p.birthday)
        return true;
    else
        return false;
}

bool Person::operator!=(const Person& p)
{
    if (name != p.name && birthday != p.birthday)
        return true;
    else
        return false;
}


bool Person::operator<(const Person& p)
{
    if (name < p.name)
        return true;
    else
        return false;
}