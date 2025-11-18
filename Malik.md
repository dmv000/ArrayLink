# PERSON 2: List Operations Implementer

## Your Assignment
**File to create: `arrayBasedList.h`**  
**Time estimate: 3-4 hours**

---

## Your Job (In Simple Terms)
Use the node pool functions from Person 1 to build a complete linked list class. You'll implement the "guts" of the list: inserting, removing, searching, and displaying.

---

## Prerequisites
⚠️ You NEED `nodePool.h` from Person 1 to be complete before you start.

Ask Person 1 to share their file with you!

---

## What You're Creating
**File: `arrayBasedList.h`**

This file contains a class with 8 methods that make the list work.

---

## Step-by-Step Instructions

### STEP 1: Set Up the Header File

Create a new file called `arrayBasedList.h` and add this:

```cpp
#ifndef ARRAYBASEDLIST_H
#define ARRAYBASEDLIST_H

#include "nodePool.h"  // You need this from Person 1!

class ArrayBasedList {
private:
    int first;  // Index of the first node in the list (NOT a pointer!)
    
public:
    // Constructor
    ArrayBasedList();
    
    // Destructor
    ~ArrayBasedList();
    
    // Basic operations
    bool isEmpty();
    void display();
    int search(ElementType data);
    bool insert(ElementType data, int position);
    bool remove(int position);
    
    // Advanced operation
    ArrayBasedList& operator=(const ArrayBasedList& other);
};
```

---

### STEP 2: Constructor

**Purpose:** Create an empty list

```cpp
/**
 * Constructor
 * Purpose: Creates an empty list
 * How it works: Sets first to NULL_VALUE (meaning no nodes in list)
 */
ArrayBasedList::ArrayBasedList() {
    first = NULL_VALUE;  // Empty list
    cout << "✓ New empty list created" << endl;
}
```

**Simple explanation:** `first = NULL_VALUE` means "this list has nothing in it yet."

---

### STEP 3: isEmpty()

**Purpose:** Check if the list is empty

```cpp
/**
 * Function: isEmpty
 * Returns: true if list is empty, false otherwise
 * How it works: Empty list means first == NULL_VALUE
 */
bool ArrayBasedList::isEmpty() {
    return (first == NULL_VALUE);
}
```

**Simple explanation:** If `first` is -1, there's nothing in the list.

---

### STEP 4: display()

**Purpose:** Print all elements in the list

```cpp
/**
 * Function: display
 * Purpose: Shows all elements in order
 * How it works: Start at first, follow the next links until NULL_VALUE
 */
void ArrayBasedList::display() {
    if (isEmpty()) {
        cout << "List is EMPTY" << endl;
        return;
    }
    
    cout << "List contents: ";
    int current = first;  // Start at first node
    
    while (current != NULL_VALUE) {
        cout << node[current].data;  // Print data at current index
        current = node[current].next;  // Move to next node
        if (current != NULL_VALUE) cout << " -> ";
    }
    cout << " -> NULL" << endl;
    
    // Also show the index chain (helpful for debugging)
    cout << "Index chain: first=" << first;
    current = first;
    while (current != NULL_VALUE) {
        cout << " -> [" << current << "]";
        current = node[current].next;
    }
    cout << " -> NULL" << endl;
}
```

**Simple explanation:** 
- Start at `first`
- Print the data at that index
- Move to the next index
- Repeat until you hit -1 (NULL_VALUE)

---

### STEP 5: insert() - THE MOST IMPORTANT FUNCTION

**Purpose:** Add new data at a specific position

⚠️ **This is the MOST CRITICAL function - read carefully!**

This function has TWO cases:

