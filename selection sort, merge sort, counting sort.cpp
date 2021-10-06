/*
This program contains three sorting algorithms: selection sort,
merge sort, and counting sort. There is a counter to the sort 
function to track the number of times that the function accesses
elements from the array you are sorting
Assignment 4 - Sort Efficiency
Hongye Xu, CS 110C
*/
#include <iostream>
using namespace std;
#include <cstdlib> 
#include <ctime> 


void displayArray(int theArray[], int size)
{
  for (int i = 0; i < size; i++)
  {
    cout << theArray[i] << " ";
  }   
  cout << endl;
}



void swapper(int &x, int &y)
{
  int temp = x;
  x = y;
  y = temp;
}




//O(n^2) sort: Selection Sort
void selectionSort(int theArray[], int size, int &selectionCounter)
{
  int min, minIndex;
  for (int i = 0; i < size - 1; i++)
  {
    min = theArray[i];
    selectionCounter++;
    minIndex = i;
    for (int j = i + 1; j < size; j++)
    {
      selectionCounter++;
      if (theArray[j] < min)  //replace the minimum value
      {
        minIndex = j;
        min = theArray[j];
        selectionCounter++;
      }
    }
    swapper(theArray[i], theArray[minIndex]);
    selectionCounter += 4;
  }
}




//O(n log n) sort: merge sort
void merge(int theArray[], int first, int mid, int last, int &mergeCounter)
{
  int tempArray[last + 1]; // Temporary array
  // Initialize the local indices to indicate the subarrays
  int first1 = first; // Beginning of first subarray
  int last1 = mid; // End of first subarray
  int first2 = mid + 1; // Beginning of second subarray
  int last2 = last; // End of second subarray
  // While both subarrays are not empty, copy the
  // smaller item into the temporary array
  int index = first1; // Next available location in tempArray
  while ((first1 <= last1) && (first2 <= last2))
  {
    // At this point, tempArray[first..index-1] is in order
    mergeCounter += 2;
    if (theArray[first1] <= theArray[first2])
    {
      tempArray[index] = theArray[first1];
      mergeCounter++;
      first1++;
    }
    else
    {
      tempArray[index] = theArray[first2];
      mergeCounter++;
      first2++;
    } // end if
    index++;
  } // end while
  // Finish off the first subarray, if necessary
  while (first1 <= last1)
  {
    // At this point, tempArray[first..index-1] is in order
    tempArray[index] = theArray[first1];
    mergeCounter++;
    first1++;
    index++;
  } // end while
  // Finish off the second subarray, if necessary
  while (first2 <= last2)
  {
    // At this point, tempArray[first..index-1] is in order
    tempArray[index] = theArray[first2];
    mergeCounter++;
    first2++;
    index++;
  } // end for
  // Copy the result back into the original array
  for (index = first; index <= last; index++)
  {
    theArray[index] = tempArray[index];
    mergeCounter++;
  }
} // end merge


void mergeSort(int theArray[], int first, int last, int &mergeCounter)
{
  if (first < last)
  {
    int mid = (first + last) / 2;
    // recursively sort first half of array
    mergeSort(theArray, first, mid, mergeCounter);
    // recursively sort second half of array
    mergeSort(theArray, mid + 1, last, mergeCounter);
    // merge sorted halves (first thru mid, and mid+1 thru last)
    merge(theArray, first, mid, last, mergeCounter);
  }
}
 



void countingSort(int theArray[], int size, int &countingSortCounter)
{
  int countSize = 101;  //in the range 0 to 100, inclusive
  int count[countSize];
  //initiate the count array with 0
  for (int i = 0; i < countSize; i++)
  {
    count[i] = 0;
  }

  //there is a number in the original array, then increment
  //the corresponding index in the count array
  for (int i = 0; i < size; i++)
  {
    count[theArray[i]]++; 
    countingSortCounter++; 
  }

  //store the count array back into the original array.  
  int position = 0;
  for (int i = 0; i < countSize; i++)
  {
    for (int j = count[i]; j > 0; j--) 
    {
      theArray[position] = i;  
      countingSortCounter++;
      position++;
    }
  }
}




