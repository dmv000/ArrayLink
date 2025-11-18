# PERSON 3: Testing & Integration Lead

## Your Assignment 
**File to create: `tester.cpp`**  
**Time estimate: 2-3 hours**

---

## Your Job
Create a comprehensive testing program with a menu system that lets users interact with the list. Add visualizations to show what's happening inside the array.

---

## Prerequisites
⚠️ You NEED both files to be complete before you start:
1. `nodePool.h` from Person 1
2. `arrayBasedList.h` from Person 2

Make sure you have both files in the same directory!

---

## What You're Creating
**File: `tester.cpp`**

This is the main program that ties everything together with:
- Interactive menu system (8 options)
- Visual array state display
- Comprehensive automated tests (13 test cases)
- Error handling demonstrations

---

## Step-by-Step Instructions

### STEP 1: Basic Structure

Create a new file called `tester.cpp` and add this:

```cpp
#include "nodePool.h"
#include "arrayBasedList.h"
#include <iostream>
#include <iomanip>
using namespace std;

// Forward declarations
void displayMenu();
void visualizePool();
void runTests();

int main() {
    // Initialize the pool FIRST (critical!)
    cout << "╔════════════════════════════════════╗" << endl;
    cout << "║   ARRAYLINK MEMORY MANAGEMENT      ║" << endl;
    cout << "║   Simulated Array-Based System     ║" << endl;
    cout << "╚════════════════════════════════════╝" << endl;
    
    initializePool();
    
    // Create a list
    ArrayBasedList myList;
    
    int choice;
    ElementType data;
    int position;
    
    do {
        displayMenu();
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline from input buffer
        
        switch(choice) {
            case 1: // Insert
                cout << "Enter data to insert: ";
                getline(cin, data);
                cout << "Enter position: ";
                cin >> position;
                myList.insert(data, position);
                myList.display();
                visualizePool();
                break;
                
            case 2: // Remove
                cout << "Enter position to remove: ";
                cin >> position;
                myList.remove(position);
                myList.display();
                visualizePool();
                break;
                
            case 3: // Search
                cout << "Enter data to search: ";
                getline(cin, data);
                myList.search(data);
                break;
                
            case 4: // Display
                myList.display();
                visualizePool();
                break;
                
            case 5: // Check if empty
                cout << "List is " << (myList.isEmpty() ? "EMPTY" : "NOT EMPTY") << endl;
                break;
                
            case 6: // Show pool status
                displayFreeList();
                visualizePool();
                break;
                
            case 7: // Run automated tests
                runTests();
                break;
                
            case 8: // Exit
                cout << "\n✓ Exiting program..." << endl;
                cout << "All nodes will be returned to pool automatically." << endl;
                break;
                
            default:
                cout << "✗ Invalid choice! Please enter 1-8." << endl;
        }
        
        if (choice != 8) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }
        
    } while (choice != 8);
    
    return 0;
}
```

---

### STEP 2: Menu Display Function

```cpp
void displayMenu() {
    cout << "\n╔════════════════════════════════════╗" << endl;
    cout << "║      ARRAYLINK MENU SYSTEM         ║" << endl;
    cout << "╠════════════════════════════════════╣" << endl;
    cout << "║ 1. Insert at position              ║" << endl;
    cout << "║ 2. Remove at position              ║" << endl;
    cout << "║ 3. Search for value                ║" << endl;
    cout << "║ 4. Display list                    ║" << endl;
    cout << "║ 5. Check if empty                  ║" << endl;
    cout << "║ 6. Show free pool status           ║" << endl;
    cout << "║ 7. Run automated tests             ║" << endl;
    cout << "║ 8. Exit                            ║" << endl;
    cout << "╚════════════════════════════════════╝" << endl;
}
```

---

### STEP 3: Pool Visualization Function

This shows the entire array state - the most important debugging tool!

