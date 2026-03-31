#include "../Headers/all.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>
#include <iomanip>

using namespace std;
using namespace pqueue;

int testsRun = 0;
int testsPassed = 0;
int testsFailed = 0;

ofstream logFile;

#define TEST(condition, testName) \
    do { \
        testsRun++; \
        bool result = (condition); \
        string status = result ? "PASS" : "FAIL"; \
        stringstream ss; \
        ss << "[" << setw(3) << testsRun << "] " << status << " " << testName; \
        string msg = ss.str(); \
        cout << msg << endl; \
        logFile << msg << endl; \
        if (result) testsPassed++; \
        else testsFailed++; \
    } while(0)

int main() {
    logFile.open("log.txt", ios::out);
    if (!logFile.is_open()) {
        cerr << "ERROR: Could not open log.txt" << endl;
        return 1;
    }

    string header = "========== PriorityQueue Test Suites ==========";
    cout << header << endl;
    logFile << header << endl;

    cout << endl;
    logFile << endl;

    {
        string sectionName = "--- Suite 1: Basic Operations ---";
        cout << sectionName << endl;
        logFile << sectionName << endl << endl;

        PriorityQueue pq;
        TEST(pq.isEmpty() == true, "New queue is empty");
        TEST(pq.size() == 0, "New queue has size 0");

        pq.insert(10, 5);
        TEST(pq.isEmpty() == false, "Queue not empty after insert");
        TEST(pq.size() == 1, "Queue size is 1 after one insert");
        TEST(pq.peek() == 10, "Peek returns correct element");

        logFile << endl;
    }


    {
        string sectionName = "--- Suite 2: Insert and Priority Ordering ---";
        cout << sectionName << endl;
        logFile << sectionName << endl << endl;

        PriorityQueue pq;
        pq.insert(40, 2);
        pq.insert(30, 0);
        pq.insert(50, 3);
        pq.insert(20, 1);

        TEST(pq.peek() == 30, "Highest priority (0) element is first: 30");
        TEST(pq.size() == 4, "Size is 4 after 4 inserts");

        logFile << endl;
    }


    {
        string sectionName = "--- Suite 3: Dequeue Operations ---";
        cout << sectionName << endl;
        logFile << sectionName << endl << endl;

        PriorityQueue pq;
        pq.insert(40, 2);
        pq.insert(30, 0);
        pq.insert(50, 1);

        int first = pq.dequeue();
        TEST(first == 30, "First dequeue returns element with priority 0");
        TEST(pq.size() == 2, "Size is 2 after one dequeue");

        int second = pq.dequeue();
        TEST(second == 50, "Second dequeue returns element with priority 1");
        TEST(pq.size() == 1, "Size is 1");

        int third = pq.dequeue();
        TEST(third == 40, "Third dequeue returns element with priority 2");
        TEST(pq.isEmpty(), "Queue empty after dequeueing all");

        logFile << endl;
    }


    {
        string sectionName = "--- Suite 4: Operator += (Insert) ---";
        cout << sectionName << endl;
        logFile << sectionName << endl << endl;

        PriorityQueue pq;
        pq += make_pair(100, 1);
        TEST(pq.size() == 1, "Size 1 after += insert");
        TEST(pq.peek() == 100, "Element inserted correctly");

        pq += make_pair(50, 0);
        TEST(pq.peek() == 50, "New high-priority element becomes peek");
        TEST(pq.size() == 2, "Size is 2");

        logFile << endl;
    }


    {
        string sectionName = "--- Suite 4a: Operator + (Non-modifying Insert) ---";
        cout << sectionName << endl;
        logFile << sectionName << endl << endl;

        PriorityQueue pq;
        pq.insert(100, 1);
        pq.insert(200, 2);

        PriorityQueue pq_new = pq + make_pair(50, 0);
        TEST(pq.size() == 2, "Original size unchanged");
        TEST(pq_new.size() == 3, "New queue has size 3");
        TEST(pq_new.peek() == 50, "New element has highest priority");
        TEST(pq.peek() == 100, "Original peek unchanged");

        logFile << endl;
    }


    {
        string sectionName = "\n--- Suite 5: Operator -= (Delete) ---";
        cout << sectionName << endl;
        logFile << sectionName << endl << endl;

        PriorityQueue pq;
        pq.insert(10, 1);
        pq.insert(20, 2);
        pq.insert(30, 3);

        pq -= 20;
        TEST(pq.size() == 2, "Size reduced to 2 after delete");
        TEST(pq[20] == -1, "Deleted element not found (returns -1)");

        pq -= 10;
        TEST(pq.size() == 1, "Size is 1");
        TEST(pq.peek() == 30, "Remaining element is correct");

        logFile << endl;
    }


    {
        string sectionName = "\n--- Suite 5a: Operator - (Non-modifying Delete) ---";
        cout << sectionName << endl;
        logFile << sectionName << endl << endl;

        PriorityQueue pq;
        pq.insert(10, 1);
        pq.insert(20, 2);
        pq.insert(30, 3);

        PriorityQueue pq_removed = pq - 20;
        TEST(pq.size() == 3, "Original size unchanged");
        TEST(pq_removed.size() == 2, "New queue has size 2");
        TEST(pq[20] == 2, "Original still contains element 20");
        TEST(pq_removed[20] == -1, "New queue doesn't have element 20");
        TEST(pq_removed.peek() == 10, "New queue peek is correct");

        logFile << endl;
    }


    {
        string sectionName = "\n--- Suite 6: Operator[] (Search) ---";
        cout << sectionName << endl;
        logFile << sectionName << endl << endl;

        PriorityQueue pq;
        pq.insert(100, 2);
        pq.insert(200, 1);
        pq.insert(300, 3);

        TEST(pq[100] == 2, "Search finds priority of element 100");
        TEST(pq[200] == 1, "Search finds priority of element 200");
        TEST(pq[300] == 3, "Search finds priority of element 300");
        TEST(pq[999] == -1, "Search returns -1 for non-existent element");

        logFile << endl;
    }


    {
        string sectionName = "--- Suite 7: Operator *= (Update) ---";
        cout << sectionName << endl;
        logFile << sectionName << endl << endl;

        PriorityQueue pq;
        pq.insert(10, 5);
        pq.insert(20, 3);
        pq.insert(30, 1);

        int updateResult = pq *= make_pair(10, 0);
        TEST(updateResult == 0, "Update returns new priority");
        TEST(pq[10] == 0, "Element priority updated");
        TEST(pq.peek() == 10, "Updated element now has highest priority");

        int notFound = pq *= make_pair(999, 5);
        TEST(notFound == -1, "Update non-existent returns -1");

        logFile << endl;
    }


    {
        string sectionName = "--- Suite 8: Operator %= (Update Alias) ---";
        cout << sectionName << endl;
        logFile << sectionName << endl << endl;

        PriorityQueue pq;
        pq.insert(10, 5);
        pq.insert(20, 3);

        int modifyResult = pq %= make_pair(20, 1);
        TEST(modifyResult == 1, "%= operator works like *=");
        TEST(pq[20] == 1, "Priority updated via %=");

        logFile << endl;
    }


    {
        string sectionName = "--- Suite 9: Comparison Operators (==, !=, <, <=, >, >=) ---";
        cout << sectionName << endl;
        logFile << sectionName << endl << endl;

        PriorityQueue pq1, pq2, pq3;
        
        pq1.insert(10, 1);
        pq1.insert(20, 2);
        pq2.insert(10, 1);
        pq2.insert(20, 2);
        
        TEST(pq1 == pq2, "Equal queues return true for ==");
        TEST(!(pq1 != pq2), "Equal queues return false for !=");

        pq3.insert(10, 1);
        TEST(pq1 != pq3, "Different queues return true for !=");
        TEST(pq3 < pq1, "Smaller queue < larger queue");
        TEST(pq3 <= pq1, "Smaller queue <= larger queue");
        TEST(pq1 > pq3, "Larger queue > smaller queue");
        TEST(pq1 >= pq3, "Larger queue >= smaller queue");

        logFile << endl;
    }


    {
        string sectionName = "--- Suite 10: Cleanup Operator! ---";
        cout << sectionName << endl;
        logFile << sectionName << endl << endl;

        PriorityQueue pq;
        pq.insert(10, 1);
        pq.insert(20, 2);
        pq.insert(30, 3);
        TEST(pq.size() == 3, "Queue has 3 elements before cleanup");

        !pq;
        TEST(pq.isEmpty(), "Queue empty after !");
        TEST(pq.size() == 0, "Size is 0 after cleanup");

        logFile << endl;
    }


    {
        string sectionName = "--- Suite 11: Copy Semantics (Deep Copy) ---";
        cout << sectionName << endl;
        logFile << sectionName << endl << endl;

        PriorityQueue original;
        original.insert(10, 1);
        original.insert(20, 2);

        PriorityQueue copy1(original);
        TEST(copy1.size() == 2, "Copy constructor copies all elements");
        TEST(copy1[10] == 1, "Copy contains correct element data");

        PriorityQueue copy2;
        copy2 = original;
        TEST(copy2.size() == 2, "Assignment operator copies elements");

        copy2.insert(30, 3);
        TEST(original.size() == 2, "Original size unchanged after modifying copy");
        TEST(copy2.size() == 3, "Modified copy has new size");
        TEST(original[30] == -1, "Original doesn't have new element");

        logFile << endl;
    }


    {
        string sectionName = "--- Suite 12: toString() Method ---";
        cout << sectionName << endl;
        logFile << sectionName << endl << endl;

        PriorityQueue pq;
        string empty = pq.toString();
        TEST(empty.find("size=0") != string::npos, "toString shows size for empty queue");

        pq.insert(10, 1);
        pq.insert(20, 2);
        string withElements = pq.toString();
        TEST(withElements.find("size=2") != string::npos, "toString shows correct size");
        TEST(withElements.find("10") != string::npos, "toString contains element data");

        logFile << endl;
    }


    {
        string sectionName = "--- Suite 13: Exception Handling ---";
        cout << sectionName << endl;
        logFile << sectionName << endl << endl;

        PriorityQueue pq;

        bool exceptionThrown = false;
        try {
            pq.dequeue();
        } catch (const EmptyQueueException &e) {
            exceptionThrown = true;
        }
        TEST(exceptionThrown, "EmptyQueueException thrown on dequeue from empty queue");

        exceptionThrown = false;
        try {
            pq.peek();
        } catch (const EmptyQueueException &e) {
            exceptionThrown = true;
        }
        TEST(exceptionThrown, "EmptyQueueException thrown on peek from empty queue");

        exceptionThrown = false;
        try {
            pq.insert(10, -5);
        } catch (const InvalidPriorityException &e) {
            exceptionThrown = true;
        }
        TEST(exceptionThrown, "InvalidPriorityException thrown for negative priority");

        logFile << endl;
    }


    {
        string sectionName = "--- Suite 14: Stress Test (Many Operations) ---";
        cout << sectionName << endl;
        logFile << sectionName << endl << endl;

        PriorityQueue pq;
        
        for (int i = 0; i < 10; i++) {
            pq.insert(i * 10, i % 5);
        }
        TEST(pq.size() == 10, "Stress test: inserted 10 elements");

        int highestPriority = pq.peek();
        TEST(highestPriority >= 0, "Stress test: peek returns valid element");

        pq.dequeue();
        TEST(pq.size() == 9, "Stress test: size correct after dequeue");

        !pq;
        TEST(pq.isEmpty(), "Stress test: cleanup works");

        logFile << endl;
    }


    {
        string sectionName = "--- Suite 15: Stream Output Operator ---";
        cout << sectionName << endl;
        logFile << sectionName << endl << endl;

        PriorityQueue pq;
        pq.insert(42, 1);
        
        stringstream ss;
        ss << pq;
        string output = ss.str();
        TEST(output.find("42") != string::npos, "Stream operator includes element data");
        TEST(output.find("size=1") != string::npos, "Stream operator includes size");

        logFile << endl;
    }


    cout << endl;
    logFile << endl;


    {
        string sectionName = "--- Suite 16: Memory Leak Detection (Instance Counting) ---";
        cout << sectionName << endl;
        logFile << sectionName << endl << endl;

        {
            PriorityQueue pq1;
            TEST(PriorityQueue::getInstanceCount() == 1, "Instance count 1 after creating pq1");
        }
        TEST(PriorityQueue::getInstanceCount() == 0, "Instance count naturally returns to 0 after pq1 destroyed");

        {
            PriorityQueue pq1;
            PriorityQueue pq2;
            TEST(PriorityQueue::getInstanceCount() == 2, "Instance count 2 with two objects");
            
            {
                PriorityQueue pq3;
                TEST(PriorityQueue::getInstanceCount() == 3, "Instance count 3 with three objects");
            }
            TEST(PriorityQueue::getInstanceCount() == 2, "Instance count 2 after pq3 destroyed");
        }
        TEST(PriorityQueue::getInstanceCount() == 0, "Instance count 0 after all destroyed");

        {
            PriorityQueue original;
            TEST(PriorityQueue::getInstanceCount() == 1, "Instance count 1 after creating original");
            
            PriorityQueue copy(original);
            TEST(PriorityQueue::getInstanceCount() == 2, "Instance count 2 after copy constructor");
        }
        TEST(PriorityQueue::getInstanceCount() == 0, "Instance count 0 after both destroyed");

        {
            PriorityQueue pq1;
            PriorityQueue pq2;
            TEST(PriorityQueue::getInstanceCount() == 2, "Instance count 2 before assignment");
            
            pq2 = pq1;
            TEST(PriorityQueue::getInstanceCount() == 2, "Instance count still 2 after assignment (not a new object)");
        }
        TEST(PriorityQueue::getInstanceCount() == 0, "Instance count 0 after cleanup");

        {
            PriorityQueue queues[5];
            TEST(PriorityQueue::getInstanceCount() == 5, "Instance count 5 with array of 5 objects");
        }
        TEST(PriorityQueue::getInstanceCount() == 0, "Instance count 0 after array destroyed (no memory leak)");

        logFile << endl;
    }

    {
        string sectionName = "--- Suite 17: Node Memory Leak Detection ---";
        cout << sectionName << endl;
        logFile << sectionName << endl << endl;

        {
            PriorityQueue pq;
            pq.insert(10, 1);
            TEST(PriorityQueue::getNodeCount() == 1, "Node count 1 after single insert");
        }
        TEST(PriorityQueue::getNodeCount() == 0, "Node count returns to 0 after queue destroyed (no leak)");

        {
            PriorityQueue pq;
            pq.insert(10, 1);
            TEST(PriorityQueue::getNodeCount() == 1, "Node count 1 after 1st insert");
            pq.insert(20, 2);
            TEST(PriorityQueue::getNodeCount() == 2, "Node count 2 after 2nd insert");
            pq.insert(30, 3);
            TEST(PriorityQueue::getNodeCount() == 3, "Node count 3 after 3rd insert");
        }
        TEST(PriorityQueue::getNodeCount() == 0, "All nodes destroyed with queue");

        {
            PriorityQueue pq;
            pq.insert(10, 1);
            pq.insert(20, 2);
            pq.insert(30, 3);
            TEST(PriorityQueue::getNodeCount() == 3, "Node count 3 before dequeue");

            pq.dequeue();
            TEST(PriorityQueue::getNodeCount() == 2, "Node count 2 after 1st dequeue");
            
            pq.dequeue();
            TEST(PriorityQueue::getNodeCount() == 1, "Node count 1 after 2nd dequeue");
            
            pq.dequeue();
            TEST(PriorityQueue::getNodeCount() == 0, "Node count 0 after dequeueing all");
        }
        TEST(PriorityQueue::getNodeCount() == 0, "No lingering nodes");

        {
            PriorityQueue pq;
            pq.insert(10, 1);
            pq.insert(20, 2);
            pq.insert(30, 3);
            pq.insert(40, 4);
            TEST(PriorityQueue::getNodeCount() == 4, "Node count 4 before clear");
            
            !pq;
            TEST(PriorityQueue::getNodeCount() == 0, "Node count 0 after clear (no leaks)");
        }
        
        {
            PriorityQueue pq;
            pq.insert(10, 1);
            pq.insert(20, 2);
            pq.insert(30, 3);
            TEST(PriorityQueue::getNodeCount() == 3, "Node count 3 before removal");

            pq -= 20;
            TEST(PriorityQueue::getNodeCount() == 2, "Node count 2 after removing middle node");
            
            pq -= 10;
            TEST(PriorityQueue::getNodeCount() == 1, "Node count 1 after removing head");
            
            pq -= 30;
            TEST(PriorityQueue::getNodeCount() == 0, "Node count 0 after removing last node");
        }
  
        {
            PriorityQueue original;
            original.insert(10, 1);
            original.insert(20, 2);
            TEST(PriorityQueue::getNodeCount() == 2, "Original has 2 nodes");

            PriorityQueue copy(original);
            TEST(PriorityQueue::getNodeCount() == 4, "Copy has 2 new nodes (4 total)");
        }
        TEST(PriorityQueue::getNodeCount() == 0, "All nodes destroyed (no leak)");

        {
            PriorityQueue pq1;
            pq1.insert(100, 1);
            pq1.insert(200, 2);
            TEST(PriorityQueue::getNodeCount() == 2, "pq1 has 2 nodes");

            PriorityQueue pq2;
            pq2.insert(50, 1);
            TEST(PriorityQueue::getNodeCount() == 3, "pq2 added 1 node (3 total)");

            pq2 = pq1;
            TEST(PriorityQueue::getNodeCount() == 4, "After assignment, 4 nodes total (pq1 has 2, pq2 now has 2 from deep copy)");
        }
        TEST(PriorityQueue::getNodeCount() == 0, "All nodes destroyed");

        {
            PriorityQueue pq;
            for (int i = 0; i < 20; i++) {
                pq.insert(i * 10, i % 5);
            }
            TEST(PriorityQueue::getNodeCount() == 20, "Node count 20 after 20 inserts");

            for (int i = 0; i < 10; i++) {
                pq.dequeue();
            }
            TEST(PriorityQueue::getNodeCount() == 10, "Node count 10 after 10 dequeues");

            !pq;
            TEST(PriorityQueue::getNodeCount() == 0, "Node count 0 after clear (stress test)");
        }
        TEST(PriorityQueue::getNodeCount() == 0, "No lingering nodes after stress test");

        logFile << endl;
    }

    {
        string sectionName = "--- Suite 18: Combined Memory Integrity Check ---";
        cout << sectionName << endl;
        logFile << sectionName << endl << endl;

        {
            PriorityQueue pq1, pq2, pq3;
            TEST(PriorityQueue::getInstanceCount() == 3, "Instance count 3");

            pq1.insert(1, 1);
            pq1.insert(2, 2);
            pq2.insert(5, 1);
            pq3.insert(10, 1);
            TEST(PriorityQueue::getNodeCount() == 4, "Node count 4 from all queues");

            pq1 = pq2;
            TEST(PriorityQueue::getNodeCount() == 3, "Node count 3 after assignment: pq1 (1 from copy), pq2 (1 original), pq3 (1)");

            pq1.dequeue();
            TEST(PriorityQueue::getNodeCount() == 2, "Node count 2 after dequeue from pq1: pq2 (1), pq3 (1)");
        }

        TEST(PriorityQueue::getInstanceCount() == 0, "All instances destroyed.");
        TEST(PriorityQueue::getNodeCount() == 0, "All nodes destroyed.");

        logFile << endl;
    }


    cout << endl;
    logFile << endl;

    string summary = "========== Test Summary ==========";
    cout << summary << endl;
    logFile << summary << endl;
    
    string line1 = "Total tests run: " + to_string(testsRun);
    string line2 = "Tests passed:   " + to_string(testsPassed);
    string line3 = "Tests failed:   " + to_string(testsFailed);
    string line4 = "Success rate:   " + to_string((testsPassed * 100) / testsRun) + "%";

    cout << line1 << endl;
    cout << line2 << endl;
    cout << line3 << endl;
    cout << line4 << endl;

    logFile << line1 << endl;
    logFile << line2 << endl;
    logFile << line3 << endl;
    logFile << line4 << endl;

    string status = (testsFailed == 0) ? "ALL TESTS PASSED" : "SOME TESTS FAILED";
    cout << endl << status << endl;
    logFile << endl << status << endl;

    logFile.close();

    return (testsFailed == 0) ? 0 : 1;
}
