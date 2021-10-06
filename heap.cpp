/*
This program tracks patients entering and leaving a hospital 
emergency room by implementing a heap. Each Patient has a 
priority and data.  For this assignment, each Patient in the heap 
will be a string.
Assignment 11 - Emergency Room
Hongye Xu, CS 110C
*/

#include <iostream>
using namespace std;

class Heap
{
  private:
    static const int maxSize = 100;
    string patients[maxSize];
    int itemCount;
  public:
    Heap();
    bool add(string newPatient);
    string peekTop();
    bool remove();
    void heapRebuild(int root, string patients[], int itemCount);
};

Heap::Heap()
{
  itemCount = 0;
}

bool Heap::add(string newData)
{
  if (itemCount == maxSize)
  {
    cout << "Heap is full!\n";
    return false;
  }

  patients[itemCount] = newData;

  int newDataIndex = itemCount;
  bool inPlace = false;

  while ((newDataIndex > 0) && !inPlace) 
  {
    int parentIndex = (newDataIndex - 1) / 2;
    if (patients[newDataIndex] < patients[parentIndex])
    {
      inPlace = true;
    }
    else
    {
      string temp = patients[newDataIndex];
      patients[newDataIndex] = patients[parentIndex];
      patients[parentIndex] = temp;

      newDataIndex = parentIndex;     
    }
  }
  itemCount++;
  return true;
}


string Heap::peekTop()
{
  return patients[0];
}

bool Heap::remove()
{
  if (itemCount == 0)
    return false;
  patients[0] = patients[itemCount - 1];
  itemCount--;
  heapRebuild(0, patients, itemCount);
  return true;
}

void Heap::heapRebuild(int rootIndex, string patients[],int itemCount)
{
  if ((2 * rootIndex + 1) < itemCount) //If the root is not a leaf
  {
    //Root must have a left child. Assume it is the larger child
    int largerChildIndex = 2 * rootIndex + 1; //left child index

    if (2 * rootIndex + 2 < itemCount) //if root has a right child
    {
      int rightChildIndex = 2 * rootIndex + 2;
               
      if (patients[rightChildIndex] > patients[largerChildIndex])
      {
        largerChildIndex = rightChildIndex;
      }
    }

    //If the item in the root is smaller than the item in the larger
    //child, swap patients
    if (patients[rootIndex] < patients[largerChildIndex])
    {
      string temp = patients[rootIndex];
      patients[rootIndex] = patients[largerChildIndex];
      patients[largerChildIndex] = temp;

      //Transform the semiheap rooted at largerChildHeap into a heap
      heapRebuild(largerChildIndex, patients, itemCount);
    }
  }
}


int main() 
{
  Heap ER;

  ER.add("5 Bob");
  ER.add("9 Mary");
  ER.add("1 Max");
  cout << ER.peekTop() << " will now see the doctor.\n";
  ER.remove();
  ER.add("3 Julio");
  ER.add("7 Stacy");
  ER.add("4 Paul");
  ER.add("2 Reiko");
  ER.add("6 Jennifer");
  ER.add("5 Chang");
  cout << ER.peekTop() << " will now see the doctor.\n";
  ER.remove();
  cout << ER.peekTop() << " will now see the doctor.\n";
  ER.remove();
  cout << ER.peekTop() << " will now see the doctor.\n";
  ER.remove();  
  return 0;
}



/*SAMPLE OUTPUT
[hxu65@hills ~]$ ./a.out
9 Mary will now see the doctor.
7 Stacy will now see the doctor.
6 Jennifer will now see the doctor.
5 Chang will now see the doctor.
*/