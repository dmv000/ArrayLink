# PERSON 2: List Operations Implementer

## Your Assignment
**File to create: `List.h`**  
**Time estimate: 3-4 hours**

---

## Your Job (In Simple Terms)
Use the NodePool template class from Person 1 to build a complete linked list template class. You'll implement the "guts" of the list: inserting, removing, searching, and displaying.

----

## Prerequisites
⚠️ You NEED `NodePool.h` from Person 1 to be complete before you start.

Ask Person 1 to share their file with you!

---

## What You're Creating
**File: `List.h`**

This file contains a template class with multiple methods that make the list work.

---

## Step-by-Step Instructions

### STEP 1: Set Up the Header File

Create a new file called `List.h` and add this:

```cpp
/*-- List.h -----------------------------------------------------------------
  This header file defines a template for a List data type, implemented
  using a NodePool memory model.

  Template Parameters:
    - ElementType: Type of data stored in list nodes.
    - NUM_NODES: Maximum number of nodes allowed in the list.

  Basic operations:
    constructor:        Constructs an empty list
    copy constructor:   Makes a deep copy of a list
    destructor:         Deallocates list nodes
    = :                 Assignment operator
    insertAtPos:        Inserts a value at a specified position
    deleteAtPos:        Deletes a value at a specified position
    getSize:            Returns the number of elements
    isEmpty:            Checks if the list is empty
    isFull:             Checks if the list is full
    sort:               Sorts the list elements
    display:            Displays the list elements
    clear:              Clears the list
    getTop:             Returns the head index
    getFFN:             Returns the first free node index
    search:             Searches for a value in the list

  Class Invariant:
    1. List elements are stored in a fixed-size NodePool.
    2. head is the index of the first node, or NULL_VALUE if list is empty.
    3. size represents the current number of elements in the list.
---------------------------------------------------------------------------*/

#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "NodePool.h"

template <typename ElementType, int NUM_NODES>
class List {
public:
    List();
    ~List();
    List(const List& other);
    List& operator=(const List& other);
    
    void insertAtPos(const ElementType& value, int position);
    void deleteAtPos(int position);
    int getSize() const;
    bool isEmpty() const;
    bool isFull() const;
    void sort();
    void display() const;
    void clear();
    int getTop() const;
    int getFFN();
    int search(const ElementType& value) const;

private:
    NodePool<ElementType, NUM_NODES> nodePool; // Memory pool of nodes
    int head;                                  // Index of the first node
    int size;                                  // Current size of the list
};
```

**What this means:** 
- This is a **template class** that uses the NodePool template
- `head` is an integer index (NOT a pointer!)
- The NodePool is a **private member** of the class

---

### STEP 2: Constructor

**Purpose:** Create an empty list

```cpp
// Definition of List constructor
template <typename ElementType, int NUM_NODES>
List<ElementType, NUM_NODES>::List() : head(NULL_VALUE), size(0) {}
```

**Simple explanation:** `head = NULL_VALUE` and `size = 0` means "this list has nothing in it yet."

---

### STEP 3: isEmpty()

**Purpose:** Check if the list is empty

```cpp
// Definition of isEmpty function
template <typename ElementType, int NUM_NODES>
bool List<ElementType, NUM_NODES>::isEmpty() const {
    return (size == 0);
}
```

**Simple explanation:** If `size` is 0, there's nothing in the list.

---

### STEP 4: isFull()

**Purpose:** Check if the list is full

```cpp
// Definition of isFull function
template <typename ElementType, int NUM_NODES>
bool List<ElementType, NUM_NODES>::isFull() const {
    return size == NUM_NODES;
}
```

---

### STEP 5: getSize()

**Purpose:** Get the current number of elements

```cpp
// Definition of getSize function
template <typename ElementType, int NUM_NODES>
int List<ElementType, NUM_NODES>::getSize() const {
    return size;
}
```

---

### STEP 6: display()

