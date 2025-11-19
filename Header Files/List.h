/*-- List.h ------------------------------------------------------------------

This header file defines a template-based List class implemented using a 
fixed-size NodePool memory manager.

The List stores nodes using array indices instead of pointers. All memory 
allocation and freeing is performed by the NodePool (no dynamic new/delete).

Supported operations:
    Constructor:          Initializes an empty list.
    Destructor:           Returns all nodes to the NodePool.
    Copy Constructor:     Deep-copies another list.
    Assignment Operator:  Overwrites this list with another.
    insertAtPos:          Inserts an element at a given (1-based) position.
    deleteAtPos:          Deletes the node at a given position.
    search:               Finds a value and returns its position.
    getSize:              Returns the number of elements.
    isEmpty:              Checks if the list is empty.
    isFull:               Checks if the list is full.
    sort:                 Bubble-sorts the list by swapping data.
    display:              Prints list elements in order.
    clear:                Deletes all elements.
    getTop:               Returns the head index.
    getFFN:               Returns the first free node index.
----------------------------------------------------------------------------*/

#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "NodePool.h"
using namespace std;

/*============================================================================
    Class Definition
============================================================================*/

template <typename ElementType, int NUM_NODES>
class List {
public:

    /*----- Constructor ------------------------------------------------------
      Precondition : None
      Postcondition: List is initialized empty (head = NULL_VALUE, size = 0).
    ------------------------------------------------------------------------*/
    List();

    /*----- Destructor -------------------------------------------------------
      Precondition : None
      Postcondition: All nodes are returned to the NodePool.
    ------------------------------------------------------------------------*/
    ~List();

    /*----- Copy Constructor -------------------------------------------------
      Precondition : other is a valid List.
      Postcondition: Deep copy of other is created.
    ------------------------------------------------------------------------*/
    List(const List& other);

    /*----- Assignment Operator ----------------------------------------------
      Precondition : other is a valid List.
      Postcondition: This list becomes a deep copy of other.
    ------------------------------------------------------------------------*/
    List& operator=(const List& other);

    /*----- insertAtPos ------------------------------------------------------
      Inserts value at position (1-based indexing).
      Precondition : 1 ≤ position ≤ size+1 and list not full.
      Postcondition: Node inserted in correct place.
    ------------------------------------------------------------------------*/
    void insertAtPos(const ElementType& value, int position);

    /*----- deleteAtPos ------------------------------------------------------
      Deletes node at given position.
      Precondition : 1 ≤ position ≤ size.
      Postcondition: Node removed & returned to NodePool.
    ------------------------------------------------------------------------*/
    void deleteAtPos(int position);

    /*----- getSize ----------------------------------------------------------
      Precondition : None
      Postcondition: Returns current number of nodes.
    ------------------------------------------------------------------------*/
    int getSize() const;

    /*----- isEmpty ----------------------------------------------------------
      Precondition : None
      Postcondition: Returns true if list has 0 elements.
    ------------------------------------------------------------------------*/
    bool isEmpty() const;

    /*----- isFull -----------------------------------------------------------
      Precondition : None
      Postcondition: Returns true if size == NUM_NODES.
    ------------------------------------------------------------------------*/
    bool isFull() const;

    /*----- sort -------------------------------------------------------------
      Sorts the list in ascending order using bubble-sort (data swapping).
      Precondition : None
      Postcondition: List becomes sorted.
    ------------------------------------------------------------------------*/
    void sort();

    /*----- display -----------------------------------------------------------
      Prints all list elements with their positions.
      Precondition : None
    ------------------------------------------------------------------------*/
    void display() const;

    /*----- clear -------------------------------------------------------------
      Deletes all nodes.
      Precondition : None
      Postcondition: head = NULL_VALUE, size = 0.
    ------------------------------------------------------------------------*/
    void clear();

    /*----- getTop -----------------------------------------------------------
      Precondition : None
      Postcondition: Returns head index.
    ------------------------------------------------------------------------*/
    int getTop() const;

    /*----- getFFN -----------------------------------------------------------
      Returns first free node index from NodePool.
      Precondition : None
      Postcondition: Matches pool.getFFN().
    ------------------------------------------------------------------------*/
    int getFFN();

    /*----- search -----------------------------------------------------------
      Searches list for value.
      Precondition : None
      Postcondition: Returns (1-based) position or -1 if not found.
    ------------------------------------------------------------------------*/
    int search(const ElementType& value) const;

private:
    NodePool<ElementType, NUM_NODES> nodePool;   // Memory pool
    int head;                                    // Index of first node
    int size;                                    // Number of nodes
};

/*============================================================================
    Implementation
============================================================================*/

/*----- Constructor ----------------------------------------------------------*/
template <typename ElementType, int NUM_NODES>
List<ElementType, NUM_NODES>::List()
    : head(NodePool<ElementType, NUM_NODES>::NULL_VALUE), size(0) {}

/*----- Destructor -----------------------------------------------------------*/
template <typename ElementType, int NUM_NODES>
List<ElementType, NUM_NODES>::~List() {
    clear();
}

