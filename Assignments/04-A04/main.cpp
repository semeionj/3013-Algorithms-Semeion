///////////////////////////////////////////////////////////////////////////////
//                   
// Author:           Semeion Stafford
// Email:            semeionjs@gmail.com
// Label:            A04
// Title:            Linked List Class
// Course:           CMPS 3013
// Semester:         Spring 2021
//
// Description:
//       This program implements a class that allows a linked list to be used just like 
//       an array. It overloads the "[]" (square brackets) to simulate accessing seperate 
//       array elements, but really it traverses the list to find the specified node using
//       an index value. It also overloads the "+" and "-" signs allowing a user to "add"
//       or "push" items onto the end of the list, as well as "pop" items off the end of our 
//       array. This class is not meant to replace the STL vector library, its simply a project
//       to introduce the beginnings of creating complex / abstract data types. 
//       
// Usage: 
//      - $ ./main filename
//      - This will read in a file containing whatever values to be read into our list/array. 
//      
// Files:            
//      main.cpp    : driver program 
//      list.h      : header file with list defintion
//      list.cpp    : list implementation
/////////////////////////////////////////////////////////////////////////////////

#include <iostream>

using namespace std;

int A[100];

struct Node {
    int x;
    Node *next;
    Node() {
        x = -1;
        next = NULL;
    }
    Node(int n) {
        x = n;
        next = NULL;
    }
};

/**
     * Class Name: List
     * 
     * Description:
     *      Manipulate linked list using nodes
     * 
     * Public Methods:
     *      - Push (void)
     *      - Pop (void)
     * 
     * Private Methods:
     *      - A list of 
     *      - each private method
     *      - with return types
     * 
     * Usage: 
     * 
     *      myList.Push(5);
     *      String s = myList.Print();
     *      
*/
class List {
private:
    Node *Head;            //pointer to front of list
    Node *Tail;            //pointer to end of list
    int Size;              //stores length of list

public:
    List() {
        Head = Tail = NULL;
        Size = 0;
    }

    /**
     * Public : Push
     * 
     * Description:
     *      Inserts value into a linked list.
     * 
     * Params:
     *      int     :  integer to insert
     * 
     * Returns:
     *      None:
     */
    void Push(int val) {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        if (!Head && !Tail) {
            Head = Tail = Temp;
        } else {
            Tail->next = Temp;
            Tail = Temp;
        }
        Size++;
    }

    /**
     * Public : Insert
     * 
     * Description:
     *      Inserts value into a linked list.
     * 
     * Params:
     *      int     :  integer to insert
     * 
     * Returns:
     *      None:
     */
    void Insert(int val) {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        // figure out where it goes in the list

        Temp->next = Head;
        Head = Temp;
        if (!Tail) {
            Tail = Head;
        }
        Size++;
    }

    void PrintTail() {
        cout << Tail->x << endl;
    }

    string Print() {
        Node *Temp = Head;
        string list;

        while (Temp != NULL) {
            list += to_string(Temp->x) + "->";
            Temp = Temp->next;
        }

        return list;
    }


    /**
     * Public : Push
     * 
     * Description:
     *      Pemove value into a linked list.
     * 
     * Params:
     *      int     :  integer to remove
     * 
     * Returns:
     *      None:
     */
    // not implemented
    int Pop() {
        Size--;
        return 0;
    }


    /**
     * Public : Overloaded +
     * 
     * Description:
     *      Join 2 lists
     * 
     * Params:
     *      const List     :  list to insert on the right
     * 
     * Returns:
     *      None:
     */
    List operator+(const List &Rhs) {
        // Create a new list that will contain both when done
        List NewList;

        // Get a reference to beginning of local list
        Node *Temp = Head;

        // Loop through local list and Push values onto new list
        while (Temp != NULL) {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Get a reference to head of Rhs
        Temp = Rhs.Head;

        // Same as above, loop and push
        while (Temp != NULL) {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Return new concatenated version of lists
        return NewList;
    }

    /**
     * Public : Overloaded +
     * 
     * Description:
     *      Implementation of [] operator.  This function returns an
     *      int value as if the list were an array.
     * 
     * Params:
     *      const List     :  value at index
     * 
     * Returns:
     *      None:
     */
    int operator[](int index) {
        Node *Temp = Head;

        if (index >= Size) {
            cout << "Index out of bounds, exiting";
            exit(0);
        } else {

            for (int i = 0; i < index; i++) {
                Temp = Temp->next;
            }
            return Temp->x;
        }
    }

    /**
     * Public : Overloaded Print
     * 
     * Description:
     *      Implementation of print function.  
     * 
     * Params:
     *      const List     :  List to print and output stream
     * 
     * Returns:
     *      None:
     */
    friend ostream &operator<<(ostream &os, List L) {
        os << L.Print();
        return os;
    }
};

int main(int argc, char **argv) {

    List L1;
    List L2;

    for (int i = 0; i < 25; i++) {
        L1.Push(i);
    }

    for (int i = 50; i < 100; i++) {
        L2.Push(i);
    }

    //cout << L1 << endl;
    L1.PrintTail();
    L2.PrintTail();

    List L3 = L1 + L2;
    cout << L3 << endl;

    cout << L3[5] << endl;
    return 0;
}