```cpp
/**
 * Function: insert
 * Purpose: Inserts new data at specified position (0 = beginning)
 * Parameters:
 *   - data: the value to insert
 *   - position: where to insert (0-based index)
 * Returns: true if successful, false if failed
 */
bool ArrayBasedList::insert(ElementType data, int position) {
    // Validate position
    if (position < 0) {
        cout << "✗ ERROR: Position cannot be negative" << endl;
        return false;
    }
    
    // CASE 1: Insert at position 0 (beginning of list)
    if (position == 0) {
        // Get a free node
        int newIndex = allocate();
        if (newIndex == NULL_VALUE) {
            cout << "✗ ERROR: Pool is full, cannot insert" << endl;
            return false;
        }
        
        // Fill the new node
        node[newIndex].data = data;
        node[newIndex].next = first;  // New node points to old first
        
        // Update list to start at new node
        first = newIndex;
        
        cout << "✓ Inserted '" << data << "' at position 0" << endl;
        return true;
    }
    
    // CASE 2: Insert at position > 0 (after some nodes)
    else {
        // Get a free node
        int newIndex = allocate();
        if (newIndex == NULL_VALUE) {
            cout << "✗ ERROR: Pool is full, cannot insert" << endl;
            return false;
        }
        
        // Find the node BEFORE where we want to insert
        int current = first;
        for (int i = 0; i < position - 1; i++) {
            if (current == NULL_VALUE) {
                cout << "✗ ERROR: Position " << position << " is out of bounds" << endl;
                deallocate(newIndex);  // Give back the node we got
                return false;
            }
            current = node[current].next;
        }
        
        // Check if we went too far
        if (current == NULL_VALUE) {
            cout << "✗ ERROR: Position " << position << " is out of bounds" << endl;
            deallocate(newIndex);
            return false;
        }
        
        // Insert the new node after 'current'
        node[newIndex].data = data;
        node[newIndex].next = node[current].next;  // ⚠️ IMPORTANT: Do this FIRST!
        node[current].next = newIndex;              // Then update predecessor
        
        cout << "✓ Inserted '" << data << "' at position " << position << endl;
        return true;
    }
}
```

**🚨 CRITICAL ORDER (for position > 0):**
1. **FIRST:** `node[newIndex].next = node[current].next;` (save rest of list)
2. **SECOND:** `node[current].next = newIndex;` (link new node in)

**Why this order matters:**
```
WRONG ORDER (loses data!):
1. node[current].next = newIndex;  ← This breaks the link to rest of list!
2. node[newIndex].next = node[current].next;  ← Too late, the link is lost!

RIGHT ORDER (preserves data):
1. node[newIndex].next = node[current].next;  ← Save the rest of list first
2. node[current].next = newIndex;  ← Now safe to update
```

---

### STEP 6: remove()

**Purpose:** Delete a node at a specific position

```cpp
/**
 * Function: remove
 * Purpose: Removes node at specified position
 * Parameters: position - which node to remove (0-based)
 * Returns: true if successful, false if failed
 */
bool ArrayBasedList::remove(int position) {
    // Check if list is empty
    if (isEmpty()) {
        cout << "✗ ERROR: Cannot remove from empty list" << endl;
        return false;
    }
    
    if (position < 0) {
        cout << "✗ ERROR: Position cannot be negative" << endl;
        return false;
    }
    
    // CASE 1: Remove position 0 (first node)
    if (position == 0) {
        int temp = first;                    // Remember which node to delete
        first = node[first].next;            // Move first to next node
        deallocate(temp);                    // Return node to free pool
        
        cout << "✓ Removed node at position 0" << endl;
        return true;
    }
    
    // CASE 2: Remove position > 0
    else {
        // Find the node BEFORE the one to delete
        int current = first;
        for (int i = 0; i < position - 1; i++) {
            if (current == NULL_VALUE || node[current].next == NULL_VALUE) {
                cout << "✗ ERROR: Position " << position << " is out of bounds" << endl;
                return false;
            }
            current = node[current].next;
        }
        
        // Check if the node to delete exists
        int temp = node[current].next;
        if (temp == NULL_VALUE) {
            cout << "✗ ERROR: Position " << position << " is out of bounds" << endl;
            return false;
        }
        
        // Bypass the node to delete
        node[current].next = node[temp].next;  // Link around the deleted node
        deallocate(temp);                       // Return it to free pool
        
        cout << "✓ Removed node at position " << position << endl;
        return true;
    }
}
```

