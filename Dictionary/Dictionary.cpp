#include "Dictionary.h"
#include "Person.h"
#include <cmath>
#include <iostream>
using namespace std;

Dictionary::Dictionary()
{
    numberOfEntries = 0;
}

bool Dictionary::sortedAdd(Person input)
{
    bool added = false;
    int newPosition = fabs(getPosition(input)); //get the proper position
    bool canAdd = (newPosition >= 1) && (newPosition <= numberOfEntries + 1);
    if (canAdd)
    {
        //move the greater elements down
        for (int i = numberOfEntries; i >= newPosition; i--)
        {
            sortedArray[i] = sortedArray[i - 1];
        }
        sortedArray[newPosition - 1] = input;
        numberOfEntries++;
        return true;
    }
    else
    {
        cout << "Can't add anymore! Dictionary is full!\n";
        return false;
    }
}

//This removes the first occurence of input in the Dictionary if exists
bool Dictionary::removeEntry(Person input)
{
    int index = 0;
    Person target = sortedArray[index];
    while (target != input && index != (getNumberOfEntries() - 1)) //need to make sure you update target every iteration
    {
        index++;
        target = sortedArray[index];
    }
    if (sortedArray[index] == input)
    {
        //Shift over each element by 1
        for (int i = index; i < getNumberOfEntries() - 1; i++) 
        {
            sortedArray[i] = sortedArray[(i + 1)];
        }
        numberOfEntries--;
        return true;
    }
    else
    {
        cout << input.getName() << " isn't in the dictionary!\n";
        return false;
    }
}

bool Dictionary::searchName(string name)
{
    int index = binarySearch(sortedArray, numberOfEntries, name);
    if (index == -1)
    {
        cout << name << " is not in the dictionary!\n";
        return false;
    }
    else
    {
        cout << name << " has a birthday on " <<
            sortedArray[index].getBirthday() << endl;
        return true;
    }
}

void Dictionary::searchForMonth(string month)
{
    for (int i = 0; i < numberOfEntries; i++)
    {
        if (sortedArray[i].getBirthdayMonth() == month)
        {
            cout << sortedArray[i].getName() << " has a birthday in "
                << month << endl;
        }
    }
}

void Dictionary::display()
{
    for (int i = 0; i < numberOfEntries; i++)
    {
        cout << sortedArray[i].getName() << " has a birthday on "
            << sortedArray[i].getBirthday() << endl;
    }
}

int Dictionary::binarySearch(Person theArray[], int size, string name)
{
    int first = 0, last = size - 1, middle;
    bool isFound = false;
    while (!isFound && first<=last)
    {
        middle = (first+last) / 2;
        if (theArray[middle].getName() == name)
            isFound = true;
        else if (theArray[middle].getName() > name) // lower half
            last = middle - 1;
        else
            first = middle + 1; // upper half
    }
    if (isFound)
        return  middle;
    else
        return -1;
}





int Dictionary::getPosition(Person entry)
{
    int position = 1;
    while ((position <= numberOfEntries) && (sortedArray[position - 1] < entry))
    {
        position ++;
    }

    if (position > numberOfEntries)
        return -position;
    else
    {
        if (sortedArray[position - 1] == entry)
            return position;
        else
            return -position;
    }
}