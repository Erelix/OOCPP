#include "../../Headers/all.h"

using namespace std;

namespace pqueue {

class PriorityQueue::Inner {
private:
    struct Node {
        int data;
        int priority;
        Node *next;
        
        static int nodeCount;
        
        Node(int d, int p) : data(d), priority(p), next(nullptr) {
            nodeCount++;
        }
        
        ~Node() {
            nodeCount--;
        }
    };

    Node *head;
    int elementCount;
    static int instanceCount;

public:
    Inner() : head(nullptr), elementCount(0) {
        instanceCount++;
    }
    
    ~Inner() {
        clear();
        instanceCount--;
    }
    
    Inner(const Inner &other) : head(nullptr), elementCount(0) {
        instanceCount++;
        Node *current = other.head;
        while (current != nullptr) {
            insert(current->data, current->priority);
            current = current->next;
        }
    }

    void insert(int data, int priority) {
        if (priority < 0) {
            throw InvalidPriorityException("Priority cannot be negative: " + to_string(priority));
        }

        Node *temp = new Node(data, priority);

        if (head == nullptr || head->priority > priority) {
            temp->next = head;
            head = temp;
        } else {
            Node *current = head;
            while (current->next != nullptr && current->next->priority <= priority) {
                current = current->next;
            }
            temp->next = current->next;
            current->next = temp;
        }
        elementCount++;
    }

    int peek() const {
        if (isEmpty()) {
            throw EmptyQueueException("Cannot peek - queue is empty");
        }
        return head->data;
    }

    int dequeue() {
        if (isEmpty()) {
            throw EmptyQueueException("Cannot dequeue - queue is empty");
        }
        Node *temp = head;
        int data = temp->data;
        head = head->next;
        delete temp;
        elementCount--;
        return data;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    int size() const {
        return elementCount;
    }

    void clear() {
        while (head != nullptr) {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
        elementCount = 0;
    }

    int findPriority(int data) const {
        Node *current = head;
        while (current != nullptr) {
            if (current->data == data) {
                return current->priority;
            }
            current = current->next;
        }
        return -1;
    }

    bool removeByValue(int data) {
        if (isEmpty()) return false;

        if (head->data == data) {
            Node *temp = head;
            head = head->next;
            delete temp;
            elementCount--;
            return true;
        }

        Node *current = head;
        while (current->next != nullptr) {
            if (current->next->data == data) {
                Node *temp = current->next;
                current->next = temp->next;
                delete temp;
                elementCount--;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    int updatePriority(int data, int newPriority) {
        if (newPriority < 0) {
            throw InvalidPriorityException("Priority cannot be negative: " + to_string(newPriority));
        }
        
        if (removeByValue(data)) {
            insert(data, newPriority);
            return newPriority;
        }
        return -1;
    }

    bool equals(const Inner &other) const {
        if (elementCount != other.elementCount) return false;

        Node *current1 = head;
        Node *current2 = other.head;

        while (current1 != nullptr) {
            if (current1->data != current2->data || current1->priority != current2->priority) {
                return false;
            }
            current1 = current1->next;
            current2 = current2->next;
        }
        return true;
    }

    string toString() const {
        stringstream ss;
        ss << "PriorityQueue[size=" << elementCount << ", elements=[";
        
        Node *current = head;
        bool first = true;
        while (current != nullptr) {
            if (!first) ss << ", ";
            ss << "(" << current->data << ":p" << current->priority << ")";
            current = current->next;
            first = false;
        }
        ss << "]]";
        return ss.str();
    }

    static int getInstanceCountValue() {
        return instanceCount;
    }

    void print() const {
        cout << toString() << endl;
    }

    string getElementsString() const {
        stringstream ss;
        Node *current = head;
        while (current != nullptr) {
            ss << current->data << " ";
            current = current->next;
        }
        return ss.str();
    }

    static int getNodeCountValue() {
        return Node::nodeCount;
    }
};

int PriorityQueue::Inner::Node::nodeCount = 0;




int PriorityQueue::Inner::instanceCount = 0;

PriorityQueue::PriorityQueue() : impl(new Inner()) {
}

PriorityQueue::PriorityQueue(const PriorityQueue &other) : impl(new Inner(*other.impl)) {
}

const PriorityQueue& PriorityQueue::operator=(const PriorityQueue &other) {
    if (this != &other) {
        delete impl;
        impl = new Inner(*other.impl);
    }
    return *this;
}

PriorityQueue::~PriorityQueue() {
    delete impl;
}

void PriorityQueue::insert(int data, int priority) {
    impl->insert(data, priority);
}

int PriorityQueue::peek() const {
    return impl->peek();
}

int PriorityQueue::dequeue() {
    return impl->dequeue();
}

int PriorityQueue::size() const {
    return impl->size();
}

bool PriorityQueue::isEmpty() const {
    return impl->isEmpty();
}

PriorityQueue PriorityQueue::operator+(const std::pair<int, int> &element) const {
    PriorityQueue result(*this);
    result.impl->insert(element.first, element.second);
    return result;
}

PriorityQueue PriorityQueue::operator-(int data) const {
    PriorityQueue result(*this);
    result.impl->removeByValue(data);
    return result;
}

PriorityQueue& PriorityQueue::operator+=(const std::pair<int, int> &element) {
    impl->insert(element.first, element.second);
    return *this;
}

PriorityQueue& PriorityQueue::operator-=(int data) {
    impl->removeByValue(data);
    return *this;
}

int PriorityQueue::operator*=(const std::pair<int, int> &updatePair) {
    return impl->updatePriority(updatePair.first, updatePair.second);
}

int PriorityQueue::operator%=(const std::pair<int, int> &updatePair) {
    return impl->updatePriority(updatePair.first, updatePair.second);
}

bool PriorityQueue::operator==(const PriorityQueue &other) const {
    return impl->size() == other.impl->size();
}

bool PriorityQueue::operator!=(const PriorityQueue &other) const {
    return !(*this == other);
}

bool PriorityQueue::operator<(const PriorityQueue &other) const {
    return impl->size() < other.impl->size();
}

bool PriorityQueue::operator<=(const PriorityQueue &other) const {
    return impl->size() <= other.impl->size();
}

bool PriorityQueue::operator>(const PriorityQueue &other) const {
    return impl->size() > other.impl->size();
}

bool PriorityQueue::operator>=(const PriorityQueue &other) const {
    return impl->size() >= other.impl->size();
}

void PriorityQueue::operator!() {
    impl->clear();
}

int PriorityQueue::operator[](int data) const {
    return impl->findPriority(data);
}

string PriorityQueue::toString() const {
    return impl->toString();
}

void PriorityQueue::print() const {
    impl->print();
}

ostream& operator<<(ostream &out, const PriorityQueue &pq) {
    out << pq.toString();
    return out;
}

int PriorityQueue::getInstanceCount() {
    return Inner::getInstanceCountValue();
}

int PriorityQueue::getNodeCount() {
    return Inner::getNodeCountValue();
}

}