int main()
{
  srand(time(0));
  int max = 100, min = 0;
  
  int selectionCounter = 0;
  int mergeCounter = 0;
  int countingSortCounter = 0;

  cout << "Selection sort with array size 8:\n";
  int arraySel8[8];
  for (int i = 0; i < 8; i++)
  {
    arraySel8[i] = (rand() % (max - min + 1)) + min; 
  }
  cout << "Initial array:\n";
  displayArray(arraySel8, 8);
  cout << "After selection sort:\n";
  selectionSort(arraySel8, 8, selectionCounter);
  displayArray(arraySel8, 8);
  cout << "The number of array accesses: " << selectionCounter << endl;

  
  selectionCounter = 0;
  cout << "\nSelection sort with array size 32:\n";
  int arraySel32[32];
  for (int i = 0; i < 32; i++)
  {
    arraySel32[i] = (rand() % (max - min + 1)) + min; 
  }
  cout << "Initial array:\n";
  displayArray(arraySel32, 32);
  cout << "After selection sort:\n";
  selectionSort(arraySel32, 32, selectionCounter);
  displayArray(arraySel32, 32);
  cout << "The number of array accesses: " << selectionCounter << endl;


  selectionCounter = 0;
  cout << "\nSelection sort with array size 128:\n";
  int arraySel128[128];
  for (int i = 0; i < 128; i++)
  {
    arraySel128[i] = (rand() % (max - min + 1)) + min; 
  }
  cout << "Initial array:\n";
  displayArray(arraySel128, 128);
  cout << "After selection sort:\n";
  selectionSort(arraySel128, 128, selectionCounter);
  displayArray(arraySel128, 128);
  cout << "The number of array accesses: " << selectionCounter << endl;

  cout << "\nMerge sort with array size 8:\n";
  int arrayMerge8[8];
  for (int i = 0; i < 8; i++)
  {
    arrayMerge8[i] = (rand() % (max - min + 1)) + min; 
  }
  cout << "Initial array:\n";
  displayArray(arrayMerge8, 8);
  cout << "After merge sort:\n";
  mergeSort(arrayMerge8, 0, 7, mergeCounter);
  displayArray(arrayMerge8, 8);
  cout << "The number of array accesses: " << mergeCounter << endl;

  

  mergeCounter = 0;
  cout << "\nMerge sort with array size 32:\n";
  int arrayMerge32[32];
  for (int i = 0; i < 32; i++)
  {
    arrayMerge32[i] = (rand() % (max - min + 1)) + min; 
  }
  cout << "Initial array:\n";
  displayArray(arrayMerge32, 32);
  cout << "After merge sort:\n";
  mergeSort(arrayMerge32, 0, 31, mergeCounter);
  displayArray(arrayMerge32, 32);
  cout << "The number of array accesses: " << mergeCounter << endl;



  mergeCounter = 0;
  cout << "\nMerge sort with array size 128:\n";
  int arrayMerge128[128];
  for (int i = 0; i < 128; i++)
  {
    arrayMerge128[i] = (rand() % (max - min + 1)) + min; 
  }
  cout << "Initial array:\n";
  displayArray(arrayMerge128, 128);
  cout << "After merge sort:\n";
  mergeSort(arrayMerge128, 0, 127, mergeCounter);
  displayArray(arrayMerge128, 128);
  cout << "The number of array accesses: " << mergeCounter << endl;


  cout << "\nCounting sort with array size 8:\n";
  int arrayCounting8[8];
  for (int i = 0; i < 8; i++)
  {
    arrayCounting8[i] = (rand() % (max - min + 1)) + min; 
  }
  cout << "Initial array:\n";
  displayArray(arrayCounting8, 8);
  cout << "After counting sort:\n";
  countingSort(arrayCounting8, 8, countingSortCounter);
  displayArray(arrayCounting8, 8);
  cout << "The number of array accesses: " << countingSortCounter << endl;

  

  countingSortCounter = 0;
  cout << "\nCounting sort with array size 32:\n";
  int arrayCounting32[32];
  for (int i = 0; i < 32; i++)
  {
    arrayCounting32[i] = (rand() % (max - min + 1)) + min; 
  }
  cout << "Initial array:\n";
  displayArray(arrayCounting32, 32);
  cout << "After counting sort:\n";
  countingSort(arrayCounting32, 32, countingSortCounter);
  displayArray(arrayCounting32, 32);
  cout << "The number of array accesses: " << countingSortCounter << endl;


  countingSortCounter = 0;
  cout << "\nCounting sort with array size 128:\n";
  int arrayCounting128[128];
  for (int i = 0; i < 128; i++)
  {
    arrayCounting128[i] = (rand() % (max - min + 1)) + min; 
  }
  cout << "Initial array:\n";
  displayArray(arrayCounting128, 128);
  cout << "After counting sort:\n";
  countingSort(arrayCounting128, 128, countingSortCounter);
  displayArray(arrayCounting128, 128);
  cout << "The number of array accesses: " << countingSortCounter << endl;

  return 0;
}

