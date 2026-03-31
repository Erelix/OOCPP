#ifndef PRIORITYQUEUE_H_90660
#define PRIORITYQUEUE_H_90660

#include <string>
#include <ostream>
#include "./exceptions.h"

namespace pqueue {

/**
 * PriorityQueue - A priority queue implementation using linked list
 * 
 * Elements are stored in priority order (lower priority number = higher priority).
 * Supports CRUD operations via operators: +/+=, -/-=, *=/%= 
 * Implements 6 comparison operators (==, !=, <, <=, >, >=) for size comparison.
 * 
 * @author Implementation based on GeeksforGeeks with PIMPL refactoring
 * @reference https://www.geeksforgeeks.org/dsa/priority-queue-using-linked-list/
 */
class PriorityQueue {

private:
    class Inner;
    Inner *impl;

    static int instanceCount;

public:
    
    /// Default constructor - creates empty priority queue
    PriorityQueue();
    
    /// Copy constructor - deep copy of another queue
    PriorityQueue(const PriorityQueue &other);
    
    /// Assignment operator - deep copy assignment
    const PriorityQueue& operator=(const PriorityQueue &other);
    
    /// Destructor - cleans up all nodes and impl
    ~PriorityQueue();

    
    /// Insert element with given priority (lower number = higher priority)
    /// Throws InvalidPriorityException if priority < 0
    void insert(int data, int priority);

    /// Get highest priority element without removing it
    /// Throws EmptyQueueException if queue is empty
    int peek() const;
    
    /// Remove and return highest priority element
    /// Throws EmptyQueueException if queue is empty
    int dequeue();
    
    /// Get number of elements in queue
    int size() const;
    
    /// Check if queue is empty
    bool isEmpty() const;


    // CRUD: +/+= for insert, -/-= for remove, *=/%= for update
    
    /// Non-modifying insert: returns NEW queue with element added
    /// Original queue is unchanged
    /// @param element pair of (data, priority)
    /// @return New queue containing all original elements plus new one
    PriorityQueue operator+(const std::pair<int, int> &element) const;
    
    /// Non-modifying remove: returns NEW queue with element removed by value
    /// Original queue is unchanged
    /// @param data Value to remove (if found)
    /// @return New queue with element removed (or unchanged if not found)
    PriorityQueue operator-(int data) const;
    
    /// Modifying insert: adds element TO THIS queue and returns reference
    /// Modifies this queue in-place
    /// @param element pair of (data, priority)
    /// @return Reference to this queue (*this)
    PriorityQueue& operator+=(const std::pair<int, int> &element);
    
    /// Modifying remove: removes element FROM THIS queue and returns reference
    /// Modifies this queue in-place
    /// @param data Value to remove (if found)
    /// @return Reference to this queue (*this)
    PriorityQueue& operator-=(int data);
    
    /// Update element's priority (modifying)
    /// Removes element and re-inserts with new priority
    /// @param updatePair pair of (data, newPriority)
    /// @return New priority on success, -1 if element not found
    /// @throws InvalidPriorityException if newPriority < 0
    int operator*=(const std::pair<int, int> &updatePair);
    
    /// Alternative update operator (same as *=)
    /// Provided for semantic flexibility
    /// @param updatePair pair of (data, newPriority)
    /// @return New priority on success, -1 if element not found
    int operator%=(const std::pair<int, int> &updatePair);


    // All based on queue SIZE, not element content
    
    /// Size equality: true if both queues have same number of elements
    bool operator==(const PriorityQueue &other) const;
    
    /// Size inequality: true if queues have different sizes
    bool operator!=(const PriorityQueue &other) const;
    
    /// Size less than: true if this queue has fewer elements
    bool operator<(const PriorityQueue &other) const;
    
    /// Size less or equal: true if this queue size <= other queue size
    bool operator<=(const PriorityQueue &other) const;
    
    /// Size greater than: true if this queue has more elements
    bool operator>(const PriorityQueue &other) const;
    
    /// Size greater or equal: true if this queue size >= other queue size
    bool operator>=(const PriorityQueue &other) const;

    
    /// Cleanup operator: removes all elements from queue
    /// Makes queue empty without deallocating the queue object itself
    void operator!();
    
    /// Search operator: find priority of element by value
    /// @param data Value to search for
    /// @return Priority of element (0-based, lower = higher priority), or -1 if not found
    int operator[](int data) const;

    
    /// Convert queue to string representation
    /// Format: PriorityQueue[size=N, elements=[(...), (...)]]
    /// @return String showing size and all elements in order
    std::string toString() const;
    
    /// Print queue to stdout
    void print() const;

    
    /// Get total number of PriorityQueue instances
    /// For memory leak detection
    static int getInstanceCount();
    
    /// Get total number of nodes currently allocated
    /// For memory leak detection
    static int getNodeCount();

    
    /// Allow cout << pq; syntax
    /// Calls toString() internally
    friend std::ostream& operator<<(std::ostream &out, const PriorityQueue &pq);
};

std::ostream& operator<<(std::ostream &out, const PriorityQueue &pq);

}

#endif
