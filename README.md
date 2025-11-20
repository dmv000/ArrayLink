# ArrayLink

A C++ implementation of a linked list using array-based memory management instead of traditional pointers.

## What's This About?

Instead of using `new` and `delete` for each node, this project uses a fixed-size memory pool. Think of it like pre-allocating a parking lot of 50 spots instead of creating parking spaces on-demand.

## Project Structure

```
ArrayLib/
├── NodePool.h          # Memory pool that manages nodes
├── ArrayBasedList.h    # The actual list implementation
└── Tester.cpp          # Interactive testing program
```

## How to Use

**Compile:**
```bash
g++ ArrayLib/Tester.cpp -o tester
```

**Run:**
```bash
./tester
```

The tester gives you an interactive menu to insert, delete, search, and test the list.

## Key Features

- **Fixed Memory Pool**: All nodes come from a pre-allocated array
- **Array Indices Instead of Pointers**: Links use integer indices rather than memory addresses
- **Standard List Operations**: Insert, delete, search, sort, clear
- **1-Based Indexing**: Positions start at 1 (like normal human counting)

## Why Array-Based?

- No memory fragmentation
- Predictable memory usage
- Faster allocation/deallocation
- Good for embedded systems or real-time applications

---

Built for Data Structures - Fall 2026