/*SAMPLE OUTPUT
[hxu65@hills ~]$ ./a.out
Selection sort with array size 8:
Initial array:
39 93 42 11 30 79 70 7 
After selection sort:
7 11 30 39 42 70 79 93 
The number of array accesses: 71

Selection sort with array size 32:
Initial array:
74 51 41 1 82 99 5 63 89 58 41 37 85 4 85 11 28 66 19 100 78 21 57 83 13 65 95 43 10 30 16 84 
After selection sort:
1 4 5 10 11 13 16 19 21 28 30 37 41 41 43 51 57 58 63 65 66 74 78 82 83 84 85 85 89 95 99 100 
The number of array accesses: 720

Selection sort with array size 128:
Initial array:
81 58 51 62 56 22 92 45 80 32 82 31 2 32 8 30 65 27 30 8 48 53 91 28 85 85 37 95 81 54 78 62 11 95 90 33 17 47 44 63 45 93 60 48 24 69 78 55 62 74 63 77 94 54 71 78 4 7 72 86 61 15 13 38 9 69 38 93 16 82 22 61 74 82 8 65 16 87 19 45 60 83 21 53 2 92 30 73 65 68 24 93 83 37 97 93 73 34 51 89 83 73 49 56 21 58 87 3 10 6 48 36 55 35 56 23 93 52 96 58 20 20 50 2 23 46 61 96 
After selection sort:
2 2 2 3 4 6 7 8 8 8 9 10 11 13 15 16 16 17 19 20 20 21 21 22 22 23 23 24 24 27 28 30 30 30 31 32 32 33 34 35 36 37 37 38 38 44 45 45 45 46 47 48 48 48 49 50 51 51 52 53 53 54 54 55 55 56 56 56 58 58 58 60 60 61 61 61 62 62 62 63 63 65 65 65 68 69 69 71 72 73 73 73 74 74 77 78 78 78 80 81 81 82 82 82 83 83 83 85 85 86 87 87 89 90 91 92 92 93 93 93 93 93 94 95 95 96 96 97 
The number of array accesses: 9181

Merge sort with array size 8:
Initial array:
47 12 84 29 85 100 51 72 
After merge sort:
12 29 47 51 72 84 85 100 
The number of array accesses: 78

Merge sort with array size 32:
Initial array:
23 38 76 100 10 90 35 65 25 91 88 17 9 49 41 29 69 91 98 59 3 59 54 50 37 4 45 88 3 62 60 93 
After merge sort:
3 3 4 9 10 17 23 25 29 35 37 38 41 45 49 50 54 59 59 60 62 65 69 76 88 88 90 91 91 93 98 100 
The number of array accesses: 568

Merge sort with array size 128:
Initial array:
100 1 92 76 91 26 40 15 84 94 100 59 43 40 88 78 98 51 36 67 76 91 83 12 61 27 0 30 89 26 22 55 27 13 30 84 5 37 66 89 97 31 13 5 71 67 84 34 18 19 0 94 76 83 73 36 76 39 66 65 31 54 86 58 67 82 7 73 85 73 27 82 70 41 87 41 7 70 41 92 56 42 52 98 91 24 0 67 63 32 98 94 87 83 17 53 30 91 92 15 30 86 97 100 93 49 6 100 86 48 58 41 56 9 4 46 33 4 79 62 37 76 21 23 24 4 42 55 
After merge sort:
0 0 0 1 4 4 4 5 5 6 7 7 9 12 13 13 15 15 17 18 19 21 22 23 24 24 26 26 27 27 27 30 30 30 30 31 31 32 33 34 36 36 37 37 39 40 40 41 41 41 41 42 42 43 46 48 49 51 52 53 54 55 55 56 56 58 58 59 61 62 63 65 66 66 67 67 67 67 70 70 71 73 73 73 76 76 76 76 76 78 79 82 82 83 83 83 84 84 84 85 86 86 86 87 87 88 89 89 91 91 91 91 92 92 92 93 94 94 94 97 97 98 98 98 100 100 100 100 
The number of array accesses: 3260

Counting sort with array size 8:
Initial array:
95 34 36 91 19 32 91 11 
After counting sort:
11 19 32 34 36 91 91 95 
The number of array accesses: 16

Counting sort with array size 32:
Initial array:
47 97 77 32 10 34 39 66 9 44 79 42 48 57 70 51 100 57 74 90 61 83 44 22 16 46 12 1 44 69 79 92 
After counting sort:
1 9 10 12 16 22 32 34 39 42 44 44 44 46 47 48 51 57 57 61 66 69 70 74 77 79 79 83 90 92 97 100 
The number of array accesses: 64

Counting sort with array size 128:
Initial array:
66 21 23 42 22 29 75 31 73 53 74 87 76 9 38 41 67 78 31 94 60 41 15 42 88 95 43 31 63 88 22 28 9 12 37 31 41 11 62 80 30 1 66 72 78 70 13 44 14 10 37 74 51 19 83 38 13 92 36 76 80 58 71 55 36 7 86 77 85 13 22 14 82 89 52 59 24 65 69 38 75 72 79 93 91 61 30 3 52 66 46 31 91 16 86 26 90 37 70 74 51 92 54 32 46 5 57 37 37 25 75 11 97 19 3 88 80 0 57 32 32 2 29 22 85 82 15 74 
After counting sort:
0 1 2 3 3 5 7 9 9 10 11 11 12 13 13 13 14 14 15 15 16 19 19 21 22 22 22 22 23 24 25 26 28 29 29 30 30 31 31 31 31 31 32 32 32 36 36 37 37 37 37 37 38 38 38 41 41 41 42 42 43 44 46 46 51 51 52 52 53 54 55 57 57 58 59 60 61 62 63 65 66 66 66 67 69 70 70 71 72 72 73 74 74 74 74 75 75 75 76 76 77 78 78 79 80 80 80 82 82 83 85 85 86 86 87 88 88 88 89 90 91 91 92 92 93 94 95 97 
The number of array accesses: 256
*/