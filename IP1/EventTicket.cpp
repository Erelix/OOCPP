#include <iostream>
#include <sstream>
#include <stdexcept>
#include <functional>

#include <cassert>
#include <vector>
#include <ctime>
#include <cstring>

// g++ -o P1 P1.cpp
// ./P1

using namespace std;

const char* DATETIME_FORMAT = "%Y-%m-%d %H:%M:%S";

bool isValidDateTime(const char* datetimeString) {
    if (datetimeString == nullptr || strlen(datetimeString) == 0) {
        return false;
    }
    
    struct tm tmStruct = {};
    char* result = strptime(datetimeString, DATETIME_FORMAT, &tmStruct);
    
    if (result == nullptr || *result != '\0') {
        return false;
    }
    
    if (tmStruct.tm_year < 0 || tmStruct.tm_mon < 0 || tmStruct.tm_mon > 11 ||
        tmStruct.tm_mday < 1 || tmStruct.tm_mday > 31 ||
        tmStruct.tm_hour < 0 || tmStruct.tm_hour > 23 ||
        tmStruct.tm_min < 0 || tmStruct.tm_min > 59 ||
        tmStruct.tm_sec < 0 || tmStruct.tm_sec > 59) {
        return false;
    }
    
    return true;
}

time_t parseDateTime(const char* datetimeString) {
    if (!isValidDateTime(datetimeString)) {
        throw invalid_argument("Invalid date format");
    }
    
    struct tm tmStruct = {};
    strptime(datetimeString, DATETIME_FORMAT, &tmStruct);
    return mktime(&tmStruct);
}

string formatDateTime(time_t time) {
    char buffer[90];
    struct tm* timeinfo = localtime(&time);
    strftime(buffer, sizeof(buffer), DATETIME_FORMAT, timeinfo);
    return buffer;
}

bool isValidPrice(double price) {
    return price >= 0;
}

class EventTicket {
    private:
        int id;
        string eventName;
        string seatNumber;
        double price;
        bool isUsed;
        time_t eventDate;
        
        static int lastId;
        static int objectCount;

    public:
        EventTicket(string eventName, string seatNumber, double price, time_t eventDate) {
            init(eventName, seatNumber, price, eventDate, false);
        }
        
        EventTicket(string eventName, string seatNumber, double price, time_t eventDate, bool isUsed) {
            init(eventName, seatNumber, price, eventDate, isUsed);
        }
        
        ~EventTicket() {
            --objectCount;
        }

    private:
        void init(string eventName, string seatNumber, double price, time_t eventDate, bool isUsed) {
            id = lastId++;
            setEventName(eventName);
            setSeatNumber(seatNumber);
            setPrice(price);
            setEventDate(eventDate);
            setIsUsed(isUsed);
            ++objectCount;
        }
        
        void setEventName(string eventName) {
            this->eventName = eventName;
        }
        
        void setSeatNumber(string seatNumber) {
            this->seatNumber = seatNumber;
        }
        
        void setPrice(double price) {
            if (!isValidPrice(price)) {
                throw invalid_argument("Price cannot be negative");
            }
            this->price = price;
        }
        
        void setEventDate(time_t eventDate) {
            this->eventDate = eventDate;
        }
        
        void setIsUsed(bool isUsed) {
            this->isUsed = isUsed;
        }

    public:
        int getId() {
            return id;
        }
        
        string getEventName() {
            return eventName;
        }
        
        string getSeatNumber() {
            return seatNumber;
        }
        
        double getPrice() {
            return price;
        }
        
        bool getIsUsed() {
            return isUsed;
        }
        
        time_t getEventDate() {
            return eventDate;
        }
        
        static int getObjectCount() {
            return objectCount;
        }
        
        string toString() {
            stringstream ss;
            ss << eventName << " " << seatNumber << " " << price << " " << formatDateTime(eventDate) << " " << id;
            return ss.str();
        }
};

int EventTicket::lastId = 0;
int EventTicket::objectCount = 0;

int testsPassed = 0;
int testsFailed = 0;

void check(bool condition, string testName) {
    if (condition) {
        cout << "[PASS] " << testName << endl;
        testsPassed++;
    } else {
        cout << "[FAIL] " << testName << endl;
        testsFailed++;
    }
}