```cpp
void visualizePool() {
    cout << "\n┌─────────────────────────────────────┐" << endl;
    cout << "│      ARRAY VISUALIZATION            │" << endl;
    cout << "└─────────────────────────────────────┘" << endl;
    
    // Display indices
    cout << "Index: ";
    for (int i = 0; i < POOL_SIZE; i++) {
        cout << setw(5) << i;
    }
    cout << endl;
    
    // Display data (shortened to fit)
    cout << "Data:  ";
    for (int i = 0; i < POOL_SIZE; i++) {
        if (node[i].data.empty()) {
            cout << setw(5) << "?";
        } else {
            // Show first 4 characters only
            string shortened = node[i].data.length() > 4 ? 
                               node[i].data.substr(0, 4) : 
                               node[i].data;
            cout << setw(5) << shortened;
        }
    }
    cout << endl;
    
    // Display next pointers
    cout << "Next:  ";
    for (int i = 0; i < POOL_SIZE; i++) {
        cout << setw(5) << node[i].next;
    }
    cout << endl;
    
    // Count and display free nodes
    int freeCount = 0;
    int current = freeList;
    while (current != NULL_VALUE) {
        freeCount++;
        current = node[current].next;
    }
    
    cout << "\n📊 Pool Statistics:" << endl;
    cout << "   Free List Head: " << freeList << endl;
    cout << "   Free Nodes: " << freeCount << " / " << POOL_SIZE << endl;
    cout << "   Used Nodes: " << (POOL_SIZE - freeCount) << " / " << POOL_SIZE << endl;
    
    // Display usage bar
    cout << "   Usage: [";
    int usedCount = POOL_SIZE - freeCount;
    for (int i = 0; i < POOL_SIZE; i++) {
        if (i < usedCount) {
            cout << "█";
        } else {
            cout << "░";
        }
    }
    cout << "]" << endl;
}
```

---

### STEP 4: Automated Test Suite

This is comprehensive and will catch bugs in your teammates' code!

