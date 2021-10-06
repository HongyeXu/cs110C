#ifndef LIST_H
#define LIST_H

class List
{
private:
    static const int CHUNK_SIZE = 10;
    int* list;
    int numItems;
    int maxItems;
public:
    // default constructor and destructor
    List()
    {
        numItems = 0; maxItems = CHUNK_SIZE;
        list = new int[CHUNK_SIZE];
    }
    ~List()
    {
        delete[] list;
    }

    // list member functions
    bool isEmpty()  const { return numItems == 0; }
    int getLength() const { return numItems; }
    bool insert(int pos, const int& item);
    bool remove(int pos);

    // clear the list
    // clear can simply set numItems to zero.  The array list may still contain
    // items already inserted into the list, but since numItems is zero, there
    // isn't any way to get at them using getEntry() or setEntry()
    void clear() { numItems = 0; }

    // return entry at postion pos
    // throw invalid_argument if pos<1 or pos>getLength()
    int getEntry(int pos) const;

    // set entry at postion pos to item
    // throw invalid_argument if pos<1 or pos>getLength()
    void setEntry(int pos, const int& item);
    bool linearSearch(int value);
};

#endif