// To reduce code duplication in exception tests
void testException(function<void()> testFunction, string expectedMessage, string testName) {
    bool exceptionCaught = false;
    try {
        testFunction();
    } catch (invalid_argument& e) {
        exceptionCaught = true;
        if (!expectedMessage.empty()) {
            check(string(e.what()).find(expectedMessage) != string::npos, 
                  testName + " - exception message correct");
        }
    } catch (...) {
        check(false, testName + " - wrong exception type");
    }
    check(exceptionCaught, testName);
}

int main() {
    cout << "Initial object count: " << EventTicket::getObjectCount() << endl;
    check(EventTicket::getObjectCount() == 0, "Initial object count is 0");

    try {
        cout << "\n=== TEST 1: Object Creation, Getters, and toString ===" << endl;
        
        EventTicket* t1 = new EventTicket("Don Juan", "J-17", 57.0, parseDateTime("2026-03-15 18:30:00"));
        
        check(t1->getEventName() == "Don Juan", "getEventName returns correct value");
        check(t1->getSeatNumber() == "J-17", "getSeatNumber returns correct value");
        check(t1->getPrice() == 57.0, "getPrice returns correct value");
        check(t1->getEventDate() == parseDateTime("2026-03-15 18:30:00"), "getEventDate returns correct value");
        check(t1->getIsUsed() == false, "getIsUsed returns correct default value");
        check(t1->getId() == 0, "getId returns correct value");
        
        string toStringResult = t1->toString();
        check(toStringResult.find("Don Juan") != string::npos, "toString contains event name");
        check(toStringResult.find("J-17") != string::npos, "toString contains seat number");
        check(toStringResult.find("57") != string::npos, "toString contains price");
        check(toStringResult.find("0") != string::npos, "toString contains id");
        check(toStringResult.find("2026-03-15 18:30:00") != string::npos, "toString contains date");
        
        delete t1;



        cout << "\n=== TEST 2: Setters Work Through Constructors ===" << endl;
        
        EventTicket* t2a = new EventTicket("Kopelija", "B-5", 30.0, parseDateTime("2026-04-01 18:00:00"), false);
        check(t2a->getEventName() == "Kopelija", "First object eventName set correctly");
        check(t2a->getSeatNumber() == "B-5", "First object seatNumber set correctly");
        check(t2a->getPrice() == 30.0, "First object price set correctly");
        check(t2a->getEventDate() == parseDateTime("2026-04-01 18:00:00"), "First object eventDate set correctly");
        check(t2a->getIsUsed() == false, "First object isUsed set correctly");
        
        EventTicket* t2b = new EventTicket("Turandot", "Z-99", 125.50, parseDateTime("2026-12-31 23:59:59"), true);
        check(t2b->getEventName() == "Turandot", "Second object eventName set to different value");
        check(t2b->getSeatNumber() == "Z-99", "Second object seatNumber set to different value");
        check(t2b->getPrice() == 125.50, "Second object price set to different value");
        check(t2b->getEventDate() == parseDateTime("2026-12-31 23:59:59"), "Second object eventDate set to different value");
        check(t2b->getIsUsed() == true, "Second object isUsed set to different value");
        
        EventTicket* t2c = new EventTicket("Carmen", "M-42", 99.99, parseDateTime("2026-06-15 14:30:00"));
        check(t2c->getEventName() == "Carmen", "Third object eventName set correctly");
        check(t2c->getSeatNumber() == "M-42", "Third object seatNumber set correctly");
        check(t2c->getPrice() == 99.99, "Third object price set correctly");
        check(t2c->getEventDate() == parseDateTime("2026-06-15 14:30:00"), "Third object eventDate set correctly");
        check(t2c->getIsUsed() == false, "Third object isUsed defaults to false");
        
        delete t2a;
        delete t2b;
        delete t2c;



        cout << "\n=== TEST 3: Validation Exceptions ===" << endl;
        
        testException(
            []() { EventTicket* t = new EventTicket("Test", "C-1", -10.0, parseDateTime("2026-05-01 10:00:00")); delete t; },
            "Price cannot be negative",
            "Negative price throws invalid_argument exception"
        );
        
        testException(
            []() { time_t invalidDate = parseDateTime("not-a-valid-date"); EventTicket* t = new EventTicket("Test", "C-3", 50.0, invalidDate); delete t; },
            "Invalid date format",
            "Invalid date format throws invalid_argument exception"
        );

        testException(
            []() { time_t emptyDate = parseDateTime(""); EventTicket* t = new EventTicket("Test", "C-4", 50.0, emptyDate); delete t; },
            "Invalid date format",
            "Empty date string throws invalid_argument exception"
        );




        cout << "\n=== TEST 4: Automatic ID Numbering ===" << endl;
        
        EventTicket* t4a = new EventTicket("Hamlet", "D-1", 25.0, parseDateTime("2026-06-01 10:00:00"));
        int id1 = t4a->getId();
        check(id1 >= 0, "First ID is 0 or greater");
        
        EventTicket* t4b = new EventTicket("Cinderella", "Y-17", 30.0, parseDateTime("2029-06-21 11:00:00"));
        int id2 = t4b->getId();
        check(id2 > id1, "Second ID is greater than first");
        
        EventTicket* t4c = new EventTicket("Giselle", "F-33", 35.0, parseDateTime("2030-06-09 12:30:00"));
        int id3 = t4c->getId();
        check(id3 > id2, "Third ID is greater than second");

        delete t4b;
        
        EventTicket* t4d = new EventTicket("Aida", "F-44", 40.0, parseDateTime("2027-01-04 18:00:00"));
        int id4 = t4d->getId();
        check(id4 > id3, "ID after deletion continues to increase");
        check(id4 != id2, "New object doesn't reuse deleted object's ID");
        
        delete t4a;
        delete t4c;
        delete t4d;




        cout << "\n=== TEST 5: Dynamic List and Object Count ===" << endl;
        
        check(EventTicket::getObjectCount() == 0, "Object count is 0 before creating list");
        
        vector<EventTicket*> ticketList;
        
        try {
            ticketList.push_back(new EventTicket("Carmen", "E-1", 45.0, parseDateTime("2026-07-10 17:00:00")));
            check(EventTicket::getObjectCount() == 1, "Object count is 1 after first object");
            
            ticketList.push_back(new EventTicket("Giselle", "E-2", 50.0, parseDateTime("2026-07-11 19:00:00")));
            check(EventTicket::getObjectCount() == 2, "Object count is 2 after second object");
            
            ticketList.push_back(new EventTicket("Onegin", "E-3", 20.0, parseDateTime("2025-08-12 18:30:00"), true));
            check(EventTicket::getObjectCount() == 3, "Object count is 3 after third object");
            
            ticketList.push_back(new EventTicket("Romeo and Juliet", "E-4", 60.0, parseDateTime("2022-07-19 19:00:00")));
            check(EventTicket::getObjectCount() == 4, "Object count is 4 after fourth object");
            
            ticketList.push_back(new EventTicket("The Nutcracker", "E-5", 68.0, parseDateTime("2026-12-25 15:00:00"), false));
            check(EventTicket::getObjectCount() == 5, "Object count is 5 after fifth object");
            
            check(ticketList.size() == 5, "List contains 5 objects");
            
            check(ticketList[0]->getEventName() == "Carmen", "Can access first list item");
            check(ticketList[2]->getIsUsed() == true, "Can access third list item properties");
            check(ticketList[4]->getPrice() == 68.0, "Can access fifth list item");
            
            delete ticketList[0];
            check(EventTicket::getObjectCount() == 4, "Object count is 4 after first delete");
            
            delete ticketList[1];
            check(EventTicket::getObjectCount() == 3, "Object count is 3 after second delete");
            
            delete ticketList[2];
            check(EventTicket::getObjectCount() == 2, "Object count is 2 after third delete");
            
            delete ticketList[3];
            check(EventTicket::getObjectCount() == 1, "Object count is 1 after fourth delete");
            
            delete ticketList[4];
            check(EventTicket::getObjectCount() == 0, "Object count is 0 after all deletes");
            
            ticketList.clear();
            check(ticketList.size() == 0, "List is empty after clear");

        } catch (exception& e) {
            cout << "Exception in TEST 5: " << e.what() << endl;
            for (size_t i = 0; i < ticketList.size(); i++) {
                if (ticketList[i] != nullptr) {
                    delete ticketList[i];
                }
            }
            ticketList.clear();
        }
        

        check(EventTicket::getObjectCount() == 0, "Final object count is 0 at end of test");
    } catch (exception& e) {
        cout << "Unexpected error occurred: " << e.what() << endl;
    } catch (...) {
        cout << "Unexpected error occured!" << endl;
    }

    cout << "\nFinal object count: " << EventTicket::getObjectCount() << endl;

    cout << "\nTEST REPORT" << endl;
    cout << "Tests passed: " << testsPassed << endl;
    cout << "Tests failed: " << testsFailed << endl;

    return 0;
}
