# PERSON 3: Testing & Integration Lead

## Your Assignment 
**File to create: `Tester.cpp`**  
**Time estimate: 2-3 hours**

---

## Your Job
Create a comprehensive testing program with a menu system that lets users interact with the list. Add visualizations to show what's happening inside the array.

----

## Prerequisites
⚠️ You NEED both files to be complete before you start:
1. `NodePool.h` from Person 1
2. `List.h` from Person 2

Make sure you have both files in the same directory!

---

## What You're Creating
**File: `Tester.cpp`**

This is the main program that ties everything together with:
- Interactive menu system (9 options)
- Comprehensive testing
- Error handling demonstrations

---

## Step-by-Step Instructions

### STEP 1: Basic Structure

Create a new file called `Tester.cpp` and add this:

```cpp
/*---------------------------------------------------------------------
  Tester Program for List with NodePool
  
  This program provides a simple interface to test operations on a List
  implemented using a NodePool. Users can insert, delete, sort, search,
  and display list elements.

  Input:  User choices and inputs for list operations (values and positions).
  Output: Displays the list content, operation results, and success/error messages.

  Methods:
    - insertValue: Insert a value at a specific position
    - deleteValue: Delete a value from a specific position
    - displayList: Display all elements in the list
    - sortList: Sort elements in ascending order
    - getSize: Display current list size
    - checkEmpty: Check if list is empty
    - checkFull: Check if list is full
    - clearList: Remove all elements from the list
    - searchValue: Search for an element in the list
---------------------------------------------------------------------*/

// Include necessary headers
#include <iostream>
#include <limits>
using namespace std;
#include "NodePool.h"
#include "List.h"

// Function declarations
void insertValue(List<string, 100> &);
void deleteValue(List<string, 100> &);
void displayList(const List<string, 100> &);
void sortList(List<string, 100> &);
void getSize(const List<string, 100> &);
void checkEmpty(const List<string, 100> &);
void checkFull(const List<string, 100> &);
void clearList(List<string, 100> &);
void searchValue(const List<string, 100> &);

int main() {
    // Constant for number of nodes
    const int NUM_NODES = 100;
    List<string, NUM_NODES> myList;
    int choice;

    do {
        cout << "\n===== List Operations =====\n";
        cout << "1. Insert at position\n";
        cout << "2. Delete at position\n";
        cout << "3. Display list\n";
        cout << "4. Sort list\n";
        cout << "5. Get size\n";
        cout << "6. Check if list is empty\n";
        cout << "7. Check if list is full\n";
        cout << "8. Clear list\n";
        cout << "9. Search for an element\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear(); // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore bad input
            cout << "Invalid input. Please enter a number between 1 and 10.\n";
            continue; // Go back to the beginning of the loop
        }
        
        switch (choice) {
            case 1: insertValue(myList); break;
            case 2: deleteValue(myList); break;
            case 3: displayList(myList); break;
            case 4: sortList(myList); break;
            case 5: getSize(myList); break;
            case 6: checkEmpty(myList); break;
            case 7: checkFull(myList); break;
            case 8: clearList(myList); break;
            case 9: searchValue(myList); break;
            case 10:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice (Should be an integer between 1 and 10 inclusive)\n";
                break;
        }
    } while (choice != 10);

    return 0;
}
```

---

### STEP 2: Function Implementations

Now add all the function definitions after main():

```cpp
// Definition of insertValue function
// Purpose: Insert a user-provided value at a specified position
// Input: Value (string), Position (int, 1-based)
// Output: Updates the list with the new value
void insertValue(List<string, 100> &myList) {
    string value;
    int position;
    cout << "Enter value to insert: ";
    cin >> value;
    cout << "Enter position to insert at (1-based): ";
    cin >> position;
    myList.insertAtPos(value, position);
}

// Definition of deleteValue function
// Purpose: Delete a node from a specified position
// Input: Position (int, 1-based)
// Output: Updates the list by removing the node
void deleteValue(List<string, 100> &myList) {
    int position;
    cout << "Enter position to delete from (1-based): ";
    cin >> position;
    myList.deleteAtPos(position);
    cout << "Node deleted at position " << position << endl;
}

// Definition of displayList function
// Purpose: Display all elements currently in the list
// Input: None
// Output: Prints list elements to console
void displayList(const List<string, 100> &myList) {
    cout << "List elements: ";
    myList.display();
}

// Definition of sortList function
// Purpose: Sort all list elements in ascending order
// Input: None
// Output: Sorted list displayed
void sortList(List<string, 100> &myList) {
    myList.sort();
    cout << "List sorted.\n";
}

// Definition of getSize function
// Purpose: Display the current size of the list
// Input: None
// Output: Number of elements printed
void getSize(const List<string, 100> &myList) {
    cout << "List size: " << myList.getSize() << endl;
}

// Definition of checkEmpty function
// Purpose: Check if the list is currently empty
// Input: None
// Output: Displays whether the list is empty
void checkEmpty(const List<string, 100> &myList) {
    if (myList.isEmpty()) {
        cout << "List is empty.\n";
    } else {
        cout << "List is not empty.\n";
    }
}

// Definition of checkFull function
// Purpose: Check if the list is currently full
// Input: None
// Output: Displays whether the list is full
void checkFull(const List<string, 100> &myList) {
    if (myList.isFull()) {
        cout << "List is full.\n";
    } else {
        cout << "List is not full.\n";
    }
}

// Definition of clearList function
// Purpose: Clear all elements from the list
// Input: None
// Output: Empties the list
void clearList(List<string, 100> &myList) {
    myList.clear();
    cout << "List cleared.\n";
}

// Definition of searchValue function
// Purpose: Search for a specific value in the list
// Input: Value (string)
// Output: Displays the position if found, otherwise not found message
void searchValue(const List<string, 100> &myList) {
    string value;
    cout << "Enter value to search: ";
    cin >> value;
    int position = myList.search(value);
    if (position != -1)
        cout << "Element found at position: " << position << endl;
    else
        cout << "Element not found in the list.\n";
}
```

