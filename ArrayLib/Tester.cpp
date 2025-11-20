/*---------------------------------------------------------------------
  Tester Program for ArrayBasedList with NodePool
  
  Tests the ArrayBasedList ADT with NodePool memory manager

  Features:
    - Basic operations (insert, delete, search, display, clear)
    - List state checking if (isEmpty, isFull)
    - Stress testing the list to its limits

  Uses 1-based indexing for positions
---------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <limits>
using namespace std;

#include "../Header Files/NodePool.h"
#include "../Header Files/ArrayBasedList.h"


const int POOL_SIZE = 50;
typedef ArrayBasedList<int, POOL_SIZE> IntList;

// Menu function prototypes
void showMainMenu();
void basicOperations(IntList& list);
void runStressTest(IntList& list);

// Basic operation functions
void insertValue(IntList& list);
void deleteValue(IntList& list);
void searchValue(IntList& list);
void showListContents(const IntList& list);

// Utility functions
void clearInputBuffer();
int getValidInteger(const string& prompt);

/*---------------------------------------------------------------------
  Main Function
---------------------------------------------------------------------*/
int main() {
    IntList myList;
    int mainChoice;
    
    cout << "\n-----------------------------------------\n";
    cout << "  ARRAY-BASED LIST TESTING SUITE\n";
    cout << "  1-based indexing | Pool Size: " << POOL_SIZE << "\n";
    cout << "-----------------------------------------\n";

    do {
        showMainMenu();
        mainChoice = getValidInteger("Select Operation: ");
        
        switch (mainChoice) {
            case 1:
                basicOperations(myList);
                break;
            case 2:
                runStressTest(myList);
                break;
            case 3:
                cout << "\nExiting the list tester program. Goodbye!\n";
                break;
            default:
                cout << "\nInvalid selection. Please choose 1-3.\n";
        }
    } while (mainChoice != 3);

    return 0;
}

/*---------------------------------------------------------------------
  Display Main Menu
---------------------------------------------------------------------*/
void showMainMenu() {
    cout << "\n-----------------------------------------\n";
    cout << "        MAIN MENU\n";
    cout << "-----------------------------------------\n";
    cout << "  1. Basic Operations\n";
    cout << "  2. Run Stress Test\n";
    cout << "  3. Exit Program\n";
    cout << "-----------------------------------------\n";
}

/*---------------------------------------------------------------------
  Basic Operations Submenu
---------------------------------------------------------------------*/
void basicOperations(IntList& list) {
    int choice;
    
    do {
        cout << "\n--- BASIC OPERATIONS ---\n";
        cout << "  1. Insert value at position\n";
        cout << "  2. Delete value at position\n";
        cout << "  3. Search for a value\n";
        cout << "  4. Display list\n";
        cout << "  5. Clear entire list\n";
        cout << "  6. Check if full\n";
        cout << "  7. Check if empty\n";
        cout << "  0. Return to main menu\n";
        
        choice = getValidInteger("Enter choice: ");
        
        switch (choice) {
            case 1: insertValue(list); break;
            case 2: deleteValue(list); break;
            case 3: searchValue(list); break;
            case 4: showListContents(list); break;
            case 5: 
                list.clear(); 
                cout << "List has been cleared.\n";
                break;
            case 6:
                cout << (list.isFull() ? "List is FULL\n" : "List is NOT full\n");
                break;
            case 7:
                cout << (list.isEmpty() ? "List is EMPTY\n" : "List is NOT empty\n");
                break;
            case 0: break;
            default: cout << "Invalid option.\n";
        }
    } while (choice != 0);
}

/*---------------------------------------------------------------------
  Insert Operation
---------------------------------------------------------------------*/
void insertValue(IntList& list) {
    if (list.isFull()) {
        cout << "Cannot insert - list is full!\n";
        return;
    }
    
    int value = getValidInteger("Enter value to insert: ");
    int position = getValidInteger("Enter position (1-" + 
                                   to_string(list.getSize() + 1) + "): ");
    
    int sizeBefore = list.getSize();
    list.insertAtPos(value, position);
    
    if (list.getSize() > sizeBefore) {
        cout << "Successfully inserted " << value << " at position " << position << "\n";
        showListContents(list);
    } else {
        cout << "Insert failed - invalid position or list full\n";
    }
}

