// COMSC210 | Midterm #1 | Majd Bohsali
// IDE used: Visual Studio Code
#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    /* creates a struct object called Node. This will be used to store the data value for each node element
       the struct also has a prev and next pointer variables of type Node to hold the address for the node
        before the current node and the node after
    */ 
    struct Node {
        int data;
        Node* prev;
        Node* next;
        // constructor sets the data, prev, and next fields
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head; // pointer variable to the Head node of the doubly linked list
    Node* tail; // pointer variable to the Tail node of the doubly linked list

public:
    // default constructor for the DoublyLinkedList class, 
    // sets head and tail to nullptr, meaning it does not point to any elements yet (doubly linked list is empty)
    DoublyLinkedList() { head = nullptr; tail = nullptr; } 

    // Defines insert_after(int value, int positon)
    // inserts new node right after the node in the position passed as an argument
    // function does not return anything
    // value is the value for the node element to insert, 
    // position is the index the value should be placed at with 0 being the start 
    void insert_after(int value, int position) {

        // Makes sure the positon is 0 or greater, ensuring it is a valid position to insert at
        if (position < 0) {
            cout << "Position must be >= 0." << endl; // outputs to the user their mistake
            return; // exits method
        }

        Node* newNode = new Node(value); // defines newNode, is is the Node that will be inserted into the list
        if (!head) { // checks if the doubly linked list is currently empty, will continue it is empty
            head = tail = newNode; // sets the start (head) and end (tail) to point to the new node
            return; // exits method
        }
        // continues here if the doubly linked list is not empty

        
        Node* temp = head; // creates a temporary node, this will iterate through each node until the correct positon is found. starts at the front (head)
        for (int i = 0; i < position && temp; ++i) // will cycle as long as i is less than the target positon or until the end is reached
            temp = temp->next; // moves temp to the next element in the doubly linked list

        if (!temp) { // checks if the temp points to a nullptr (meaning the end of the doubly linked list is reached)
            cout << "Position exceeds list size. Node not inserted.\n"; // outputs to user that the target postion was out of bounds
            delete newNode; // deletes newNode to avoid memory leak
            return; // exits method
        }

        // reached only when the target positon was valid and temp points to the node right before the insert location
        newNode->next = temp->next; // sets the newNode's next pointer to the node after the temp Node
        newNode->prev = temp; // sets the newNode's prev pointer to the temp node
        if (temp->next) // checks if the temp's node (or newNode's) next value pointed to an element or nullptr
            temp->next->prev = newNode; // if it pointed to an element, that elements prev pointer is set to the newNode
        else
            tail = newNode; // if temp pointed to nullptr, it means the element was inserted at the end
                            // sets the tail of the doubly linked list to the newly inserted node
        temp->next = newNode; // sets the temp's next pointer to the newly inserted node
    }

    // Defines delete_val(int value
    // function does not return anything
    // value is the target value to remove
    void delete_val(int value) {
        if (!head) return; // checks if the doubly linked list is currently empty

        Node* temp = head; // creates a temporary node, this will iterate through each node until the correct node to delete is found. starts at the front (head)
        
        // continues until the target delete value is found or has reached the end without finding the value
        while (temp && temp->data != value)
            temp = temp->next; // moves temp to the next element in the doubly linked list

        if (!temp) return; // exits method if the end of the doubly linked list was reached without finding the delete value

        // checks if the node that is being deleted has a previous value
        // it is not the head of the doubly linked list if true
        if (temp->prev) 
            temp->prev->next = temp->next; // sets the next value for the node right before the delete node to the node right after the delete node
        else
            head = temp->next; // if the delete node is the head, the new value for the head is set to the node right after the delete node

        // checks if the node that is being deleted has a next value
        // it is not at the tail of the doubly linked list if true
        if (temp->next)
            temp->next->prev = temp->prev; // sets the prev value for the node right after the delete node to the node right before the delete node
        else
            tail = temp->prev; // if the delete node is the tail, the new value for the tail is set to the node right before the delete node

        delete temp; // deletes the temp Node, removing it from memory preventing any memory leaks
    }

    // Defines delete)pos(int pos)
    // deletes the node at the position pos, the position for the first element is 1 
    void delete_pos(int pos) {
        // checks if the list is empty
        if (!head) { 
            cout << "List is empty." << endl; // returns the problem to the user
            return; // exits the method
        }
        
        // checks if the pos is 1, meaning it is the front of the list
        if (pos == 1) {
            pop_front(); // if the first element is being deleted it calls pop_front()
            return; // exits the method
        }
    
        Node* temp = head; // creates a temporary node to iterate until the correct node is found
    
        // iterates until temp points to one node before the target node
        for (int i = 1; i < pos; i++){
            // checks if it reached the end of the doubly linked list before finding the positon 
            if (!temp) {
                cout << "Position doesn't exist." << endl; 
                return; // exits method
            }
            else // contiues if it did not reach the end
                temp = temp->next; // steps one to the next node, temp points to the node at position pos
        }

        // checks if it reached the end of the doubly linked list before finding the positon 
        if (!temp) {
            cout << "Position doesn't exist." << endl; // returns the error to the user
            return; // exits method
        }
        
        // checks if the node points to the end
        if (!temp->next) {
            pop_back(); // uses pop_back if the delete node is the tail
            return; // exits method
        }
        
        Node* tempPrev = temp->prev; // saves the pointer to the Node before temp
        tempPrev->next = temp->next; // sets the next pointer of the node before temp to the node after temp 
        temp->next->prev = tempPrev; // sets the prev pointer of the node after temp to the node before temp
        delete temp; // deletes temp to prevent memory leak
    }

    // inserts node with value v at the end of the doubly linked list
    void push_back(int v) {
        Node* newNode = new Node(v); // creates new node with element value v
        if (!tail) // checks if list is empty
            head = tail = newNode; // if empty sets the head and tail to the new node
        else { // contunes if not empty 
            tail->next = newNode; // sets the current tail node next pointer to the new node 
            newNode->prev = tail;  // sets the new nodes prev pointer to the current tail
            tail = newNode; // sets the tail of the list to the new node
        }
    }
    
    // inserts node with value v at the front of the doubly linked list
    void push_front(int v) {
        Node* newNode = new Node(v); // creates new node with element value v
        if (!head) // checks if list is empty
            head = tail = newNode; // if empty sets the head and tail to the new node
        else { // contunes if not empty 
            newNode->next = head; // sets the new nodes next pointer to the current head
            head->prev = newNode; // sets the current heads node previous pointer to the new node 
            head = newNode; // sets the head of the list to the new node
        }
    }
    
    // removes the node at the front of the doubly linked list
    void pop_front() {
        if (!head) { // checks if list is empty
            cout << "List is empty." << endl; // tells the user the error if it is empty
            return; // exits method
        }

        Node * temp = head; // sets a temp node to iterate, starts at the head

        if (head->next) { // checks if the list is more than one node long
            head = head->next; // moves the lists head pointer up one
            head->prev = nullptr; // sets the new head's prev pointer to nullptr since it is going to be the new head
        }
        else
            head = tail = nullptr; // sets head and tail to nullptr since the list is now empty 
        delete temp; // deletes the node to prevent memory leak
    }

    // removes the noed at the end of the doubly linked list
    void pop_back() {
        if (!tail) { // checks if list is empty
            cout << "List is empty." << endl; // prints the error if it is empty
            return; // exits method
        }
        Node * temp = tail; // sets a temp node to iterate, starts at the tail

        if (tail->prev) {  // checks if the list is more than one node long
            tail = tail->prev; // moves the lists tail pointer down one
            tail->next = nullptr; // sets the new tails's next pointer to nullptr since it is going to be the new tail
        }
        else
            head = tail = nullptr;  // sets head and tail to nullptr since the list is now empty 
        delete temp; // deletes the node to prevent memory leak
    }

    // Destructor method for the DoublyLinkedList class
    ~DoublyLinkedList() {
        // goes through each value and deletes it to prevent memory leaks
        while (head) {
            Node* temp = head; // sets the temp node front of the doubly linked list
            head = head->next; // moves the head node down one
            delete temp; // deletes the current node (the head) 
        }
    }
    
    // prints all elements in order
    void print() {
        Node* current = head; // starst with setting the iterator pointer to the head of the linked list
        if (!current) { // check if the list is empty 
            cout << "List is empty." << endl; // prints the error if it is empty
            return; // exits method
        }

        // iterates untill the end is reached 
        while (current) {
            cout << current->data << " "; // prints the nodes data and adds space
            current = current->next; // continues to the next node
        }
        cout << endl; // creates new line in console
    }

    // prints all elements in reverse order
    void print_reverse() {
        Node* current = tail; // starst with setting the iterator pointer to the tail of the linked list
        if (!current) { // check if the list is empty 
            cout << "List is empty." << endl; // prints the error if it is empty
            return; // exits method
        }
        
        // iterates until the end is reached 
        while (current) {
            cout << current->data << " "; // prints the nodes data and adds space
            current = current->prev; // continues to the previous node
        }
        cout << endl; // creates new line in console
    }

    // prints every other element of the doubly linked list
    void every_other_element() { 
        Node* current = head; // starst with setting the iterator pointer to the head of the linked list
        if (!current) { // check if the list is empty 
            cout << "List is empty." << endl; // prints the error if it is empty
            return; // exits method
        }

        // iterates until the end is reached 
        while (current) {
            cout << current->data << " "; // prints the nodes data and adds space
            current = current->next; // goes up one node

            // makes sure node is not nullptr before continuing up one more to skip
            if (current) {
                current = current->next; // goes up one node
            }
        }
        cout << endl; // creates new line in console
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    return 0;
    
}