**Purpose:** Print all elements in the list

```cpp
// Definition of display function
template <typename ElementType, int NUM_NODES>
void List<ElementType, NUM_NODES>::display() const {
    int current = head;
    if (current == NULL_VALUE) {
        std::cerr << "The list is empty. Nothing to display." << std::endl;
        return;
    }

    int index = 1;
    while (current != NULL_VALUE) {
        std::cout << "[" << index++ << "]: " << nodePool.getNodeConst(current).data << " ";
        current = nodePool.getNodeConst(current).next; // Move to next node
    }
    std::cout << std::endl;
}
```

**Simple explanation:** 
- Start at `head`
- Print the data at that index using `nodePool.getNodeConst()`
- Move to the next index
- Repeat until you hit -1 (NULL_VALUE)

---

### STEP 7: insertAtPos() - THE MOST IMPORTANT FUNCTION

**Purpose:** Add new data at a specific position (1-based indexing!)

⚠️ **This is the MOST CRITICAL function - read carefully!**

```cpp
// Definition of insertAtPos function
template <typename ElementType, int NUM_NODES>
void List<ElementType, NUM_NODES>::insertAtPos(const ElementType& value, int position) {
    if (position < 1 || position > size + 1) {
        std::cerr << "Invalid position. Use 1 to " << (size + 1) << "." << std::endl;
        return;
    }

    int newNodeIndex = nodePool.allocate(); // Allocate new node
    if (newNodeIndex == NULL_VALUE) return;

    nodePool.getNode(newNodeIndex).data = value; // Store value

    if (position == 1) { // Inserting at head
        nodePool.getNode(newNodeIndex).next = head;
        head = newNodeIndex;
    } else { // Inserting elsewhere
        int prev = head;
        for (int i = 1; i < position - 1; ++i) {
            prev = nodePool.getNode(prev).next; // Find previous node
        }
        nodePool.getNode(newNodeIndex).next = nodePool.getNode(prev).next;
        nodePool.getNode(prev).next = newNodeIndex;
    }

    ++size; // Increase list size
}
```

**🚨 CRITICAL ORDER (for position > 1):**
1. **FIRST:** `nodePool.getNode(newNodeIndex).next = nodePool.getNode(prev).next;` (save rest of list)
2. **SECOND:** `nodePool.getNode(prev).next = newNodeIndex;` (link new node in)

**Why this order matters:**
```
WRONG ORDER (loses data!):
1. nodePool.getNode(prev).next = newNodeIndex;  ← This breaks the link to rest of list!
2. nodePool.getNode(newNodeIndex).next = nodePool.getNode(prev).next;  ← Too late!

RIGHT ORDER (preserves data):
1. nodePool.getNode(newNodeIndex).next = nodePool.getNode(prev).next;  ← Save first
2. nodePool.getNode(prev).next = newNodeIndex;  ← Now safe to update
```

---

### STEP 8: deleteAtPos()

**Purpose:** Delete a node at a specific position (1-based indexing!)

```cpp
// Definition of deleteAtPos function
template <typename ElementType, int NUM_NODES>
void List<ElementType, NUM_NODES>::deleteAtPos(int position) {
    if (isEmpty()) {
        std::cerr << "List is empty." << std::endl;
        return;
    }

    if (position < 1 || position > size) {
        std::cerr << "Invalid position. Use 1 to " << size << "." << std::endl;
        return;
    }

    int toDelete;
    if (position == 1) { // Deleting head node
        toDelete = head;
        head = nodePool.getNode(head).next;
    } else { // Deleting non-head node
        int prev = head;
        for (int i = 1; i < position - 1; ++i) {
            prev = nodePool.getNode(prev).next; // Find previous node
        }
        toDelete = nodePool.getNode(prev).next; // Node to be deleted
        nodePool.getNode(prev).next = nodePool.getNode(toDelete).next; // Bypass the node
    }

    nodePool.deallocate(toDelete); // Free node
    --size; // Decrease list size
}
```

