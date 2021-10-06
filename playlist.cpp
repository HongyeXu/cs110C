// An array-based list implementation to track songs in a playlist
// setEntry: replace item at position pos in the list with the new 
// parameter item.
// remove: remove the item at position pos
// insert: improved so that it dynamically allocates more memory 
// to the list to make room for the new item
// Assignment 2 - Playlist
// From Max Luttrell CS 110C
// Hongye Xu, CS 110C

#include <string>
#include <iostream>
#include <stdexcept>
using namespace std;


template<class ItemType>
class List
{
  private:
    static const int CHUNK_SIZE = 2;
    ItemType *list;
    int numItems;
    int maxItems;
  public:
    // default constructor and destructor
    List() 
      { numItems = 0; maxItems = CHUNK_SIZE;
        list = new ItemType[CHUNK_SIZE]; }
    ~List() 
      { delete [] list; }
    
    // list member functions
    bool isEmpty()  const { return numItems == 0; }
    int getLength() const { return numItems; }
    bool insert(int pos, const ItemType& item);
    bool remove(int pos);
    
    // clear the list
    // clear can simply set numItems to zero.  The array list may still contain
    // items already inserted into the list, but since numItems is zero, there
    // isn't any way to get at them using getEntry() or setEntry()
    void clear() { numItems = 0; }
    
    // return entry at postion pos
    // throw invalid_argument if pos<1 or pos>getLength()
    ItemType getEntry(int pos) const;
    
    // set entry at postion pos to item
    // throw invalid_argument if pos<1 or pos>getLength()
    void setEntry(int pos, const ItemType& item);
};



template<class ItemType>
bool List<ItemType>::insert(int pos, const ItemType& item)
{
  bool canAdd;
  if (numItems >= maxItems)
  {
    ItemType *originalList = list;
    
    //increase size, and copy
    maxItems += CHUNK_SIZE;
    list = new ItemType[maxItems];
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
    list[pos-1] = item;
        
    numItems++;
  }
    
  return canAdd;
}



template<class ItemType>
ItemType List<ItemType>::getEntry(int pos) const
{
  if ((pos < 1) || (pos > getLength())) 
  {
    throw invalid_argument("ERROR: getEntry() using invalid position");
  }
  return list[pos - 1];
}



// TODO: add implementations for setEntry() and remove() functions
template<class ItemType>
void List<ItemType>::setEntry(int pos, const ItemType& item)
{
  if ((pos < 1) || (pos > getLength()))
  {
    throw invalid_argument("ERROR: invalid position");
  }
  list[pos - 1] = item;
}



template<class ItemType>
bool List<ItemType>::remove(int pos)
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



// Utility function to input a track number with some input checking
// to make sure it's a number
int getTrack()
{
  bool inputCheck;
  int trackNumber;
    
  do
  {
    inputCheck = true;
    cout << "Please enter the track number you'd like to view: ";
    if (!(cin >> trackNumber))
    {
      cout << "Please enter numbers only.\n";
      cin.clear();
      cin.ignore(10000, '\n');
      inputCheck = false;
    }
  } while (!inputCheck);
  return trackNumber;
}



int main()
{/*
  List<string> songs;
  char goAgain = 'y';
  int trackNumber;
  string trackName;

  try
  {
    songs.setEntry(20, "Can it?");
  }
  catch (invalid_argument invErr)
  {
    cout << invErr.what() << endl;
  }
    
  songs.insert(1, "One More Saturday Night");
  songs.insert(1, "Friday I'm in Love");
  songs.insert(3, "Sunday Morning Coming Down");
  songs.insert(1, "California Love");

  songs.insert(3, "What's up");
  songs.insert(3, "Panda");

  songs.setEntry(2, "This Should Be Two");
  songs.remove(3);
  songs.remove(4);
    
  songs.insert(1, "California Love");
  songs.insert(2, "California Love");
  songs.insert(3, "California Love");
  songs.insert(4, "California Love");
  songs.insert(5, "California Love");
  songs.insert(6, "California Love");
  songs.insert(7, "California Love");
  songs.insert(8, "California Love");
  songs.insert(9, "California Love");
  songs.insert(10, "California Love");

  songs.insert(10, "X");

  
  cout << "Welcome!  There are " << songs.getLength() << " tracks.\n";
  while (goAgain != 'n')
  {
    trackNumber = getTrack();
    try
    {
      trackName = songs.getEntry(trackNumber);
    }
    catch (invalid_argument arg)
    {
      cout << arg.what() << endl;
      trackName = "No Track";
    }
    cout << "Your track name is " << trackName << endl;
    cout << "Go again? (y/n) ";
    cin >> goAgain;
  }
    */
      List<int> vertexSet;
    vertexSet.insert(1, 0);
  cout << "Rock on!\n";
  return 0;
}

/*SAMPLE OUTPUT
[hxu65@hills ~]$ ./a.out
ERROR: invalid position
Welcome!  There are 4 tracks.
Please enter the track number you'd like to view: 1
Your track name is California Love
Go again? (y/n) y
Please enter the track number you'd like to view: 2
Your track name is This Should Be Two
Go again? (y/n) y
Please enter the track number you'd like to view: 3
Your track name is What's up
Go again? (y/n) y
Please enter the track number you'd like to view: 4
Your track name is Sunday Morning Coming Down
Go again? (y/n) y
Please enter the track number you'd like to view: 5
ERROR: getEntry() using invalid position
Your track name is No Track
Go again? (y/n) n
Rock on!
*/
