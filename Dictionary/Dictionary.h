
#ifndef _DICTIONARY
#define _DICTIONARY
#include "Person.h"
#include <iostream>
using namespace std;

class Dictionary
{
private:
    static const int maxSize = 20;
    Person sortedArray[maxSize];
    int numberOfEntries;

public:
    Dictionary();
    bool sortedAdd(Person input);
    bool removeEntry(Person input);
    bool searchName(string name);
    void searchForMonth(string month);
    void display();
    int getNumberOfEntries()
        {return numberOfEntries;}
    int binarySearch(Person array[], int numberOfEntries, string name);
    int getPosition(Person input);
};

#endif