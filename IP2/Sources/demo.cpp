#include "../Headers/all.h"
#include <iostream>

using namespace std;
using namespace pqueue;


int main() {
    cout << "  PriorityQueue (Linked-List) Demo" << endl;

    PriorityQueue pq;
    cout << "1. Creating empty PriorityQueue" << endl;
    cout << "    Status: " << pq.toString() << endl;
    cout << "    isEmpty: " << (pq.isEmpty() ? "true" : "false") << endl << endl;

    cout << "2. Inserting elements with priorities" << endl;
    cout << "    insert(40, 2)" << endl;
    pq.insert(40, 2);
    cout << "    insert(30, 0)" << endl;
    pq.insert(30, 0);
    cout << "    insert(20, 5)" << endl;
    pq.insert(20, 5);
    cout << "    insert(10, 1)" << endl;
    pq.insert(10, 1);
    cout << "    insert(70, 3)" << endl;
    pq.insert(70, 3);
    cout << "    Status: " << pq.toString() << endl;
    cout << "    Size: " << pq.size() << endl << endl;

    cout << "3. Peek (highest priority element)" << endl;
    cout << "    Peek result: " << pq.peek() << endl << endl;

    cout << "4. Using operator+ to insert (non-modifying)" << endl;
    PriorityQueue pq_new = pq + make_pair(50, 4);
    cout << "    PriorityQueue pq_new = pq + (50, 4)" << endl;
    cout << "    pq (original): " << pq.toString() << endl;
    cout << "    pq_new (copy): " << pq_new.toString() << endl << endl;

    cout << "5. Using operator+= to insert (modifying)" << endl;
    pq += make_pair(50, 4);
    cout << "    pq += (50, 4)" << endl;
    cout << "    Status: " << pq.toString() << endl << endl;

    cout << "6. Dequeue (remove highest priority element)" << endl;
    int removed1 = pq.dequeue();
    cout << "    Dequeued element: " << removed1 << endl;
    cout << "    Status: " << pq.toString() << endl << endl;

    cout << "6. Using operator-= to remove element by value" << endl;
    pq -= 20;
    cout << "    pq -= 20 (remove value 20)" << endl;
    cout << "    Status: " << pq.toString() << endl << endl;

    cout << "7. Using operator- to remove (non-modifying)" << endl;
    PriorityQueue pq_removed = pq - 40;
    cout << "    PriorityQueue pq_removed = pq - 40" << endl;
    cout << "    pq (original): " << pq.toString() << endl;
    cout << "    pq_removed (copy): " << pq_removed.toString() << endl << endl;

    cout << "8. Using operator[] to search for priority of element" << endl;
    int priority = pq[40];
    cout << "    pq[40] = " << priority << " (priority of element 40)" << endl;
    int notFound = pq[999];
    cout << "    pq[999] = " << notFound << " (element not found returns -1)" << endl << endl;

    cout << "9. Using operator*= to update element priority" << endl;
    int oldPriority = 2;
    cout << "    Changing element 40 from priority " << oldPriority << " to priority 0" << endl;
    int result = pq *= make_pair(40, 0);
    cout << "    Result: " << (result != -1 ? "Success (new priority: " + to_string(result) + ")" : "Failed") << endl;
    cout << "    Status: " << pq.toString() << endl << endl;

    cout << "10. Using operator%= (alias for update)" << endl;
    pq %= make_pair(10, 2);
    cout << "    pq %= (10, 2) - update element 10 to priority 2" << endl;
    cout << "    Status: " << pq.toString() << endl << endl;

    cout << "11. Comparison Operators" << endl;
    PriorityQueue pq2;
    pq2.insert(100, 1);
    pq2.insert(200, 2);
    cout << "    pq2 created with 2 elements: " << pq2.toString() << endl;
    cout << "    pq == pq2: " << (pq == pq2 ? "true" : "false") << endl;
    cout << "    pq != pq2: " << (pq != pq2 ? "true" : "false") << endl;
    cout << "    pq < pq2: " << (pq < pq2 ? "true" : "false") << endl;
    cout << "    pq <= pq2: " << (pq <= pq2 ? "true" : "false") << endl;
    cout << "    pq > pq2: " << (pq > pq2 ? "true" : "false") << endl;
    cout << "    pq >= pq2: " << (pq >= pq2 ? "true" : "false") << endl << endl;

    cout << "12. Deep Copy Semantics" << endl;
    PriorityQueue pq3 = pq;
    cout << "    pq3 = pq (copy constructor)" << endl;
    cout << "    pq3: " << pq3.toString() << endl;
    pq3.insert(999, 10);
    cout << "    After pq3.insert(999, 10):" << endl;
    cout << "    pq3: " << pq3.toString() << endl;
    cout << "    pq:  " << pq.toString() << " (unchanged - deep copy verified)" << endl << endl;

    cout << "13. Cleanup Operator!" << endl;
    cout << "    Before: " << pq3.toString() << endl;
    !pq3;
    cout << "    After !pq3: " << pq3.toString() << endl;
    cout << "    isEmpty: " << (pq3.isEmpty() ? "true" : "false") << endl << endl;

    cout << "14. Stream Output Operator" << endl;
    cout << "    cout << pq: " << pq << endl << endl;

    cout << "15. Exception Handling" << endl;
    try {
        cout << "    Attempting to dequeue from empty queue..." << endl;
        !pq;
        pq.dequeue();
    } catch (const EmptyQueueException &e) {
        cout << "    Caught EmptyQueueException: " << e.what() << endl;
    }

    try {
        cout << "    Attempting to insert with negative priority..." << endl;
        pq.insert(100, -5);
    } catch (const InvalidPriorityException &e) {
        cout << "    Caught InvalidPriorityException: " << e.what() << endl;
    }

    cout << endl;

    cout << "16. Memory Leak Detection" << endl;
    cout << "    Before creating test objects:" << endl;
    cout << "    Instance count: " << PriorityQueue::getInstanceCount() << endl;
    cout << "    Node count: " << PriorityQueue::getNodeCount() << endl;
    {
        cout << "    Creating 3 test queues with elements..." << endl;
        PriorityQueue test1, test2, test3;
        test1.insert(10, 1);
        test1.insert(20, 2);
        test2.insert(30, 1);
        test3.insert(40, 1);
        cout << "    Instance count: " << PriorityQueue::getInstanceCount() << " (3 queues)" << endl;
        cout << "    Node count: " << PriorityQueue::getNodeCount() << " (4 total nodes)" << endl;
    }
    cout << "    After destroying test queues:" << endl;
    cout << "    Instance count: " << PriorityQueue::getInstanceCount() << " (all destroyed)" << endl;
    cout << "    Node count: " << PriorityQueue::getNodeCount() << " (all destroyed)" << endl;
    cout << endl;

    cout << "  Demo Completed Successfully!" << endl;

    return 0;
}