/*----- Copy Constructor -----------------------------------------------------*/
template <typename ElementType, int NUM_NODES>
List<ElementType, NUM_NODES>::List(const List& other)
    : head(NodePool<ElementType, NUM_NODES>::NULL_VALUE), size(0) {

    int cur = other.head;
    while (cur != NodePool<ElementType, NUM_NODES>::NULL_VALUE) {
        insertAtPos(other.nodePool.getNodeConst(cur).data, size + 1);
        cur = other.nodePool.getNodeConst(cur).next;
    }
}

/*----- Assignment Operator --------------------------------------------------*/
template <typename ElementType, int NUM_NODES>
List<ElementType, NUM_NODES>&
List<ElementType, NUM_NODES>::operator=(const List& other) {

    if (this != &other) {
        clear();
        int cur = other.head;
        while (cur != NodePool<ElementType, NUM_NODES>::NULL_VALUE) {
            insertAtPos(other.nodePool.getNodeConst(cur).data, size + 1);
            cur = other.nodePool.getNodeConst(cur).next;
        }
    }
    return *this;
}

/*----- isEmpty ---------------------------------------------------------------*/
template <typename ElementType, int NUM_NODES>
bool List<ElementType, NUM_NODES>::isEmpty() const {
    return (size == 0);
}

/*----- isFull ----------------------------------------------------------------*/
template <typename ElementType, int NUM_NODES>
bool List<ElementType, NUM_NODES>::isFull() const {
    return (size == NUM_NODES);
}

/*----- getSize ---------------------------------------------------------------*/
template <typename ElementType, int NUM_NODES>
int List<ElementType, NUM_NODES>::getSize() const {
    return size;
}

/*----- getTop ----------------------------------------------------------------*/
template <typename ElementType, int NUM_NODES>
int List<ElementType, NUM_NODES>::getTop() const {
    return head;
}

/*----- getFFN ----------------------------------------------------------------*/
template <typename ElementType, int NUM_NODES>
int List<ElementType, NUM_NODES>::getFFN() {
    return nodePool.getFFN();
}

/*----- display ---------------------------------------------------------------*/
template <typename ElementType, int NUM_NODES>
void List<ElementType, NUM_NODES>::display() const {
    int cur = head;
    int pos = 1;

    while (cur != NodePool<ElementType, NUM_NODES>::NULL_VALUE) {
        cout << "[" << pos++ << "]: "
             << nodePool.getNodeConst(cur).data << " ";
        cur = nodePool.getNodeConst(cur).next;
    }
    cout << endl;
}

/*----- search ----------------------------------------------------------------*/
template <typename ElementType, int NUM_NODES>
int List<ElementType, NUM_NODES>::search(const ElementType& value) const {
    int cur = head;
    int pos = 1;

    while (cur != NodePool<ElementType, NUM_NODES>::NULL_VALUE) {
        if (nodePool.getNodeConst(cur).data == value)
            return pos;
        cur = nodePool.getNodeConst(cur).next;
        pos++;
    }
    return -1;
}

/*----- insertAtPos -----------------------------------------------------------*/
template <typename ElementType, int NUM_NODES>
void List<ElementType, NUM_NODES>::insertAtPos(const ElementType& value,
                                               int position) {
    if (position < 1 || position > size + 1 || isFull())
        return;

    int newNode = nodePool.allocate();
    nodePool.getNode(newNode).data = value;

    if (position == 1) {        // Insert at head
        nodePool.getNode(newNode).next = head;
        head = newNode;
    }
    else {                      // Insert in the middle
        int prev = head;
        for (int i = 1; i < position - 1; i++)
            prev = nodePool.getNode(prev).next;

        nodePool.getNode(newNode).next = nodePool.getNode(prev).next;
        nodePool.getNode(prev).next = newNode;
    }

    size++;
}

/*----- deleteAtPos -----------------------------------------------------------*/
template <typename ElementType, int NUM_NODES>
void List<ElementType, NUM_NODES>::deleteAtPos(int position) {
    if (isEmpty() || position < 1 || position > size)
        return;

    int toDelete;

    if (position == 1) {           // Delete head
        toDelete = head;
        head = nodePool.getNode(head).next;
    }
    else {                         // Delete in the middle
        int prev = head;
        for (int i = 1; i < position - 1; i++)
            prev = nodePool.getNode(prev).next;

        toDelete = nodePool.getNode(prev).next;
        nodePool.getNode(prev).next = nodePool.getNode(toDelete).next;
    }

    nodePool.deallocate(toDelete);
    size--;
}

/*----- clear -----------------------------------------------------------------*/
template <typename ElementType, int NUM_NODES>
void List<ElementType, NUM_NODES>::clear() {
    while (!isEmpty())
        deleteAtPos(1);
}

/*----- sort ------------------------------------------------------------------*/
template <typename ElementType, int NUM_NODES>
void List<ElementType, NUM_NODES>::sort() {
    if (size < 2)
        return;

    for (int i = 0; i < size - 1; i++) {
        int cur = head;
        int nxt = nodePool.getNode(cur).next;

        for (int j = 0; j < size - i - 1; j++) {

            if (nodePool.getNode(cur).data > nodePool.getNode(nxt).data) {
                ElementType temp = nodePool.getNode(cur).data;
                nodePool.getNode(cur).data = nodePool.getNode(nxt).data;
                nodePool.getNode(nxt).data = temp;
            }

            cur = nxt;
            nxt = nodePool.getNode(cur).next;
        }
    }
}

#endif // LIST_H
