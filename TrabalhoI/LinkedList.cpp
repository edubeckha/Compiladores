// From http://stackoverflow.com/questions/22141477/simple-linked-list-c

#include <iostream>
using namespace std;

class LinkedList{
    // Struct inside the class LinkedList
    // This is one node which is not needed by the caller. It is just
    // for internal work.
    struct Node {
        int x;
        Node *next;
    };

// public member
public:
    // constructor
    LinkedList(){
        head = NULL; // set head to NULL
    }

    // This prepends a new value at the beginning of the list
    void addValue(int val){
        Node *n = new Node();   // create new Node
        n->x = val;             // set value
        n->next = head;         // make the node point to the next node.
                                //  If the list is empty, this is NULL, so the end of the list --> OK
        head = n;               // last but not least, make the head point at the new node.
    }

    // returns the first element in the list and deletes the Node.
    // caution, no error-checking here!
    int popValue(){
        Node *n = head;
        int ret = n->x;

        head = head->next;
        delete n;
        return ret;
    }

// private member
private:
    Node *head; // this is the private member variable. It is just a pointer to the first Node
};

// int main() {
//     LinkedList list;

//     list.addValue(5);
//     list.addValue(10);
//     list.addValue(20);
//     list.addValue(20);
//     list.addValue(5);
//     list.addValue(10);
//     list.addValue(20);
//     list.addValue(20);
// 	list.addValue(5);
//     list.addValue(10);
//     list.addValue(20);
//     list.addValue(20);


// 	cout << list.popValue() << endl;
//     cout << list.popValue() << endl;
//     cout << list.popValue() << endl;
//     cout << list.popValue() << endl;
//     cout << list.popValue() << endl;
//     cout << list.popValue() << endl;
//     cout << list.popValue() << endl;
//     cout << list.popValue() << endl;
//     cout << list.popValue() << endl;
//     cout << list.popValue() << endl;
//     cout << list.popValue() << endl;
//     cout << list.popValue() << endl;
//     // because there is no error checking in popValue(), the following
//     // is undefined behavior. Probably the program will crash, because
//     // there are no more values in the list.
//     // cout << list.popValue() << endl;
//     return 0;
// }
