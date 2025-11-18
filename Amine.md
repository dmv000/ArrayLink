# PERSON 1: Node Pool Manager

## Your Assignment 
**File to create: `nodePool.h`**  
**Time estimate: 1-2 hours**

---

## Your Job (In Simple Terms)
Create a "memory manager" that keeps track of which array slots are free and which are in use. You'll write **only 3 functions** with algorithms already provided.

---

## What You're Creating
**File: `nodePool.h`**

This file contains:
1. A `Node` structure (to store data)
2. Constants and global variables
3. Three simple functions

---

## Step-by-Step Instructions

### STEP 1: Create the Node Structure

Create a new file called `nodePool.h` and add this:

```cpp
#ifndef NODEPOOL_H
#define NODEPOOL_H

#include <iostream>
#include <string>
using namespace std;

// Choose ONE data type for your list (I recommend string for names)
typedef string ElementType;  // You can change to 'int' if you prefer numbers

struct Node {
    ElementType data;   // The actual data stored
    int next;           // Integer "pointer" to next node (NOT a real pointer!)
    
    // Default constructor
    Node() {
        next = -1;  // Initialize to "null"
    }
    
    // Constructor with data
    Node(ElementType value) {
        data = value;
        next = -1;
    }
};
```

**What this means:** Each node stores data and an integer that tells us where the next node is in the array.

---

### STEP 2: Define Constants and Global Variables

Add this right after the Node structure:

```cpp
// Constants
const int NULL_VALUE = -1;      // Our version of "null pointer"
const int POOL_SIZE = 10;       // Array holds 10 nodes

// Global variables (the actual storage!)
Node node[POOL_SIZE];           // The array that holds everything
int freeList = 0;               // Points to first available node
```

**What this means:**
- `NULL_VALUE = -1`: When next = -1, it means "end of list"
- `POOL_SIZE = 10`: We have 10 slots in our array
- `node[POOL_SIZE]`: This is the actual array storage
- `freeList`: Keeps track of which nodes are available to use

---

### STEP 3: Function 1 - initializePool()

**Purpose:** Set up the array so all 10 nodes are linked together as "available"

**Copy this EXACTLY:**

```cpp
/**
 * Function: initializePool
 * Purpose: Links all nodes together to form the initial free list
 * How it works: node[0] points to node[1], node[1] points to node[2], etc.
 */
void initializePool() {
    // Link all nodes in a chain: 0->1->2->3->4->5->6->7->8->9->NULL
    for (int i = 0; i < POOL_SIZE - 1; i++) {
        node[i].next = i + 1;  // Each node points to the next index
    }
    
    // Last node points to NULL_VALUE (end of free list)
    node[POOL_SIZE - 1].next = NULL_VALUE;
    
    // Free list starts at index 0
    freeList = 0;
    
    cout << "✓ Pool initialized: All " << POOL_SIZE << " nodes are free" << endl;
}
```

**Visual result after running:**
```
Index: [0] [1] [2] [3] [4] [5] [6] [7] [8] [9]
Next:   1   2   3   4   5   6   7   8   9  -1
        ↑
    freeList starts here
```

---

### STEP 4: Function 2 - allocate()

**Purpose:** Get one free node from the pool (like calling `new` in normal C++)

**Copy this EXACTLY:**

```cpp
/**
 * Function: allocate
 * Purpose: Gives you one free node to use
 * Returns: The index of a free node, or NULL_VALUE if pool is full
 * How it works: Takes the first node from the free list
 */
int allocate() {
    // Check if pool is empty
    if (freeList == NULL_VALUE) {
        cout << "✗ ERROR: Pool is full! No more nodes available." << endl;
        return NULL_VALUE;
    }
    
    // Take the first free node
    int allocatedIndex = freeList;           // Remember which node we're giving away
    freeList = node[freeList].next;          // Move freeList to next available node
    
    cout << "✓ Allocated node at index " << allocatedIndex << endl;
    return allocatedIndex;
}
```

**Example:**
```
BEFORE: freeList = 0, node[0].next = 1
Call allocate()
AFTER:  freeList = 1, returns 0

(We gave away node 0, now free list starts at 1)
```

---

### STEP 5: Function 3 - deallocate()

**Purpose:** Return a used node back to the free pool (like calling `delete` in normal C++)

**Copy this EXACTLY:**

