# PERSON 1: Node Pool Manager

## Your Assignment 
**File to create: `NodePool.h`**  
**Time estimate: 1-2 hours**

---

## Your Job (In Simple Terms)
Create a template class "memory manager" that keeps track of which array slots are free and which are in use. You'll write a **template class** with encapsulated memory management.

----

## What You're Creating
**File: `NodePool.h`**

This file contains:
1. A template class with a `NodeType` structure (to store data)
2. Constants for NULL_VALUE
3. Class methods for memory management
4. All implementations inline in the header

---

## Step-by-Step Instructions

### STEP 1: Create the Template Class Structure

Create a new file called `NodePool.h` and add this:

```cpp
/*-- NodePool.h -------------------------------------------------------------
  This header file defines a template class for managing a pool of linked nodes.
  It is a memory-efficient way to implement dynamic lists or stacks using a
  fixed-size array with manual memory handling.

  Template Parameters:
    - ElementType: The type of data each node will store.
    - NUM_NODES:   The maximum number of nodes in the pool.

  Basic operations:
    constructor:      Initializes the node pool and links all nodes in a free list.
    allocate:         Allocates a node from the pool and returns its index.
    deallocate:       Frees a node by returning it to the free list.
    getNode:          Returns a reference to a node at a given index (modifiable).
    getNodeConst:     Returns a const reference to a node at a given index.
    getFFN:           Returns the current index of the first free node.
    setFFN:           Sets the index of the first free node.

  Class Invariant:
    1. nodepool is a fixed-size array of NUM_NODES nodes.
    2. Each node contains:
        - data: of type ElementType
        - next: the index of the next node in the list, or -1 if none
    3. ffn (first free node) points to the head of the free node list.
---------------------------------------------------------------------------*/

#ifndef NODEPOOL_H
#define NODEPOOL_H

#include <iostream>

static const int NULL_VALUE = -1;

template <typename ElementType, int NUM_NODES>
class NodePool {
public:
    struct NodeType {
        ElementType data;  // Data element stored in the node
        int next;          // Index of the next node in list or free list
    };

    NodePool();
    int allocate();
    void deallocate(int pos);
    NodeType& getNode(int pos);
    const NodeType& getNodeConst(int pos) const;
    int getFFN() const;
    void setFFN(int value);

private:
    NodeType nodepool[NUM_NODES]; // Array of nodes
    int ffn;                      // Index of first free node (First Free Node)
};
```

**What this means:** 
- The class is a **template** so it can work with any data type (string, int, etc.)
- Each node stores data and an integer that tells us where the next node is
- Everything is **encapsulated** in the class (no global variables!)

---

### STEP 2: Constructor - Initialize the Pool

Add this right after the class definition:

```cpp
//=== FUNCTION DEFINITIONS ===

// Definition of NodePool constructor
template <typename ElementType, int NUM_NODES>
NodePool<ElementType, NUM_NODES>::NodePool() {
    ffn = 0; // First free node index is set to 0
    for (int i = 0; i < NUM_NODES - 1; ++i) {
        nodepool[i].next = i + 1; // Each node points to the next node
    }
    nodepool[NUM_NODES - 1].next = NULL_VALUE; // Last node points to -1 (no next node)
}
```

**What this does:** Links all nodes together to form the initial free list.

**Visual result after construction:**
```
Index: [0] [1] [2] [3] [4] [5] [6] [7] [8] [9]
Next:   1   2   3   4   5   6   7   8   9  -1
        ↑
    ffn starts here
```

---

### STEP 3: allocate() Method

**Purpose:** Get one free node from the pool (like calling `new` in normal C++)

**Copy this EXACTLY:**

```cpp
// Definition of allocate function
template <typename ElementType, int NUM_NODES>
int NodePool<ElementType, NUM_NODES>::allocate() {
    if (ffn == NULL_VALUE) { // If no free nodes are available
        std::cerr << "Error: No free nodes available." << std::endl;
        return NULL_VALUE; // Return -1 to indicate failure
    }
    int p = ffn; // Save current first free node
    ffn = nodepool[ffn].next; // Update ffn to next free node
    nodepool[p].next = NULL_VALUE; // Initialize the allocated node
    return p; 
}
```

**Example:**
```
BEFORE: ffn = 0, nodepool[0].next = 1
Call allocate()
AFTER:  ffn = 1, returns 0

(We gave away node 0, now free list starts at 1)
```

---

### STEP 4: deallocate() Method

**Purpose:** Return a used node back to the free pool (like calling `delete` in normal C++)

**Copy this EXACTLY:**

```cpp
// Definition of deallocate function
template <typename ElementType, int NUM_NODES>
void NodePool<ElementType, NUM_NODES>::deallocate(int pos) {
    if (pos < 0 || pos >= NUM_NODES) {
        std::cerr << "Error: Invalid index " << pos << " in deallocate()" << std::endl;
        return;
    }
    nodepool[pos].next = ffn; // Link node to current free list head
    ffn = pos;
}
```

