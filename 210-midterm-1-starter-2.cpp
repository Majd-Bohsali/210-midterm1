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
        if (!head) return; // checks if the doublyLinkedList is currently empty

        Node* temp = head; // creates a temporary node, this will iterate through each node until the correct node to delete is found. starts at the front (head)
        
        // continues untill the target delete value is found or has reached the end without finding the value
        while (temp && temp->data != value)
            temp = temp->next; // moves temp to the next element in the doubly linked list

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}