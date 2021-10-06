#include "List.h"
#include <iostream>
#include <stdexcept>
using namespace std;


bool List::insert(int pos, const int& item)
{
    bool canAdd;
    if (numItems >= maxItems)
    {
        int* originalList = list;

        //increase size, and copy
        maxItems += CHUNK_SIZE;
        list = new int[maxItems];
        for (int i = 0; i < numItems; i++)
        {
            list[i] = originalList[i];
        }

        delete[] originalList;
    }

    canAdd = ((pos > 0) && (pos <= numItems + 1) && (numItems < maxItems));
    if (canAdd)
    {
        // first, we have to move everything after our insertion point over one
        // position to make room for our new item.  start at the back of the list.
        // don't forget arrays start at postion zero and our list ADT starts at
        // position 1.
        for (int i = numItems; i >= pos; i--)
            list[i] = list[i - 1];

        // now put our item at position pos-1
        list[pos - 1] = item;

        numItems++;
    }

    return canAdd;
}




int List::getEntry(int pos) const
{
    if ((pos < 1) || (pos > getLength()))
    {
        throw invalid_argument("ERROR: getEntry() using invalid position");
    }
    return list[pos - 1];
}



void List::setEntry(int pos, const int& item)
{
    if ((pos < 1) || (pos > getLength()))
    {
        throw invalid_argument("ERROR: invalid position");
    }
    list[pos - 1] = item;
}


bool List::remove(int pos)
{
    bool canRemove;
    canRemove = ((pos > 0) && (pos <= numItems) && (numItems <= maxItems));
    if (canRemove)
    {
        for (int i = pos - 1; i < numItems - 1; i++)
        {
            list[i] = list[i + 1];
        }
        numItems--;
    }

    return canRemove;
}



bool List::linearSearch(int value)
{
    int pos = 0;
    bool isFound = false;
    while (!isFound && pos < numItems)
    {
        if (list[pos] == value)
            isFound = true;
        pos++;
    }
    return isFound;
}