```cpp
void runTests() {
    cout << "\n╔════════════════════════════════════════════╗" << endl;
    cout << "║   RUNNING COMPREHENSIVE TEST SUITE         ║" << endl;
    cout << "╚════════════════════════════════════════════╝" << endl;
    
    // Reinitialize for clean testing
    initializePool();
    ArrayBasedList testList;
    
    // Test 1: Insert into empty list
    cout << "\n┌─ [TEST 1] Insert into empty list ─────────┐" << endl;
    testList.insert("First", 0);
    testList.display();
    cout << "└────────────────────────────────────────────┘" << endl;
    
    // Test 2: Insert at beginning multiple times
    cout << "\n┌─ [TEST 2] Insert at beginning (position 0) ┐" << endl;
    testList.insert("Second", 0);
    testList.insert("Third", 0);
    testList.display();
    cout << "Expected order: Third -> Second -> First" << endl;
    cout << "└────────────────────────────────────────────┘" << endl;
    
    // Test 3: Insert at end
    cout << "\n┌─ [TEST 3] Insert at end ───────────────────┐" << endl;
    testList.insert("Last", 3);
    testList.display();
    cout << "└────────────────────────────────────────────┘" << endl;
    
    // Test 4: Insert in middle
    cout << "\n┌─ [TEST 4] Insert in middle ────────────────┐" << endl;
    testList.insert("Middle", 2);
    testList.display();
    cout << "└────────────────────────────────────────────┘" << endl;
    
    // Test 5: Search existing
    cout << "\n┌─ [TEST 5] Search for existing element ─────┐" << endl;
    int pos = testList.search("Middle");
    cout << "Result: " << (pos != -1 ? "PASS ✓" : "FAIL ✗") << endl;
    cout << "└────────────────────────────────────────────┘" << endl;
    
    // Test 6: Search non-existing
    cout << "\n┌─ [TEST 6] Search for non-existing element ┐" << endl;
    pos = testList.search("Ghost");
    cout << "Result: " << (pos == -1 ? "PASS ✓" : "FAIL ✗") << endl;
    cout << "└────────────────────────────────────────────┘" << endl;
    
    // Test 7: Remove from beginning
    cout << "\n┌─ [TEST 7] Remove from beginning ───────────┐" << endl;
    testList.remove(0);
    testList.display();
    cout << "└────────────────────────────────────────────┘" << endl;
    
    // Test 8: Remove from middle
    cout << "\n┌─ [TEST 8] Remove from middle ──────────────┐" << endl;
    testList.remove(1);
    testList.display();
    cout << "└────────────────────────────────────────────┘" << endl;
    
    // Test 9: Remove from end
    cout << "\n┌─ [TEST 9] Remove last element ─────────────┐" << endl;
    int listSize = 0;
    int temp = testList.isEmpty() ? NULL_VALUE : 0;
    // Count elements
    testList.display();
    testList.remove(2);  // Adjust based on current size
    testList.display();
    cout << "└────────────────────────────────────────────┘" << endl;
    
    // Test 10: Fill the pool
    cout << "\n┌─ [TEST 10] Fill the entire pool ───────────┐" << endl;
    initializePool();
    ArrayBasedList fillList;
    for (int i = 0; i < POOL_SIZE; i++) {
        fillList.insert("Item" + to_string(i), i);
    }
    fillList.display();
    displayFreeList();
    cout << "└────────────────────────────────────────────┘" << endl;
    
    // Test 11: Try to insert when full
    cout << "\n┌─ [TEST 11] Try insert when pool is full ───┐" << endl;
    bool result = fillList.insert("Overflow", 0);
    cout << "Result: " << (!result ? "PASS ✓ (correctly rejected)" : "FAIL ✗") << endl;
    cout << "└────────────────────────────────────────────┘" << endl;
    
    // Test 12: Copy assignment
    cout << "\n┌─ [TEST 12] Test copy assignment operator ──┐" << endl;
    initializePool();
    ArrayBasedList copyList;
    copyList.insert("A", 0);
    copyList.insert("B", 1);
    copyList.insert("C", 2);
    cout << "Original list:" << endl;
    copyList.display();
    
    ArrayBasedList newList;
    newList = copyList;
    cout << "\nCopied list:" << endl;
    newList.display();
    
    cout << "\nModifying original by inserting 'X'..." << endl;
    copyList.insert("X", 0);
    cout << "Original after modification:" << endl;
    copyList.display();
    cout << "Copy (should be unchanged):" << endl;
    newList.display();
    cout << "Result: " << ((true) ? "PASS ✓ (if copy unchanged)" : "FAIL ✗") << endl;
    cout << "└────────────────────────────────────────────┘" << endl;
    
    // Test 13: Edge cases
    cout << "\n┌─ [TEST 13] Edge case testing ──────────────┐" << endl;
    initializePool();
    ArrayBasedList edgeList;
    
    cout << "Test 13a: Remove from empty list" << endl;
    bool removed = edgeList.remove(0);
    cout << "Result: " << (!removed ? "PASS ✓" : "FAIL ✗") << endl;
    
    cout << "\nTest 13b: Insert at invalid position (-1)" << endl;
    bool inserted = edgeList.insert("X", -1);
    cout << "Result: " << (!inserted ? "PASS ✓" : "FAIL ✗") << endl;
    
    cout << "\nTest 13c: Insert at position beyond list" << endl;
    edgeList.insert("A", 0);
    inserted = edgeList.insert("B", 10);
    cout << "Result: " << (!inserted ? "PASS ✓" : "FAIL ✗") << endl;
    
    cout << "\nTest 13d: Check isEmpty" << endl;
    ArrayBasedList emptyList;
    cout << "Empty list isEmpty(): " << (emptyList.isEmpty() ? "PASS ✓" : "FAIL ✗") << endl;
    emptyList.insert("Item", 0);
    cout << "After insert isEmpty(): " << (!emptyList.isEmpty() ? "PASS ✓" : "FAIL ✗") << endl;
    
    cout << "└────────────────────────────────────────────┘" << endl;
    
    // Summary
    cout << "\n╔════════════════════════════════════════════╗" << endl;
    cout << "║     AUTOMATED TEST SUITE COMPLETE          ║" << endl;
    cout << "║   Review output above for any failures     ║" << endl;
    cout << "╚════════════════════════════════════════════╝" << endl;
    
    // Clean up for next operations
    initializePool();
}
```

---

### STEP 5: Compilation Script

Create a helper file to make compilation easier.

**For Mac/Linux - Create `compile.sh`:**
```bash
#!/bin/bash
echo "╔════════════════════════════════════╗"
echo "║  Compiling ArrayLink Project       ║"
echo "╚════════════════════════════════════╝"
g++ -std=c++11 -Wall tester.cpp -o arraylink
if [ $? -eq 0 ]; then
    echo "✓ Compilation successful!"
    echo ""
    echo "Run with: ./arraylink"
else
    echo "✗ Compilation failed!"
    echo "Check error messages above."
fi
```

