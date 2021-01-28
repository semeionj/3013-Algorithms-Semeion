///////////////////////////////////////////////////////////////////////////////
//
// Author:           Semeion Stafford
// Email:            semeionjs@gmail.com
// Label:            P01
// Title:            Lecture 01 - Array Based Stack
// Course:           3013
// Semester:         Spring 2021
//
// Description:
//                   Overview of a class implementing an array based stack
//
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>

using namespace std;

/**
 * ArrayStack
 * 
 * Description:
 *      Array based stack
 * 
 * Public Methods:
 *      - See class below
 * 
 * Usage: 
 *      - See main program
 *      
 */
class ArrayStack
{
private:
    int *A;      // pointer to array of int's
    int size;    // current max stack size
    int top;     // top of stack
    int resize;  // how many times the stack size changed
    int maxSize; // largest size of stack

    /**
  * Private bool: Empty
  * 
  * Description:
  *      Stack empty?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = empty
*/
    bool Empty()
    {
        return (top <= 0);
    }

    /**
  * Private bool: Full
  * 
  * Description:
  *      Stack full?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = full
*/
    bool Full()
    {
        return (top >= size);
    }

    /**
  * Private void: ContainerGrow
  * 
  * Description:
  *      Resizes the container for the stack by doubling
  *      its capacity
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
*/
    void ContainerGrow()
    {

        int newSize = size * 2; // double size of original

        if (newSize > maxSize)
            maxSize = newSize;

        int *B = new int[newSize]; // allocate new memory

        for (int i = 0; i < size; i++)
        { // copy values to new array
            B[i] = A[i];
        }

        delete[] A; // delete old array

        size = newSize; // save new size

        A = B; // reset array pointer
        resize++;
    }

    /**
  * Private void: ContainerShrink
  * 
  * Description:
  *      Resizes the container for the stack by halfing
  *      its capacity
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
*/
    void ContainerShrink()
    {

        if (size <= 10)
            return;

        int newSize = size / 2; // half size of original

        //size never goes below 10
        if (newSize <= 10)
            newSize = 10;

        int *B = new int[newSize]; // allocate new memory

        for (int i = 0; i < top; i++)
        { // copy values to new array
            B[i] = A[i];
        }

        delete[] A; // delete old array

        size = newSize; // save new size

        A = B; // reset array pointer
        resize++;
    }

public:
    /**
  * Public void: Print
  * 
  * Description:
  *      Prints stack to standard out
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
*/
    void Print()
    {
        for (int i = 0; i <= (top - 1); i++)
        {
            cout << A[i] << " ";
        }
        cout << endl;
    }

    /**
  * ArrayStack
  * 
  * Description:
  *      Constructor no params
  * 
  * Params:
  *     - None
  * 
  * Returns:
  *     - NULL
*/
    ArrayStack()
    {
        size = 10;
        A = new int[size];
        top = 0;
        maxSize = 10;
        resize = 0;
    }

    /**
  * ArrayStack
  * 
  * Description:
  *      Constructor size param
  * 
  * Params:
  *     - int size
  * 
  * Returns:
  *     - NULL
  */
    ArrayStack(int s)
    {
        size = s;
        A = new int[s];
        top = 0;
        maxSize = 10;
        resize = 0;
    }

    /**
  * Public int: Pop
  * 
  * Description:
  *      Returns top value and removes it from stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [int] top value if any
*/
    int Pop()
    {
        if (!Empty())
        {
            //cout << "POP " << A[top - 1] << endl;
            int val = A[top - 1];
            top--;
            //cout << "HERE WE POP " <<A[top] << " new top is "<< top << endl;
            //shrink by .5 if less than ~15% the size

            if (top <= (size / 6))
                ContainerShrink();

            return val;
        }
        else
        {
            cout << "Empty stack" << endl;
            return INT_MAX; //Sentinel value
                            
        }
    }

    /**
  * Public bool: Push
  * 
  * Description:
  *      Adds an item to top of stack
  * 
  * Params:
  *      [int] : item to be added
  * 
  * Returns:
  *      [bool] ; success = true
*/
    bool Push(int x)
    {
        //grow by 1.75 container if it is full
        if (Full())
        {
            ContainerGrow();
        }
        if (!Full())
        {
            A[top] = x;
            top++;
            if (Full())
            {
                ContainerGrow();
            }
            return true;
        }

        return false;
    }

    /**
  * Public void: info
  * 
  * Description:
  *      Prints scack info
  * 
  * Params:
  *      None
  * 
  * Returns:
  *      None
*/
    void info()
    {
        cout << "######################################################################" << endl;
        cout << "Assignment 4 - Resizing the Stack" << endl;
        cout << "CMPS 3013" << endl;
        cout << "Semeion Stafford" << endl;
        cout << "Max Stack Size: " << maxSize << endl;
        cout << "End Stack Size: " << size << endl;
        cout << "Stack Resized: " << resize << endl;
        cout << "Elements: " << top << endl;
        cout << "######################################################################" << endl;
    }
};

// MAIN DRIVER
// Simple Array Based Stack Usage
int main()
{
    
    ifstream infile;  // object for reading from a file
    ofstream outfile; // object for writing to a file

    infile.open("nums_test.txt");

    if (!infile)
    {
        cout << "Error opening file...";
        exit(1);
    }

    ArrayStack stack;
    int num = 0;

    int o = 0, e = 0;
    while (!infile.eof())
    {
        infile >> num;
        //push even numbers to stack
        if (num % 2 == 0)
        {
            stack.Push(num);
            e++;
        }
        else
        {
            //pop when odd
            stack.Pop();
            o++;
        }
    }
    stack.Print();
    stack.info();
}
