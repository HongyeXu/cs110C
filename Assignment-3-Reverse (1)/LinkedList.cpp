//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Implementation file for the class LinkedList.
 @file LinkedList.cpp */

#include "LinkedList.h"  // Header file
#include <cassert>
#include <string>
#include <cstdlib>

template<class ItemType>
LinkedList<ItemType>::LinkedList() : headPtr(nullptr), itemCount(0)
{
   headPtr = nullptr;
   tailPtr = nullptr;
   itemCount = 0;
}  // end default constructor

template<class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& aList) : itemCount(aList.itemCount)
{
   Node<ItemType>* origChainPtr = aList.headPtr;  // Points to nodes in original chain

   if (origChainPtr == nullptr)
      headPtr = nullptr;  // Original list is empty
   else
   {
      // Copy first node
      headPtr = new Node<ItemType>();
      headPtr->setItem(origChainPtr->getItem());
      
      // Copy remaining nodes
      Node<ItemType>* newChainPtr = headPtr;      // Points to last node in new chain
      origChainPtr = origChainPtr->getNext();     // Advance original-chain pointer
      while (origChainPtr != nullptr)
      {
         // Get next item from original chain
         ItemType nextItem = origChainPtr->getItem();
         
         // Create a new node containing the next item 
         Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);  
         
         // Link new node to end of new chain
         newChainPtr->setNext(newNodePtr); 
         
         // Advance pointer to new last node      
         newChainPtr = newChainPtr->getNext();
         
         // Advance original-chain pointer
         origChainPtr = origChainPtr->getNext();
      }  // end while
      
      newChainPtr->setNext(nullptr);              // Flag end of chain
   }  // end if
}  // end copy constructor

template<class ItemType>
LinkedList<ItemType>::~LinkedList()
{
   clear();
}  // end destructor

template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
   return itemCount == 0;
}  // end isEmpty

template<class ItemType>
int LinkedList<ItemType>::getLength() const
{
   return itemCount;
}  // end getLength

template<class ItemType>
bool LinkedList<ItemType>::insert(int newPosition, const ItemType& newEntry)
{
   bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1);
   if (ableToInsert)
   {
      // Create a new node containing the new entry 
      Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);  

      if (getLength() == 0)
      {
         headPtr = newNodePtr;
         tailPtr = newNodePtr;
      }

      else if (newPosition == 1)
      {
        newNodePtr->setNext(headPtr);
        headPtr->setPrev(newNodePtr);
        headPtr = newNodePtr;
      }

      else if (newPosition == (itemCount + 1))
      {
         Node<ItemType>* prevPtr = getNodeAt(newPosition - 1);
         prevPtr->setNext(newNodePtr);
         newNodePtr->setPrev(prevPtr);
         tailPtr = newNodePtr; 
      }

      else
      {
         Node<ItemType>* prevPtr = getNodeAt(newPosition - 1); 
         newNodePtr->setNext(getNodeAt(newPosition));  
         prevPtr->setNext(newNodePtr);

         newNodePtr->setPrev(prevPtr);
         Node<ItemType>* nextPtr = getNodeAt(newPosition + 1); 
         nextPtr->setPrev(newNodePtr);
      }

      itemCount++;  // Increase count of entries
   }  // end if
   
   return ableToInsert;
}  // end insert

template<class ItemType>
bool LinkedList<ItemType>::remove(int position)
{
   bool ableToRemove = (position >= 1) && (position <= itemCount);
   if (ableToRemove)
   {
      Node<ItemType>* curPtr = nullptr;
      if (position == 1)
      {
         // Remove the first node in the chain
         curPtr = headPtr; // Save pointer to node
         headPtr = headPtr->getNext();
         headPtr->setPrev(nullptr); 
      }
      else
      {
         // Find node that is before the one to delete
         Node<ItemType>* prevPtr = getNodeAt(position - 1);

         Node<ItemType>* nextPtr = getNodeAt(position + 1);
         
         // Point to node to delete
         curPtr = prevPtr->getNext();
         
         // Disconnect indicated node from chain by connecting the
         // prior node with the one after
         prevPtr->setNext(curPtr->getNext());

         nextPtr->setPrev(curPtr->getPrev());
         curPtr->setPrev(nullptr);
      }  // end if
      
      // Return node to system
      curPtr->setNext(nullptr);
      delete curPtr;
      curPtr = nullptr;
      
      itemCount--;  // Decrease count of entries
   }  // end if
   
   return ableToRemove;
}  // end remove

template<class ItemType>
void LinkedList<ItemType>::clear()
{
   while (!isEmpty())
      remove(1);
}  // end clear

template<class ItemType>
ItemType LinkedList<ItemType>::getEntry(int position) const throw(PrecondViolatedExcep)
{
   // Enforce precondition
   bool ableToGet = (position >= 1) && (position <= itemCount);
   if (ableToGet)
   {
      Node<ItemType>* nodePtr = getNodeAt(position);
      return nodePtr->getItem();
   }
   else
   {
      string message = "getEntry() called with an empty list or "; 
      message  = message + "invalid position.";
      throw(PrecondViolatedExcep(message)); 
   }  // end if
}  // end getEntry

template<class ItemType>
void LinkedList<ItemType>::setEntry(int position, const ItemType& newEntry) throw(PrecondViolatedExcep)
{
   // Enforce precondition
   bool ableToSet = (position >= 1) && (position <= itemCount);
   if (ableToSet)
   {
      Node<ItemType>* nodePtr = getNodeAt(position);
      nodePtr->setItem(newEntry);
   }
   else
   {
      string message = "setEntry() called with an invalid position."; 
      throw(PrecondViolatedExcep(message)); 
   }  // end if
}  // end setEntry

template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt(int position) const
{
   // Debugging check of precondition
   assert( (position >= 1) && (position <= itemCount) );
   
   // Count from the beginning of the chain
   Node<ItemType>* curPtr = headPtr;
   for (int skip = 1; skip < position; skip++)
      curPtr = curPtr->getNext();
      
   return curPtr;
}  // end getNodeAt

template<class ItemType>
void LinkedList<ItemType>::reverse()
{
   Node<ItemType>* curPtr = getNodeAt(1);
   Node<ItemType>* nextPtr = curPtr->getNext();
   
   //Switch nextPtr and prevPtr
   for(int i = 0; i < itemCount; i++)
   {
      curPtr->setNext(curPtr->getPrev()); 
      curPtr->setPrev(nextPtr);
      curPtr = nextPtr;
      if((nextPtr->getNext()) != nullptr) 
      {
         nextPtr = nextPtr->getNext();
      }  
   }
    
   //Switch the headPtr and tailPtr
   nextPtr = headPtr;
   headPtr = tailPtr;
   tailPtr = nextPtr;
}


// End of implementation file.  To get this to compile on hills,
// add definitions of template types we will use (int or string now,
// add more types if necessary)
template class LinkedList<int>;
template class LinkedList<std::string>;