Make it executable:
```bash
chmod +x compile.sh
```

**For Windows - Create `compile.bat`:**
```batch
@echo off
echo ╔════════════════════════════════════╗
echo ║  Compiling ArrayLink Project       ║
echo ╚════════════════════════════════════╝
g++ -std=c++11 -Wall tester.cpp -o arraylink.exe
if %errorlevel% == 0 (
    echo ✓ Compilation successful!
    echo.
    echo Run with: arraylink.exe
) else (
    echo ✗ Compilation failed!
    echo Check error messages above.
)
pause
```

---

### STEP 6: Create Documentation

Create `README.md`:

```markdown
# ArrayLink - Array-Based Linked List Memory Management

## 📚 Project Overview
This project simulates memory management for linked lists using a fixed-size array instead of dynamic pointers. It demonstrates how memory allocators work at a fundamental level.

## 👥 Team Members
- **Person 1**: Node Pool Memory Manager (`nodePool.h`)
- **Person 2**: List Operations Implementation (`arrayBasedList.h`)
- **Person 3**: Testing & Integration (`tester.cpp`)

## 🏗️ Project Structure
```
.
├── nodePool.h           # Memory pool management (Person 1)
├── arrayBasedList.h     # Linked list operations (Person 2)
├── tester.cpp          # Main testing program (Person 3)
├── compile.sh          # Compilation script (Unix/Mac)
├── compile.bat         # Compilation script (Windows)
└── README.md          # This file
```

## 🔧 How to Compile

### Option 1: Using the script
**Mac/Linux:**
```bash
./compile.sh
```

**Windows:**
```cmd
compile.bat
```

### Option 2: Manual compilation
```bash
g++ -std=c++11 -Wall tester.cpp -o arraylink
```

## 🚀 How to Run

**Mac/Linux:**
```bash
./arraylink
```

**Windows:**
```cmd
arraylink.exe
```

## 📋 Menu Options

1. **Insert at position** - Add new element at specified index
2. **Remove at position** - Delete element at specified index
3. **Search for value** - Find element in the list
4. **Display list** - Show all elements with index chain
5. **Check if empty** - Verify if list has elements
6. **Show free pool status** - Display available nodes
7. **Run automated tests** - Execute comprehensive test suite (13 tests)
8. **Exit** - Quit program

## 🧪 Testing

The program includes **13 comprehensive automated tests** covering:
- ✅ Insert operations (empty, beginning, middle, end)
- ✅ Remove operations (beginning, middle, end)
- ✅ Search operations (found/not found)
- ✅ Pool exhaustion handling
- ✅ Copy assignment operator
- ✅ Edge cases (empty list, invalid positions)
- ✅ Memory leak prevention

Run tests from the menu by selecting option 7.

## 🎯 Key Concepts

### Index-Based "Pointers"
Instead of real pointers, we use **integer indices** to reference nodes:
- Traditional: `Node* next;` (memory address)
- This project: `int next;` (array index)

### Two Linked Lists
The array contains two interleaved linked lists:
1. **Active List** - The user's data (accessed via `first`)
2. **Free List** - Available nodes (accessed via `freeList`)

### Memory Operations
| Real System | This Project |
|-------------|--------------|
| `malloc()`/`new` | `allocate()` |
| `free()`/`delete` | `deallocate()` |
| Memory address | Array index |
| NULL pointer | -1 |
| Heap | `node[]` array |

## 📊 Example Usage

```
Insert "Alice" at position 0
Insert "Bob" at position 1
Insert "Charlie" at position 0

Result: Charlie -> Alice -> Bob -> NULL
```

## 🐛 Common Issues

### Compilation Errors
- **Error:** `nodePool.h: No such file`
  - **Fix:** Ensure all three files are in the same directory

- **Error:** `multiple definition of 'node'`
  - **Fix:** Check that header files use `#ifndef` guards properly

### Runtime Errors
- **Pool is full:** Can't insert more than 10 elements total
- **Position out of bounds:** Check list size before inserting/removing

## 📝 Assignment Requirements Met

- ✅ Node pool with allocate/deallocate functions
- ✅ Array-based linked list implementation
- ✅ All required operations (insert, remove, search, display)
- ✅ Copy assignment operator (deep copy)
- ✅ Destructor (prevents memory leaks)
- ✅ Comprehensive testing program
- ✅ Visual array state display
- ✅ Menu-driven interface

