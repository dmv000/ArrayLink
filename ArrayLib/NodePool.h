/*-- NodePool.h -------------------------------------------------------------

This header file defines a template-based NodePool class used for managing
a fixed-size pool of linked-list nodes.

The NodePool replaces dynamic memory allocation (new/delete) by maintaining
a free-list of nodes that can be reused efficiently.

Basic operations:
    Constructor:     Initializes the pool and links all nodes into a free list.
    allocate:        Allocates a free node and returns its index.
    deallocate:      Returns a node to the free list.
    getNode:         Provides non-const access to a node.
    getNodeConst:    Provides const access to a node.
    getFFN:          Returns the index of the first free node.

Class Invariant:
    - pool[] is a fixed-size array of NUM_NODES linked together.
    - freeList points to the first available node.
    - A node is free if it is reachable through the freeList chain.

---------------------------------------------------------------------------*/

#ifndef NODEPOOL_H
#define NODEPOOL_H


/*==========================================================================*
 *                             Class Definition                             *
 *==========================================================================*/

template <typename ElementType, int NUM_NODES>
class NodePool {
public:
    static const int NULL_VALUE = -1;

    struct Node {
        ElementType data;   // Data stored in the node
        int next;           // Next node index (or next free node)
    };

    /***** Constructor *****/
    NodePool();
    /*----------------------------------------------------------------------
      Constructs the NodePool and initializes the free list.

      Precondition : None
      Postcondition: All nodes form a chain 0 → 1 → 2 → ... → -1.
                     freeList = 0.
    ----------------------------------------------------------------------*/

    /***** allocate *****/
    int allocate();
    /*----------------------------------------------------------------------
      Allocates (removes) a node from the free list.

      Precondition : freeList != NULL_VALUE (pool has free nodes)
      Postcondition: Returns index of allocated node.
                     freeList is updated to point to next free node.
                     Returns NULL_VALUE if pool is exhausted.
    ----------------------------------------------------------------------*/

    /***** deallocate *****/
    void deallocate(int index);
    /*----------------------------------------------------------------------
      Returns a node back to the free list.

      Precondition : 0 ≤ index < NUM_NODES
      Postcondition: Node at 'index' becomes new freeList head.
    ----------------------------------------------------------------------*/

    /***** getNode *****/
    Node& getNode(int index);
    /*----------------------------------------------------------------------
      Provides write access to a node.

      Precondition : 0 ≤ index < NUM_NODES
      Postcondition: Returns reference to the node at given index.
    ----------------------------------------------------------------------*/

    /***** getNodeConst *****/
    const Node& getNodeConst(int index) const;
    /*----------------------------------------------------------------------
      Provides read-only access to a node.

      Precondition : 0 ≤ index < NUM_NODES
      Postcondition: Returns const reference to node at given index.
    ----------------------------------------------------------------------*/

    /***** getFFN *****/
    int getFFN() const;
    /*----------------------------------------------------------------------
      Returns the index of the first free node.

      Precondition : None
      Postcondition: Returns freeList.
    ----------------------------------------------------------------------*/

private:
    Node pool[NUM_NODES];  // Fixed-size array of nodes
    int freeList;          // Head of the free node list

    void initializePool();
    /*----------------------------------------------------------------------
      Links all nodes into the initial free list.

      Precondition : None
      Postcondition: pool[i].next = i + 1 for all i
                     pool[NUM_NODES - 1].next = NULL_VALUE
                     freeList = 0
    ----------------------------------------------------------------------*/
};


/*==========================================================================*
 *                          Implementation Section                           *
 *==========================================================================*/

template <typename ElementType, int NUM_NODES>
NodePool<ElementType, NUM_NODES>::NodePool() {
    initializePool();
}

/*-------------------------------------------------------------------------*/

template <typename ElementType, int NUM_NODES>
void NodePool<ElementType, NUM_NODES>::initializePool() {
    for (int i = 0; i < NUM_NODES - 1; i++)
        pool[i].next = i + 1;

    pool[NUM_NODES - 1].next = NULL_VALUE;
    freeList = 0;
}

/*-------------------------------------------------------------------------*/

template <typename ElementType, int NUM_NODES>
int NodePool<ElementType, NUM_NODES>::allocate() {
    if (freeList == NULL_VALUE)
        return NULL_VALUE;

    int idx = freeList;
    freeList = pool[idx].next;

    return idx;
}

/*-------------------------------------------------------------------------*/

template <typename ElementType, int NUM_NODES>
void NodePool<ElementType, NUM_NODES>::deallocate(int index) {
    pool[index].next = freeList;
    freeList = index;
}

/*-------------------------------------------------------------------------*/

template <typename ElementType, int NUM_NODES>
typename NodePool<ElementType, NUM_NODES>::Node&
NodePool<ElementType, NUM_NODES>::getNode(int index) {
    return pool[index];
}

/*-------------------------------------------------------------------------*/

template <typename ElementType, int NUM_NODES>
const typename NodePool<ElementType, NUM_NODES>::Node&
NodePool<ElementType, NUM_NODES>::getNodeConst(int index) const {
    return pool[index];
}

/*-------------------------------------------------------------------------*/

template <typename ElementType, int NUM_NODES>
int NodePool<ElementType, NUM_NODES>::getFFN() const {
    return freeList;
}

/*-------------------------------------------------------------------------*/

#endif
