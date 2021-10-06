/*
This program uses a queue and a stack to determine if a 
string S is a palindrome. It implements the algorithm 
discussed in the textbook section 13.2.2
Assignment 8 - Palindrome
Hongye Xu, CS 110C
*/


#include <iostream>
using namespace std;


// a queue of chars
class Queue 
{
  private:
    static const int MAX_QUEUE = 100;
    // an array to hold queue entries
    char entries[MAX_QUEUE];
    // properties to hold current front, 
    // back, and count
    int front;
    int back;
    int count;
  public:
    Queue() 
      { front = 0; back = MAX_QUEUE-1; count = 0; };
    bool enqueue(char newEntry);
    bool dequeue();
    char peek();
    bool isEmpty();
};

bool Queue::isEmpty()
{
  if (count == 0)
    return true;
  else
    return false;
}

bool Queue::enqueue(char newEntry)
{
  bool canEnqueue = false;
  if (count < MAX_QUEUE)
  {
    back = (back + 1) % MAX_QUEUE;
    entries[back] = newEntry;
    count++;
    canEnqueue = true ;
  }
  if (!canEnqueue)
    cout << "Can't enqueue! The queue is full.\n";
  return canEnqueue;
}

bool Queue::dequeue()
{
  bool canDequeue = false;
  if (!isEmpty())
  {
    front = (front + 1) % MAX_QUEUE;
    count--;
    canDequeue = true ;
  }
  if (!canDequeue)
    cout << "Can't dequeue! The queue is empty.\n";
  return canDequeue;
}

char Queue::peek()
{
  return entries[front];
}



class ArrayStack
{
  private:
    static const int maxStack = 100;
    char stack[maxStack]; // Array of stack items
    int top;
  public:
    ArrayStack();
    bool isEmpty() const ;
    bool push( const char& newitem);
    bool pop();
    char peek() const ;
};

ArrayStack::ArrayStack() : top(-1)
{
}

bool ArrayStack::isEmpty() const
{
  return top < 0;
}

bool ArrayStack::push( const char& newitem)
{
  bool canPush = false ;
  if (top < maxStack - 1)
  {
    top++;
    stack[top] = newitem;
    canPush = true;
  } 
  return canPush;  
}

bool ArrayStack::pop()
{
  bool canPop = false;
  if (!isEmpty())
  {
    top--;
    canPop = true;
  }
  return canPop;
}

char ArrayStack::peek() const 
{
  return stack[top];
}



bool isPalindrome(string input)
{
  Queue aQueue;
  ArrayStack aStack;
  int length = input.size();
  for (int i = 0; i < length; i++)
  {
    char nextChar = input[i];
    aQueue.enqueue(nextChar);
    aStack.push(nextChar);
  }

  bool charactersAreEqual = true;
  char queueFront, stackTop;
  while ((!aQueue.isEmpty()) && (charactersAreEqual))
  {
    queueFront = aQueue.peek();
    stackTop = aStack.peek();
    if (queueFront == stackTop)
    {
      aQueue.dequeue();
      aStack.pop();
    }
    else
      charactersAreEqual = false;
  }
  return charactersAreEqual;
}



int main() 
{
  string input;
  cout << "Enter a string to test if it is a palindrome: ";
  cin >> input;
  if (isPalindrome(input))
    cout << "This is a palindrome\n";
  else
    cout << "This is not a palindrome\n";
  return 0;
}


/*
[hxu65@hills ~]$ ./a.out
Enter a string to test if it is a palindrome: madam
This is a palindrome
[hxu65@hills ~]$ ./a.out
Enter a string to test if it is a palindrome: rotator
This is a palindrome
[hxu65@hills ~]$ ./a.out
Enter a string to test if it is a palindrome: flower
This is not a palindrome
[hxu65@hills ~]$ ./a.out
Enter a string to test if it is a palindrome: apple
This is not a palindrome
*/