**Simple explanation:**
- To delete position 0: Move `first` to the next node, free the old first
- To delete position > 0: Find the node before it, link around it, free it

**Visual Example:**
```
BEFORE: first=7, [Brown(7)] -> [Jones(1)] -> [Smith(3)] -> NULL
Remove position 1 (Jones):

Step 1: Find node before position 1 → current = 7 (Brown)
Step 2: temp = node[7].next = 1 (Jones)
Step 3: node[7].next = node[1].next = 3 (Brown now points to Smith)
Step 4: deallocate(1) (Return Jones to free pool)

AFTER: first=7, [Brown(7)] -> [Smith(3)] -> NULL
```

---

### STEP 7: search()

**Purpose:** Find where a value is in the list

```cpp
/**
 * Function: search
 * Purpose: Finds a value in the list
 * Parameters: data - the value to search for
 * Returns: Position where found (0-based), or -1 if not found
 */
int ArrayBasedList::search(ElementType data) {
    int current = first;
    int position = 0;
    
    while (current != NULL_VALUE) {
        if (node[current].data == data) {
            cout << "✓ Found '" << data << "' at position " << position << endl;
            return position;
        }
        current = node[current].next;
        position++;
    }
    
    cout << "✗ '" << data << "' not found in list" << endl;
    return -1;  // Not found
}
```

**Simple explanation:** Walk through the list comparing each data value. Return position if found, -1 if not.

---

### STEP 8: Destructor

**Purpose:** Clean up when the list is destroyed (prevents memory leaks)

```cpp
/**
 * Destructor
 * Purpose: Returns all nodes in this list back to the free pool
 * How it works: Walks through list and deallocates every node
 * IMPORTANT: This prevents "memory leaks" in our simulated system
 */
ArrayBasedList::~ArrayBasedList() {
    int current = first;
    
    while (current != NULL_VALUE) {
        int temp = current;              // Remember current node
        current = node[current].next;    // Move to next node
        deallocate(temp);                // Free the remembered node
    }
    
    first = NULL_VALUE;
    cout << "✓ List destroyed, all nodes returned to pool" << endl;
}
```

**Simple explanation:** Walk through the entire list and call `deallocate()` on every node.

---

### STEP 9: operator= (Copy Assignment)

**Purpose:** Make a deep copy of another list

```cpp
/**
 * Function: operator=
 * Purpose: Makes a complete copy of another list
 * IMPORTANT: Must allocate NEW nodes and copy data (not just copy indices!)
 */
ArrayBasedList& ArrayBasedList::operator=(const ArrayBasedList& other) {
    // Check for self-assignment (list1 = list1)
    if (this == &other) {
        return *this;
    }
    
    // Step 1: Clear current list (deallocate all nodes)
    int current = first;
    while (current != NULL_VALUE) {
        int temp = current;
        current = node[current].next;
        deallocate(temp);
    }
    first = NULL_VALUE;
    
    // Step 2: If source is empty, we're done
    if (other.first == NULL_VALUE) {
        return *this;
    }
    
    // Step 3: Copy first node
    first = allocate();
    if (first == NULL_VALUE) {
        cout << "✗ ERROR: Pool exhausted during copy" << endl;
        return *this;
    }
    node[first].data = node[other.first].data;
    
    // Step 4: Copy remaining nodes
    int currentThis = first;
    int currentOther = node[other.first].next;
    
    while (currentOther != NULL_VALUE) {
        int newIndex = allocate();
        if (newIndex == NULL_VALUE) {
            cout << "✗ ERROR: Pool exhausted during copy" << endl;
            return *this;
        }
        
        node[newIndex].data = node[currentOther].data;
        node[currentThis].next = newIndex;
        
        currentThis = newIndex;
        currentOther = node[currentOther].next;
    }
    
    node[currentThis].next = NULL_VALUE;
    cout << "✓ List copied successfully" << endl;
    return *this;
}
```