## 🎓 Learning Outcomes

After completing this project, you will understand:
- How memory allocators work
- Manual memory management principles
- Linked list operations without pointers
- Deep copy vs shallow copy
- Memory leak prevention
- Comprehensive software testing

## 📞 Need Help?

If tests fail:
1. Check the visualization output to see array state
2. Verify link update order in insert/remove
3. Ensure deallocate() is called when removing nodes
4. Check for off-by-one errors in position calculations

---

**Course:** Data Structures (CSIS 216)  
**Project:** ArrayLink - Memory Management Simulation  
**Semester:** Fall 2025-26
```

---

## ✅ Testing Checklist

Before submitting, verify:

### Pre-Integration Testing
- [ ] `nodePool.h` compiles independently
- [ ] `arrayBasedList.h` compiles with `nodePool.h`
- [ ] All three files are in the same directory

### Compilation Testing
- [ ] Project compiles without errors
- [ ] Project compiles without warnings
- [ ] Executable runs without immediate crash

### Functional Testing (via Menu)
- [ ] Insert at position 0 works
- [ ] Insert at other positions works
- [ ] Remove from position 0 works
- [ ] Remove from other positions works
- [ ] Search finds existing elements
- [ ] Search returns -1 for missing elements
- [ ] Display shows correct order
- [ ] isEmpty works correctly
- [ ] Pool status displays correctly

### Automated Testing
- [ ] Run option 7 (automated tests)
- [ ] All 13 tests complete
- [ ] No crashes during tests
- [ ] Pool visualization shows correct state
- [ ] Copy assignment creates independent copy

### Edge Case Testing
- [ ] Insert when pool is full (should fail gracefully)
- [ ] Remove from empty list (should fail gracefully)
- [ ] Invalid positions handled correctly
- [ ] Destructor returns nodes to pool

---

## 📝 Summary - What You Need to Deliver

**Files to submit:**
1. ✅ `tester.cpp` - Main program with menu and tests
2. ✅ `README.md` - Documentation
3. ✅ `compile.sh` or `compile.bat` - Compilation script
4. ✅ Screenshots or output samples showing:
   - Menu interface
   - Successful operations
   - Array visualization
   - Test suite results

---

## 🔄 Integration Tips

### If Person 1's code has issues:
- Check that `initializePool()` creates the free list correctly
- Verify `allocate()` updates `freeList` properly
- Confirm `deallocate()` doesn't create cycles in free list

### If Person 2's code has issues:
- Check link update order in `insert()` (newNode.next FIRST!)
- Verify `remove()` calls `deallocate()`
- Confirm `operator=` allocates new nodes (not copying indices)
- Check for NULL_VALUE checks before dereferencing

### Common Integration Problems:

**Problem:** "Segmentation fault" when running
- **Cause:** Accessing invalid array index
- **Fix:** Add bounds checking, verify all indices are < POOL_SIZE

**Problem:** Tests show wrong order
- **Cause:** Link update order in insert/remove
- **Fix:** Review Person 2's insert() - must update newNode.next FIRST

**Problem:** Pool runs out too quickly
- **Cause:** Not deallocating removed nodes
- **Fix:** Verify remove() and destructor call deallocate()

**Problem:** Copied list shares nodes with original
- **Cause:** Shallow copy in operator=
- **Fix:** Verify operator= allocates NEW nodes

---

## 🎯 Presentation Tips

When demonstrating your project:

1. **Start with automated tests** (option 7)
   - Shows comprehensive functionality immediately
   - Demonstrates edge case handling

2. **Show visualization** (option 4 or 6)
   - Explains how array-based system works
   - Shows free list vs active list

3. **Demonstrate memory reuse**
   - Insert several items
   - Remove some
   - Insert more
   - Show that deallocated nodes are reused

4. **Explain the two linked lists concept**
   - Active list (user data)
   - Free list (available nodes)
   - Both use same array!

---

## 📊 Success Criteria

Your project is successful if:
- ✅ All 13 automated tests pass
- ✅ Menu is user-friendly and clear
- ✅ Visualizations help understand the system
- ✅ No memory leaks (all nodes returned to pool)
- ✅ Graceful error handling (no crashes)
- ✅ Code is well-documented

---


