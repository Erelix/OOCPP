#ifndef PRIORITYQUEUE_H_90660
#define PRIORITYQUEUE_H_90660

#include <string>
#include <ostream>
#include "./exceptions.h"

namespace pqueue {

// @author Implementation based on GeeksforGeeks with PIMPL refactoring
// https://www.geeksforgeeks.org/dsa/priority-queue-using-linked-list/
class PriorityQueue {

private:
    class Inner;
    Inner *impl;

    static int instanceCount;

public:
    PriorityQueue();
    PriorityQueue(const PriorityQueue &other);
    const PriorityQueue& operator=(const PriorityQueue &other);
    ~PriorityQueue();

    void insert(int data, int priority);

    int peek() const;
    int dequeue();
    int size() const;
    
    bool isEmpty() const;
    
    PriorityQueue& operator+=(const std::pair<int, int> &element);
    PriorityQueue& operator-=(int data);
    
    // Update priority of element (if found)
    // Returns new priority, -1 if not found
    int operator*=(const std::pair<int, int> &updatePair);
    int operator%=(const std::pair<int, int> &updatePair);

    // Compare queue size (element count)
    bool operator==(const PriorityQueue &other) const;
    bool operator!=(const PriorityQueue &other) const;
    bool operator<(const PriorityQueue &other) const;
    bool operator<=(const PriorityQueue &other) const;
    bool operator>(const PriorityQueue &other) const;
    bool operator>=(const PriorityQueue &other) const;

    void operator!(); // Cleanup 
    
    int operator[](int data) const; // Search by value, -1 if not found

    std::string toString() const;
    
    void print() const;

    static int getInstanceCount();
    static int getNodeCount();

    friend std::ostream& operator<<(std::ostream &out, const PriorityQueue &pq);
};

std::ostream& operator<<(std::ostream &out, const PriorityQueue &pq);

}

#endif