**Simple explanation:**
1. Clear the current list
2. Walk through the other list
3. Allocate new nodes and copy data values
4. Link them together

**⚠️ CRITICAL MISTAKE TO AVOID:**
```cpp
❌ WRONG WAY:
this->first = other.first;  // Both lists share same nodes!

✅ RIGHT WAY:
// Allocate new nodes and copy data (see algorithm above)
```

---

### STEP 10: Close the Header File

Add this at the very end:

```cpp
#endif // ARRAYBASEDLIST_H
```

---

## ✅ Testing Your Code

Create `test_list.cpp`:

```cpp
#include "nodePool.h"
#include "arrayBasedList.h"

int main() {
    cout << "=== Testing ArrayBasedList ===" << endl;
    
    // Initialize the pool first!
    initializePool();
    
    // Create a list
    ArrayBasedList list;
    
    // Test insert
    cout << "\n--- Testing Insert ---" << endl;
    list.insert("Alice", 0);
    list.insert("Bob", 1);
    list.insert("Charlie", 2);
    list.display();
    
    // Test search
    cout << "\n--- Testing Search ---" << endl;
    list.search("Bob");
    list.search("David");
    
    // Test remove
    cout << "\n--- Testing Remove ---" << endl;
    list.remove(1);  // Remove Bob
    list.display();
    
    // Test isEmpty
    cout << "\n--- Testing isEmpty ---" << endl;
    cout << "Is empty? " << (list.isEmpty() ? "Yes" : "No") << endl;
    
    return 0;
}
```

**Compile and run:**
```bash
g++ test_list.cpp -o test_list
./test_list
```

---

## 📝 Summary - What You Need to Deliver

**File: `arrayBasedList.h`** containing:
- ✅ ArrayBasedList class definition
- ✅ Constructor and Destructor
- ✅ isEmpty()
- ✅ display()
- ✅ insert() - handles both position 0 and position > 0
- ✅ remove() - handles both position 0 and position > 0
- ✅ search()
- ✅ operator=()

---

## 🐛 Common Mistakes to Avoid

### Mistake 1: Wrong link update order in insert()
❌ Wrong:
```cpp
node[current].next = newIndex;          // Breaks link to rest!
node[newIndex].next = node[current].next;  // Too late!
```
✅ Correct:
```cpp
node[newIndex].next = node[current].next;  // Save rest first!
node[current].next = newIndex;             // Then update
```

### Mistake 2: Not deallocating removed nodes
❌ Wrong:
```cpp
first = node[first].next;  // Just moves pointer - leaks node!
```
✅ Correct:
```cpp
temp = first;
first = node[first].next;
deallocate(temp);  // Return to pool!
```

### Mistake 3: Shallow copy in operator=
❌ Wrong:
```cpp
this->first = other.first;  // Shares nodes!
```
✅ Correct:
```cpp
// Allocate NEW nodes and copy data
```

### Mistake 4: Not checking allocate() result
❌ Wrong:
```cpp
int newIndex = allocate();
node[newIndex].data = value;  // Crashes if allocate() returned -1!
```
✅ Correct:
```cpp
int newIndex = allocate();
if (newIndex == NULL_VALUE) {
    return false;  // Handle error
}
node[newIndex].data = value;
```

---

## When You're Done

1. Make sure your file compiles without errors
2. Run the test program and verify it works
3. Share `arrayBasedList.h` with Person 3
4. **Important:** Person 3 needs your file before they can complete the project!

---

## Questions to Check Your Understanding

Before submitting, make sure you can answer:
1. Why must we update links in a specific order during insert? (Answer: To not lose references to the rest of the list)
2. What's the difference between `first = node[first].next` and proper node removal? (Answer: Proper removal also calls deallocate())
3. Why can't we just copy `first` in operator=? (Answer: Would create shallow copy sharing nodes)

---