/*---------------------------------------------------------------------
  Delete Operation
---------------------------------------------------------------------*/
void deleteValue(IntList& list) {
    if (list.isEmpty()) {
        cout << "Cannot delete - list is empty!\n";
        return;
    }
    
    int position = getValidInteger("Enter position to delete (1-" + 
                                   to_string(list.getSize()) + "): ");
    
    int sizeBefore = list.getSize();
    list.deleteAtPos(position);
    
    if (list.getSize() < sizeBefore) {
        cout << "Successfully deleted element at position " << position << "\n";
        showListContents(list);
    } else {
        cout << "Delete failed - invalid position\n";
    }
}

/*---------------------------------------------------------------------
  Search Operation
---------------------------------------------------------------------*/
void searchValue(IntList& list) {
    int value = getValidInteger("Enter value to search for: ");
    int position = list.search(value);
    
    if (position != -1) {
        cout << "Found value " << value << " at position " << position << "\n";
    } else {
        cout << "Value " << value << " not found in list\n";
    }
}

/*---------------------------------------------------------------------
  Display List Contents
---------------------------------------------------------------------*/
void showListContents(const IntList& list) {
    cout << "\nList Contents: ";
    if (list.isEmpty()) {
        cout << "(empty)\n";
    } else {
        list.display();
    }
}

/*---------------------------------------------------------------------
  Stress Test
---------------------------------------------------------------------*/
void runStressTest(IntList& list) {
    cout << "\n-----------------------------------------\n";
    cout << "            STRESS TEST\n";
    cout << "  This will test edge cases and boundary conditions\n";
    cout << "-----------------------------------------\n\n";
    
    // Fill to its max capacity
    cout << "Testing: Filling list to capacity\n";
    list.clear();
    for (int i = 0; i < POOL_SIZE; i++) {
        list.insertAtPos(i + 1, list.getSize() + 1);
    }
    cout << "List size: " << list.getSize() << " (should be " << POOL_SIZE << ")\n";
    
    // Try inserting when full
    cout << "\nTesting: Insert when full\n";
    int sizeBefore = list.getSize();
    list.insertAtPos(999, 1);
    cout << (list.getSize() == sizeBefore ? "Insert rejected\n" : "Insert accepted\n");
    
    // Delete all elements from thi list
    cout << "\nTesting: Deleting all elements\n";
    while (!list.isEmpty()) {
        list.deleteAtPos(1);
    }
    cout << "List size: " << list.getSize() << " (should be 0)\n";
    
    // Try deleting from empty list
    cout << "\nTesting: Delete from empty list\n";
    sizeBefore = list.getSize();
    list.deleteAtPos(1);
    cout << (list.getSize() == sizeBefore ? "Delete ignored\n" : "Size changed\n");
    
    // Boundary position insertion testing
    cout << "\nTesting: Boundary position insertions\n";
    list.insertAtPos(10, 1);  // Insert at beginning
    list.insertAtPos(20, 2);  // Insert at end
    list.insertAtPos(15, 2);  // Insert in middle
    cout << "List after boundary inserts: ";
    list.display();
    
    // Search in empty vs populated list
    cout << "\nTesting: Search operations\n";
    int pos = list.search(15);
    cout << "Search for 15: " << (pos != -1 ? "Found at position " + to_string(pos) : "Not found") << "\n";
    pos = list.search(999);
    cout << "Search for 999: " << (pos == -1 ? "Not found" : "Found at position " + to_string(pos)) << "\n";
    
    cout << "\n-----------------------------------------\n";
    cout << "       STRESS TEST COMPLETED\n";
    cout << "-----------------------------------------\n";
}

/*---------------------------------------------------------------------
  Get Valid Integer
---------------------------------------------------------------------*/
int getValidInteger(const string& prompt) {
    int value;
    cout << prompt;
    
    while (!(cin >> value)) {
        clearInputBuffer();
        cout << "Invalid input. Please enter an integer.\n";
        cout << prompt;
    }
    
    clearInputBuffer();
    return value;
}


  //this function Clear Input Buffer

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