**Example:**
```
BEFORE: ffn = 3, we want to free node 7
Execute: nodepool[7].next = 3, then ffn = 7
AFTER:  ffn = 7, nodepool[7].next = 3

(Node 7 is now at the front of the free list)
```

---

### STEP 5: Accessor Methods

Add these methods to access nodes:

```cpp
// Definition of getNode function
template <typename ElementType, int NUM_NODES>
typename NodePool<ElementType, NUM_NODES>::NodeType&
NodePool<ElementType, NUM_NODES>::getNode(int pos) {
    // Access a node for modification
    return nodepool[pos];
}


// Definition of getNodeConst function
template <typename ElementType, int NUM_NODES>
const typename NodePool<ElementType, NUM_NODES>::NodeType&
NodePool<ElementType, NUM_NODES>::getNodeConst(int pos) const {
    // Access a node without modifying it (const)
    return nodepool[pos];
}


// Definition of getFFN function
template <typename ElementType, int NUM_NODES>
int NodePool<ElementType, NUM_NODES>::getFFN() const {
    // Return the current first free node index
    return ffn;
}

// Definition of setFFN function
template <typename ElementType, int NUM_NODES>
void NodePool<ElementType, NUM_NODES>::setFFN(int value) {
    // Set a new value for first free node index
    ffn = value;
}
```

---

### STEP 6: Close the Header File

Add this at the very end:

```cpp
#endif
```

---

## ✅ Testing Your Code

Create `test_pool.cpp`:

```cpp
#include "NodePool.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    cout << "=== Testing Node Pool ===" << endl;
    
    // Create a NodePool for strings with 10 nodes
    NodePool<string, 10> pool;
    
    // Test 1: Check initial state
    cout << "\n--- Initial State ---" << endl;
    cout << "First free node: " << pool.getFFN() << endl;
    
    // Test 2: Allocate some nodes
    cout << "\n--- Allocating 3 nodes ---" << endl;
    int n1 = pool.allocate();
    int n2 = pool.allocate();
    int n3 = pool.allocate();
    cout << "Allocated nodes: " << n1 << ", " << n2 << ", " << n3 << endl;
    cout << "First free node now: " << pool.getFFN() << endl;
    
    // Test 3: Use the nodes
    cout << "\n--- Storing data ---" << endl;
    pool.getNode(n1).data = "Alice";
    pool.getNode(n2).data = "Bob";
    pool.getNode(n3).data = "Charlie";
    cout << "Data in n1: " << pool.getNode(n1).data << endl;
    
    // Test 4: Deallocate one
    cout << "\n--- Deallocating node " << n2 << " ---" << endl;
    pool.deallocate(n2);
    cout << "First free node now: " << pool.getFFN() << endl;
    
    // Test 5: Allocate again (should reuse freed node)
    cout << "\n--- Allocating one more ---" << endl;
    int n4 = pool.allocate();
    cout << "Got node: " << n4 << " (should be " << n2 << ")" << endl;
    
    return 0;
}
```

**Compile and run:**
```bash
g++ -std=c++11 test_pool.cpp -o test_pool
./test_pool
```

---

## 📝 Summary - What You Need to Deliver

**File: `NodePool.h`** containing:
- ✅ Template class definition with ElementType and NUM_NODES parameters
- ✅ NodeType structure inside the class
- ✅ Constructor that initializes the free list
- ✅ allocate() method
- ✅ deallocate() method
- ✅ getNode() and getNodeConst() accessor methods
- ✅ getFFN() and setFFN() methods
- ✅ All implementations inline in the header file

---

## 🐛 Common Mistakes to Avoid

### Mistake 1: Forgetting template syntax
❌ Wrong: `class NodePool {`
✅ Correct: `template <typename ElementType, int NUM_NODES> class NodePool {`

### Mistake 2: Using wrong types
❌ Wrong: `NodeType* next;` (real pointer)
✅ Correct: `int next;` (integer index)

### Mistake 3: Global variables
❌ Wrong: Having `Node node[10];` outside the class
✅ Correct: Having `NodeType nodepool[NUM_NODES];` as a private member

### Mistake 4: Wrong loop bounds
❌ Wrong: `for (int i = 0; i < NUM_NODES; i++)`
✅ Correct: `for (int i = 0; i < NUM_NODES - 1; i++)` in constructor
(The last node needs special handling!)

---

## 📤 When You're Done

1. Make sure your file compiles without errors
2. Run the test program and verify output is correct
3. Share `NodePool.h` with your teammates
4. **Important:** Person 2 needs your file before they can start!

---

## ❓ Questions to Check Your Understanding

Before submitting, make sure you can answer:
1. What does `ffn` stand for and what does it point to? (Answer: First Free Node - the index of the first free node)
2. What does `allocate()` return? (Answer: An integer index, or -1 if full)
3. Why is this a template class? (Answer: So it can work with any data type: string, int, custom classes, etc.)
4. What does `nodepool[5].next = 7` mean? (Answer: Node at index 5 points to node at index 7)

---