```cpp
/**
 * Function: deallocate
 * Purpose: Returns a used node back to the free pool
 * Parameters: index - the array index of the node to free
 * How it works: Inserts the node at the FRONT of the free list
 */
void deallocate(int index) {
    // Check for invalid index
    if (index < 0 || index >= POOL_SIZE) {
        cout << "✗ ERROR: Invalid index " << index << endl;
        return;
    }
    
    // Insert at front of free list (LIFO - Last In First Out)
    node[index].next = freeList;    // This node now points to old free list start
    freeList = index;                // Free list now starts at this node
    
    cout << "✓ Deallocated node at index " << index << endl;
}
```

**Example:**
```
BEFORE: freeList = 3, we want to free node 7
Execute: node[7].next = 3, then freeList = 7
AFTER:  freeList = 7, node[7].next = 3

(Node 7 is now at the front of the free list)
```

---

### STEP 6: Add a Helper Function (For Testing)

This helps visualize the free list:

```cpp
/**
 * Function: displayFreeList
 * Purpose: Shows which nodes are currently free
 * Useful for debugging
 */
void displayFreeList() {
    cout << "\n--- Free List Status ---" << endl;
    cout << "Free list starts at index: " << freeList << endl;
    
    if (freeList == NULL_VALUE) {
        cout << "Free list is EMPTY (pool is full)" << endl;
        return;
    }
    
    cout << "Free nodes: ";
    int current = freeList;
    int count = 0;
    
    while (current != NULL_VALUE) {
        cout << current;
        current = node[current].next;
        count++;
        if (current != NULL_VALUE) cout << " -> ";
    }
    cout << " -> NULL" << endl;
    cout << "Total free nodes: " << count << endl;
}
```

---

### STEP 7: Close the Header File

Add this at the very end:

```cpp
#endif // NODEPOOL_H
```

---

## ✅ Testing Your Code

Create a simple test file `test_pool.cpp`:

```cpp
#include "nodePool.h"

int main() {
    cout << "=== Testing Node Pool ===" << endl;
    
    // Test 1: Initialize
    initializePool();
    displayFreeList();
    
    // Test 2: Allocate some nodes
    cout << "\n--- Allocating 3 nodes ---" << endl;
    int n1 = allocate();
    int n2 = allocate();
    int n3 = allocate();
    displayFreeList();
    
    // Test 3: Deallocate one
    cout << "\n--- Deallocating node " << n2 << " ---" << endl;
    deallocate(n2);
    displayFreeList();
    
    // Test 4: Allocate again (should reuse freed node)
    cout << "\n--- Allocating one more ---" << endl;
    int n4 = allocate();
    cout << "Got node: " << n4 << " (should be " << n2 << ")" << endl;
    displayFreeList();
    
    return 0;
}
```

**Compile and run:**
```bash
g++ test_pool.cpp -o test_pool
./test_pool
```

**Expected output:**
```
✓ Pool initialized: All 10 nodes are free
Free nodes: 0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> NULL
✓ Allocated node at index 0
✓ Allocated node at index 1
✓ Allocated node at index 2
Free nodes: 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> NULL
✓ Deallocated node at index 1
Free nodes: 1 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> NULL
✓ Allocated node at index 1
Got node: 1 (should be 1)
```

---

## 📝 Summary - What You Need to Deliver

**File: `nodePool.h`** containing:
- ✅ Node structure with constructors
- ✅ Constants (NULL_VALUE, POOL_SIZE)
- ✅ Global array and freeList variable
- ✅ initializePool() function
- ✅ allocate() function
- ✅ deallocate() function
- ✅ displayFreeList() helper function

---

## 🐛 Common Mistakes to Avoid

### Mistake 1: Forgetting #ifndef guards
❌ Wrong: Starting the file directly with `#include`
✅ Correct: Use `#ifndef NODEPOOL_H` at the top and `#endif` at the bottom

### Mistake 2: Using wrong types
❌ Wrong: `Node* next;` (real pointer)
✅ Correct: `int next;` (integer index)

### Mistake 3: Wrong loop bounds
❌ Wrong: `for (int i = 0; i < POOL_SIZE; i++)`
✅ Correct: `for (int i = 0; i < POOL_SIZE - 1; i++)` in initializePool()
(The last node needs special handling!)

---

## 📤 When You're Done

1. Make sure your file compiles without errors
2. Run the test program and verify output matches expected
3. Share `nodePool.h` with your teammates
4. **Important:** Person 2 needs your file before they can start!

---

## ❓ Questions to Check Your Understanding

Before submitting, make sure you can answer:
1. What does `freeList` point to? (Answer: The index of the first free node)
2. What does `allocate()` return? (Answer: An integer index, or -1 if full)
3. What does `node[5].next = 7` mean? (Answer: Node at index 5 points to node at index 7)

---