**Simple explanation:**
- To delete position 1: Move `head` to the next node, deallocate the old head
- To delete position > 1: Find the node before it, link around it, deallocate it

---

### STEP 9: search()

**Purpose:** Find where a value is in the list (returns 1-based position!)

```cpp
// Definition of search function
template <typename ElementType, int NUM_NODES>
int List<ElementType, NUM_NODES>::search(const ElementType& value) const {
    int current = head;
    int position = 1;

    while (current != NULL_VALUE) {
        if (nodePool.getNodeConst(current).data == value) {
            return position; // Found the value
        }
        current = nodePool.getNodeConst(current).next;
        ++position;
    }

    return -1; // Value not found
}
```

**Simple explanation:** Walk through the list comparing each data value. Return position if found, -1 if not.

---

### STEP 10: clear()

**Purpose:** Remove all elements from the list

```cpp
// Definition of clear function
template <typename ElementType, int NUM_NODES>
void List<ElementType, NUM_NODES>::clear() {
    while (!isEmpty()) {
        deleteAtPos(1); // Keep deleting head until empty
    }
}
```

---

### STEP 11: Destructor

**Purpose:** Clean up when the list is destroyed (prevents memory leaks)

```cpp
// Definition of List destructor
template <typename ElementType, int NUM_NODES>
List<ElementType, NUM_NODES>::~List() {
    clear();
}
```

**Simple explanation:** Use the clear() method to deallocate all nodes.

---

### STEP 12: Copy Constructor

**Purpose:** Make a deep copy when creating a new list from another

```cpp
// Definition of List copy constructor
template <typename ElementType, int NUM_NODES>
List<ElementType, NUM_NODES>::List(const List& other) : head(NULL_VALUE), size(0) {
    int current = other.head;
    while (current != NULL_VALUE) {
        insertAtPos(other.nodePool.getNodeConst(current).data, size + 1); // Insert each node's data
        current = other.nodePool.getNodeConst(current).next; // Move to next node
    }
}
```

---

### STEP 13: operator= (Copy Assignment)

**Purpose:** Make a deep copy of another list

```cpp
// Definition of List assignment operator
template <typename ElementType, int NUM_NODES>
List<ElementType, NUM_NODES>& List<ElementType, NUM_NODES>::operator=(const List& other) {
    if (this != &other) { // Check for self-assignment
        clear(); // Clear existing list
        int current = other.head;
        while (current != NULL_VALUE) {
            insertAtPos(other.nodePool.getNodeConst(current).data, size + 1); // Insert copied data
            current = other.nodePool.getNodeConst(current).next;
        }
    }
    return *this;
}
```

**⚠️ CRITICAL MISTAKE TO AVOID:**
```cpp
❌ WRONG WAY:
this->head = other.head;  // Both lists share same nodes!

✅ RIGHT WAY:
// Allocate new nodes and copy data (see algorithm above)
```

---

### STEP 14: Helper Methods

```cpp
// Definition of getTop function
template <typename ElementType, int NUM_NODES>
int List<ElementType, NUM_NODES>::getTop() const {
    return head;
}

// Definition of getFFN function
template <typename ElementType, int NUM_NODES>
int List<ElementType, NUM_NODES>::getFFN() {
    return nodePool.getFFN();
}
```

---

### STEP 15: sort() (Optional but Useful)

```cpp
// Definition of sort function
template <typename ElementType, int NUM_NODES>
void List<ElementType, NUM_NODES>::sort() {
    if (size < 2) return; // No need to sort if list is too small

    for (int i = 0; i < size - 1; ++i) {
        int current = head;
        int nextNode = nodePool.getNode(current).next;

        for (int j = 0; j < size - i - 1; ++j) {
            if (nodePool.getNode(current).data > nodePool.getNode(nextNode).data) {
                std::swap(nodePool.getNode(current).data, nodePool.getNode(nextNode).data); // Swap if needed
            }
            current = nextNode;
            nextNode = nodePool.getNode(current).next;
        }
    }
}
```

