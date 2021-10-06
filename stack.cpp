/*
This program implements a simple stack calculator which can compute an infix 
expression. It contains two main steps -- first convert the infix expression 
to postfix, and then compute tht result. Assumptions: no swhitespace in the 
string; all the operands are single digits; the result of every operation 
is a single digit; balanced parenthesis.
Assignment 7 - Calculator
Hongye Xu, CS 110C
*/

#include <iostream>
using namespace std;

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


string inToPost(string input)
{
  ArrayStack stack;
  string postfixExp = "";
  //To put the string into postfix format
  for (int i = 0; i < input.size(); i++)
  {
    char item = input[i];
    //if you encounter an operand
    if (isdigit(item))
    {
      postfixExp += item;
    }
    //If you encounter '('
    else if (item == '(')
    {
      stack.push(item);
    }
    //If you encounter an operator
    else if (item == '+' || item == '-' || item == '*' || item == '/')
    {
      //If the stack is empty
      if (stack.isEmpty())
      {
        stack.push(item);
      }
      else
      {
        bool precedenceAction = false;
        //check if if it is an operator of greater or equal precedence
        if (((stack.peek() == '+') || (stack.peek() == '-')) && ((item == '+') || (item == '-')))
          precedenceAction = true;
        if ((stack.peek() == '*') || (stack.peek() == '/'))
          precedenceAction = true;

        if (precedenceAction)
        {
          postfixExp += stack.peek(); //Appends the operator to end of stack
          stack.pop(); //"pops" the operator from stack
          if (item == '*' || item == '/')
          {  
            while ((stack.peek() != '(') && (stack.peek() != '+') && (stack.peek() != '-') && (!stack.isEmpty()))
            {
              postfixExp += stack.peek(); //Appends the operator to end of stack
              stack.pop(); //"pops" the operator from stack
            }
            stack.push(item); 
          }
          else
          {
            while((stack.peek() != '(') && (!stack.isEmpty()))
            {
              postfixExp += stack.peek(); //Appends the operator to end of stack
              stack.pop(); //"pops" the operator from stack
            }
            stack.push(item); 
          }
        }
        else
        {
          stack.push(item);  
        }
      }
    }
    //if you encounter a ")"
    else if(item == ')')
    {
      do
      {  
        postfixExp += stack.peek(); //Appends the operator to end of stack
        stack.pop(); //"pops" the operator from stack     
      } while(stack.peek() != '(');
      stack.pop(); //To pop off the '('
    }

  }
  //reach the end of the string at this point
  while (!stack.isEmpty())
  {
    postfixExp += stack.peek(); 
    stack.pop();
  }
  return postfixExp;
}


int calculator(string postfixExp)
{
  int result;
  ArrayStack stack;
  char operand1, operand2;
  int operand1Value,  operand2Value;
  // calculate a string containing postfix expression
  // at loop end, the result will be at the top of the stack
  for (int i = 0; i < postfixExp.size(); i++)
  {
    char item = postfixExp[i];
    if (isdigit(item))  //if item is an operand
      stack.push(item);
    else // if item is an operator
    {
      // compute result of applying operator to the top
      // two elements and push result on stack
      operand2 = stack.peek();
      operand2Value = operand2 - '0';
      stack.pop();

      operand1 = stack.peek();
      operand1Value = operand1 - '0';
      stack.pop();
      if (item == '+')
      {
        result = operand1Value + operand2Value;
      }
      else if (item == '-')
      {
        result = operand1Value - operand2Value;
      }
      else if (item == '*')
      {
        result = operand1Value * operand2Value;
      }
      else if (item == '/')
      {
        result = operand1Value / operand2Value;
      }

      if (result < 0 || result >= 10)
      {
        cout << "Error! The result of some operation is not a single digit!\n";
        exit(0);
      }
      stack.push(result + '0');
    }
  }
  return stack.peek() - '0';
}


bool parenthesisBalanced(string input)
{           
  bool balancedSoFar = true;
  ArrayStack stack;
  int length = input.size();
  for (int i = 0; i < length; i++)
  {
    if (input[i] == '(')
      stack.push('(');
    else if (input[i] == ')')
    {
      if (stack.isEmpty())
        balancedSoFar = false;
      else
        stack.pop();
    }
  }
  if (balancedSoFar && stack.isEmpty())
    return true;
  else
    return false;
}


int main()
{
  string input;
  cout << "Enter an infix expression to calculate: ";
  cin >> input;
  
  if (parenthesisBalanced(input) == false)
  {
    cout << "Error! Parenthesis are not balanced.\n";
    exit(0);
  }

  string postfixExp = inToPost(input);
  cout << "The postfixExp expression is:" << postfixExp << endl;
  cout << "The result: " << calculator(postfixExp) << endl;
  return 0;
}


/*SAMPLE OUTPUT
[hxu65@hills ~]$ ./a.out
Enter an infix expression to calculate: (1+1)*2+4/2
The postfixExp expression is:11+2*42/+
The result: 6
[hxu65@hills ~]$ ./a.out
Enter an infix expression to calculate: ((2*3)-(1*4))/2+1
The postfixExp expression is:23*14*-2/1+
The result: 2
[hxu65@hills ~]$ ./a.out
Enter an infix expression to calculate: ((2+3)*1+1
Error! Parenthesis are not balanced.
[hxu65@hills ~]$ ./a.out
Enter an infix expression to calculate: (2+3)*1+1)
Error! Parenthesis are not balanced.
[hxu65@hills ~]$ ./a.out
Enter an infix expression to calculate: 2*6+4/2
The postfixExp expression is:26*42/+
Error! The result of some operation is not a single digit!
*/