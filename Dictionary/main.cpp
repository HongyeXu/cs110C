/*
This program  implement a dictionary to track the name and 
birthday of your friends and relatives. It has the following
functions, add an entry, remove an entry, search the dictionary 
for the birthday for a given name, display the name and birthday
of every entry in the dictionary, display everyone in the
dictionary who was born in a given month.
Hongye Xu, CS 110C
Assignment 12 - Birthdays
*/

#include <iostream>
using namespace std;
#include "Person.h"
#include "Dictionary.h"


int main()
{
    Person entry1("Ben", "Jun 18, 2011");
    Person entry2("Charlie", "Dec 21, 1990");
    Person entry3("Amy", "Jun 23, 2005");

    Dictionary birthdayBook;
    birthdayBook.sortedAdd(entry1);
    birthdayBook.sortedAdd(entry2);
    birthdayBook.sortedAdd(entry3);

    cout << "Here is the dictionary:\n";
    birthdayBook.display();

    cout << endl;
    cout << "Search Ben in the dictionary:\n";
    birthdayBook.searchName("Ben");

    
    Person entry4("Danny", "Dec 21, 1990");
    Person entry5("Emily", "Jun 23, 2005");
    birthdayBook.removeEntry(entry2);
    birthdayBook.removeEntry(entry3);
    birthdayBook.sortedAdd(entry4);
    birthdayBook.sortedAdd(entry5);

    cout << endl;
    cout << "Search for June:\n";
    birthdayBook.searchForMonth("Jun");
    return 0;
}

/*SAMPLE OUT
[hxu65@hills ~]$ ./a.out
Here is the dictionary:
Amy has a birthday on Jun 23, 2005
Ben has a birthday on Jun 18, 2011
Charlie has a birthday on Dec 21, 1990

Search Ben in the dictionary:
Ben has a birthday on Jun 18, 2011

Search for June:
Ben has a birthday in Jun
Emily has a birthday in Jun
*/