---

### STEP 16: Close the Header File

Add this at the very end:

```cpp
#endif
```

---

## ✅ Testing Your Code

Create `test_list.cpp`:

```cpp
#include "NodePool.h"
#include "List.h"
#include <iostream>
using namespace std;

int main() {
    cout << "=== Testing List ===" << endl;
    
    // Create a list of strings with capacity 100
    List<string, 100> list;
    
    // Test insert
    cout << "\n--- Testing Insert ---" << endl;
    list.insertAtPos("Alice", 1);
    list.insertAtPos("Bob", 2);
    list.insertAtPos("Charlie", 3);
    list.display();
    
    // Test search
    cout << "\n--- Testing Search ---" << endl;
    int pos = list.search("Bob");
    cout << "Bob found at position: " << pos << endl;
    
    // Test delete
    cout << "\n--- Testing Delete ---" << endl;
    list.deleteAtPos(2);  // Remove Bob
    list.display();
    
    // Test isEmpty
    cout << "\n--- Testing isEmpty ---" << endl;
    cout << "Is empty? " << (list.isEmpty() ? "Yes" : "No") << endl;
    
    return 0;
}
```

**Compile and run:**
```bash
g++ -std=c++11 test_list.cpp -o test_list
./test_list
```

---

## 📝 Summary - What You Need to Deliver

**File: `List.h`** containing:
- ✅ Template class definition
- ✅ Constructor and Destructor
- ✅ Copy Constructor
- ✅ isEmpty(), isFull(), getSize()
- ✅ display()
- ✅ insertAtPos() - handles both position 1 and position > 1
- ✅ deleteAtPos() - handles both position 1 and position > 1
- ✅ search()
- ✅ clear()
- ✅ operator=()
- ✅ sort() (optional)
- ✅ All implementations inline in the header file

---

## 🐛 Common Mistakes to Avoid

### Mistake 1: Forgetting template syntax
❌ Wrong: `class List {`
✅ Correct: `template <typename ElementType, int NUM_NODES> class List {`

### Mistake 2: Wrong link update order in insertAtPos()
❌ Wrong:
```cpp
nodePool.getNode(prev).next = newIndex;          // Breaks link to rest!
nodePool.getNode(newIndex).next = nodePool.getNode(prev).next;  // Too late!
```
✅ Correct:
```cpp
nodePool.getNode(newIndex).next = nodePool.getNode(prev).next;  // Save rest first!
nodePool.getNode(prev).next = newIndex;             // Then update
```

### Mistake 3: Not deallocating removed nodes
❌ Wrong:
```cpp
head = nodePool.getNode(head).next;  // Just moves pointer - leaks node!
```
✅ Correct:
```cpp
temp = head;
head = nodePool.getNode(head).next;
nodePool.deallocate(temp);  // Return to pool!
```

### Mistake 4: Accessing nodePool array directly
❌ Wrong:
```cpp
nodePool.nodepool[i].data = value;  // Accessing private member!
```
✅ Correct:
```cpp
nodePool.getNode(i).data = value;  // Use public accessor!
```

---

## When You're Done

1. Make sure your file compiles without errors
2. Run the test program and verify it works
3. Share `List.h` with Person 3
4. **Important:** Person 3 needs your file before they can complete the project!

---

## Questions to Check Your Understanding

Before submitting, make sure you can answer:
1. Why must we update links in a specific order during insert? (Answer: To not lose references to the rest of the list)
2. What's the difference between `head = nodePool.getNode(head).next` and proper node removal? (Answer: Proper removal also calls deallocate())
3. Why can't we just copy `head` in operator=? (Answer: Would create shallow copy sharing nodes)
4. Why is position 1-based instead of 0-based? (Answer: Convention for this implementation - user-friendly)

---