---

## ✅ Testing Checklist

Before submitting, verify:

### Pre-Integration Testing
- [ ] `NodePool.h` compiles independently
- [ ] `List.h` compiles with `NodePool.h`
- [ ] All three files are in the same directory

### Compilation Testing
- [ ] Project compiles without errors: `g++ -std=c++11 Tester.cpp -o tester`
- [ ] Project compiles without warnings
- [ ] Executable runs without immediate crash

### Functional Testing (via Menu)
- [ ] Insert at position 1 works
- [ ] Insert at other positions works
- [ ] Delete from position 1 works
- [ ] Delete from other positions works
- [ ] Search finds existing elements
- [ ] Search returns -1 for missing elements
- [ ] Display shows correct order
- [ ] isEmpty works correctly
- [ ] isFull works correctly (test with small pool size)
- [ ] Sort works correctly

### Edge Case Testing
- [ ] Insert when list is full (should fail gracefully)
- [ ] Delete from empty list (should fail gracefully)
- [ ] Invalid positions handled correctly
- [ ] Destructor returns nodes to pool

---

## 📝 Summary - What You Need to Deliver

**Files to submit:**
1. ✅ `Tester.cpp` - Main program with menu
2. ✅ Screenshots or output samples showing:
   - Menu interface
   - Successful operations
   - Test results

---

## 🔄 Integration Tips

### If Person 1's code has issues:
- Check that NodePool constructor creates the free list correctly
- Verify `allocate()` updates `ffn` properly
- Confirm `deallocate()` doesn't create cycles in free list
- Make sure `getNode()` and `getNodeConst()` return correct references

### If Person 2's code has issues:
- Check link update order in `insertAtPos()` (newNode.next FIRST!)
- Verify `deleteAtPos()` calls `deallocate()`
- Confirm `operator=` allocates new nodes (not copying indices)
- Check for NULL_VALUE checks before dereferencing

### Common Integration Problems:

**Problem:** "No matching function for call to 'List<string, 100>::List()'"
- **Cause:** Template not properly defined
- **Fix:** Make sure all template implementations are in the header file

**Problem:** Tests show wrong order
- **Cause:** Link update order in insertAtPos/deleteAtPos
- **Fix:** Review Person 2's insertAtPos() - must update newNode.next FIRST

**Problem:** "Cannot access private member nodepool"
- **Cause:** Trying to access NodePool's private members directly
- **Fix:** Use `getNode()` and `getNodeConst()` accessor methods

---

## 🎯 Presentation Tips

When demonstrating your project:

1. **Start with basic operations**
   - Show insert, delete, display
   - Demonstrates core functionality

2. **Show the template flexibility**
   - Can create `List<int, 50>` or `List<string, 100>`
   - Same code works for different types

3. **Demonstrate memory management**
   - Insert several items
   - Delete some
   - Insert more
   - Show that deallocated nodes are reused (via getFFN())

4. **Explain the encapsulation**
   - No global variables
   - Everything is class-based
   - Type-safe with templates

---

## 📊 Success Criteria

Your project is successful if:
- ✅ All menu options work correctly
- ✅ Menu is user-friendly and clear
- ✅ No memory leaks (all nodes returned to pool)
- ✅ Graceful error handling (no crashes)
- ✅ Code is well-documented
- ✅ Template-based design allows flexibility

---

## 🎓 Key Concepts to Understand

### Template Instantiation
```cpp
// Different lists with different types and sizes
List<string, 100> stringList;   // 100 string nodes
List<int, 50> intList;           // 50 int nodes  
List<double, 200> doubleList;    // 200 double nodes
```

### Encapsulation Benefits
- No global variables to conflict with other code
- Each List has its own NodePool
- Type safety at compile time

### 1-Based vs 0-Based Indexing
- User interface uses 1-based positions (position 1 = first element)
- Internal array uses 0-based indexing
- Makes it more intuitive for users

---

## Compilation and Running

**Compile:**
```bash
g++ -std=c++11 -Wall Tester.cpp -o tester
```

**Run:**
```bash
./tester
```

**On Windows:**
```cmd
g++ -std=c++11 -Wall Tester.cpp -o tester.exe
tester.exe
```

---

## Sample Test Session

```
===== List Operations =====
1. Insert at position
Enter your choice: 1
Enter value to insert: Alice
Enter position to insert at (1-based): 1

===== List Operations =====
1. Insert at position
Enter your choice: 1
Enter value to insert: Bob
Enter position to insert at (1-based): 2

===== List Operations =====
3. Display list
Enter your choice: 3
List elements: [1]: Alice [2]: Bob

===== List Operations =====
9. Search for an element
Enter your choice: 9
Enter value to search: Alice
Element found at position: 1
```

---
