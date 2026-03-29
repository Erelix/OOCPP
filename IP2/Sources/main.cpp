#include "../Headers/all.h"
#include <iostream>
#include <limits>

using namespace std;
using namespace pqueue;


void displayMenu() {
    cout << "\n========================================" << endl;
    cout << "   PriorityQueue Interactive Menu" << endl;
    cout << "========================================" << endl;
    cout << "1. Insert element (data, priority)" << endl;
    cout << "2. Peek (view highest priority element)" << endl;
    cout << "3. Dequeue (remove highest priority element)" << endl;
    cout << "4. Search element by value" << endl;
    cout << "5. Update element priority" << endl;
    cout << "6. View queue status" << endl;
    cout << "7. Clear queue" << endl;
    cout << "8. Size of queue" << endl;
    cout << "\n0. Exit" << endl;
    cout << "========================================" << endl;
    cout << "Enter your choice (0-8): ";
}

int main() {
    PriorityQueue pq;
    int choice = 0;
    int data = 0, priority = 0;


    while (true) {
        displayMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n[ERROR] Invalid input! Please enter a number." << endl;
            continue;
        }

        switch (choice) {
            case 1: {
                cout << "\n[INSERT]" << endl;
                cout << "Enter data value: ";
                cin >> data;
                cout << "Enter priority (lower number = higher priority): ";
                cin >> priority;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "[ERROR] Invalid input!" << endl;
                    break;
                }

                try {
                    pq.insert(data, priority);
                    cout << "[SUCCESS] Inserted (" << data << ", priority=" << priority << ")" << endl;
                    cout << "Queue: " << pq.toString() << endl;
                } catch (const exception &e) {
                    cout << "[ERROR] " << e.what() << endl;
                }
                break;
            }

            case 2: {
                cout << "\n[PEEK]" << endl;
                try {
                    int result = pq.peek();
                    cout << "[SUCCESS] Highest priority element: " << result << endl;
                    cout << "Queue: " << pq.toString() << endl;
                } catch (const exception &e) {
                    cout << "[ERROR] " << e.what() << endl;
                }
                break;
            }

            case 3: {
                cout << "\n[DEQUEUE]" << endl;
                try {
                    int result = pq.dequeue();
                    cout << "[SUCCESS] Dequeued: " << result << endl;
                    cout << "Queue: " << pq.toString() << endl;
                } catch (const exception &e) {
                    cout << "[ERROR] " << e.what() << endl;
                }
                break;
            }

            case 4: {
                cout << "\n[SEARCH]" << endl;
                cout << "Enter data value to search: ";
                cin >> data;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "[ERROR] Invalid input!" << endl;
                    break;
                }

                int result = pq[data];
                if (result == -1) {
                    cout << "[NOT FOUND] Element " << data << " not in queue" << endl;
                } else {
                    cout << "[FOUND] Element " << data << " has priority: " << result << endl;
                }
                cout << "Queue: " << pq.toString() << endl;
                break;
            }

            case 5: {
                cout << "\n[UPDATE PRIORITY]" << endl;
                cout << "Enter data value: ";
                cin >> data;
                cout << "Enter new priority: ";
                cin >> priority;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "[ERROR] Invalid input!" << endl;
                    break;
                }

                try {
                    int oldPriority = pq[data];
                    if (oldPriority == -1) {
                        cout << "[ERROR] Element " << data << " not found in queue" << endl;
                    } else {
                        int newPriority = pq *= make_pair(data, priority);
                        cout << "[SUCCESS] Updated " << data << " from priority " 
                             << oldPriority << " to " << newPriority << endl;
                        cout << "Queue: " << pq.toString() << endl;
                    }
                } catch (const exception &e) {
                    cout << "[ERROR] " << e.what() << endl;
                }
                break;
            }

            case 6: {
                // View queue status
                cout << "\n[QUEUE STATUS]" << endl;
                cout << "Queue: " << pq.toString() << endl;
                cout << "Size: " << pq.size() << endl;
                cout << "Empty: " << (pq.isEmpty() ? "Yes" : "No") << endl;
                break;
            }

            case 7: {
                cout << "\n[CLEAR QUEUE]" << endl;
                !pq;
                cout << "[SUCCESS] Queue cleared" << endl;
                cout << "Queue: " << pq.toString() << endl;
                break;
            }

            case 8: {
                cout << "\n[SIZE]" << endl;
                cout << "Queue size: " << pq.size() << endl;
                break;
            }

            case 0: {
                cout << "\n[EXIT]" << endl;
                cout << "Program has been exited." << endl;
                return 0;
            }

            default:
                cout << "\n[ERROR] Invalid choice! Please enter a number between 0-8." << endl;
        }
    }

    return 0;
}
