#include <iostream>
#include <sstream>
#include <stdexcept>

#include <cassert>
#include <vector>
#include <ctime>
#include <cstring>

using namespace std;

time_t parseDateTime(const char* datetimeString);
string DateTime(time_t time);
const char* DATETIME_FORMAT = "%Y-%m-%d %H:%M:%S";

class EventTicket {
    private:
        int id;
        static int objectCount;

        string eventName;
        string seatNumber;
        double price;
        bool isUsed;
        time_t eventDate;
        static int lastId;

    public:
        EventTicket(string eventName, string seatNumber, double price, time_t eventDate){
            init(eventName, seatNumber, price, eventDate, false);
        }
        EventTicket(string eventName, string seatNumber, double price, time_t eventDate, bool isUsed){
            init(eventName, seatNumber, price, eventDate, isUsed);
        }
        ~EventTicket(){
            --objectCount;
        }

    private:
        void init(string eventName, string seatNumber, double price, time_t eventDate, bool isUsed){
            id = lastId++;
            setEventName(eventName);
            setSeatNumber(seatNumber);
            setPrice(price);
            setEventDate(eventDate);
            setIsUsed(isUsed);
            ++objectCount;
        }
        void setEventName(string eventName){
            this->eventName = eventName;
        }
        void setSeatNumber(string seatNumber){
            this->seatNumber = seatNumber;
        }
        void setPrice(double price){
            if (price >= 0){
                this->price = price;
            } else {
                 throw invalid_argument("Exception in EventTicket: price cannot be negative!");
            }

        }
        void setEventDate(time_t eventDate){
            this->eventDate = eventDate;
        }

        void setIsUsed(bool isUsed){
            this->isUsed = isUsed;
        }

    public:
        int getId(){
            return id;
        }
        string getEventName(){
            return eventName;
        }
        string getSeatNumber(){
            return seatNumber;
        }
        double getPrice(){
            return price;
        }
        bool getIsUsed(){
            return isUsed;
        }
        time_t getEventDate(){
            return eventDate;
        }

        static int getObjectCount(){
            return objectCount;
        }

        string toString(){
            stringstream ss;
            ss << getEventName() << " " << getSeatNumber() << ", price: " << getPrice() << "eur " << DateTime(getEventDate())  << " id: " << getId() << endl;
            return ss.str();
        }
};

int EventTicket::lastId = 0;
int EventTicket::objectCount = 0;


// From: https://www.geeksforgeeks.org/cpp/date-and-time-parsing-in-cpp/ with added validation
time_t parseDateTime(const char* datetimeString){
    if (datetimeString == nullptr || strlen(datetimeString) == 0) {
        throw invalid_argument("Exception in parseDateTime: date string cannot be null or empty!");
    }
    
    struct tm tmStruct = {};
    char* result = strptime(datetimeString, DATETIME_FORMAT, &tmStruct);
    
    if (result == nullptr || *result != '\0') {
        throw invalid_argument("Exception in parseDateTime: invalid date format! Expected: YYYY-MM-DD HH:MM:SS");
    }
    
    if (tmStruct.tm_year < 0 || tmStruct.tm_mon < 0 || tmStruct.tm_mon > 11 ||
        tmStruct.tm_mday < 1 || tmStruct.tm_mday > 31 ||
        tmStruct.tm_hour < 0 || tmStruct.tm_hour > 23 ||
        tmStruct.tm_min < 0 || tmStruct.tm_min > 59 ||
        tmStruct.tm_sec < 0 || tmStruct.tm_sec > 59) {
        throw invalid_argument("Exception in parseDateTime: date values out of valid range!");
    }
    
    time_t resultTime = mktime(&tmStruct);
    if (resultTime == -1) {
        throw invalid_argument("Exception in parseDateTime: failed to convert to time_t");
    }
    
    return resultTime;
}

string DateTime(time_t time){
    char buffer[90];
    struct tm* timeinfo = localtime(&time);
    strftime(buffer, sizeof(buffer), DATETIME_FORMAT, timeinfo);
    return buffer;
}

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

int main (){

    try {
        cout << "=== TEST SUITE 1: Constructor(4 parameters) & Getters ===" << endl;
        EventTicket* et1 = new EventTicket("Kopelija", "B-11", 55.0, parseDateTime("2026-03-15 12:00:00"));
        check(et1->getEventName() == "Kopelija", "getEventName returns correct value");
        check(et1->getSeatNumber() == "B-11", "getSeatNumber returns correct value");
        check(et1->getPrice() == 55.0, "getPrice returns correct value");
        check(et1->getEventDate() == parseDateTime("2026-03-15 12:00:00"), "getEventDate returns correct value");
        check(et1->getIsUsed() == false, "getIsUsed default false");
        check(et1->getId() == 0, "getId returns 0 for first object");
        check(EventTicket::getObjectCount() == 1, "getObjectCount returns 1");

        cout << "\n=== TEST SUITE 2: toString Method ===" << endl;
        string txt = et1->toString();
        check(txt.find("Kopelija") != string::npos, "toString contains event name");
        check(txt.find("B-11") != string::npos, "toString contains seat");
        check(txt.find("55") != string::npos, "toString contains price");
        check(txt.find("id: 0") != string::npos, "toString contains id");

        cout << "\n=== TEST SUITE 3: Second Constructor(5 parameters) ===" << endl;
        EventTicket* et2 = new EventTicket("Don Juan", "C-15", 27.0, parseDateTime("2026-05-20 18:30:00"), true);
        check(et2->getEventName() == "Don Juan", "second object eventName");
        check(et2->getSeatNumber() == "C-15", "second object seatNumber");
        check(et2->getPrice() == 27.0, "second object price");
        check(et2->getIsUsed() == true, "second object isUsed true");
        check(et2->getId() == 1, "second object id is 1");
        check(EventTicket::getObjectCount() == 2, "objectCount is 2");

        cout << "\n=== TEST SUITE 4: Multiple Objects & Setter Variations ===" << endl;
        EventTicket* et3 = new EventTicket("Paquita", "D-5", 100.0, parseDateTime("2026-06-10 19:00:00"));
        check(et3->getEventName() == "Paquita", "third object eventName");
        check(et3->getSeatNumber() == "D-5", "third object seatNumber");
        check(et3->getPrice() == 100.0, "third object price");
        check(et3->getId() == 2, "third object id is 2");
        check(EventTicket::getObjectCount() == 3, "objectCount is 3");

        EventTicket* et4 = new EventTicket("La Strada", "B-20", 75.5, parseDateTime("2026-12-31 20:00:00"), false);
        check(et4->getEventName() == "La Strada", "fourth object eventName");
        check(et4->getSeatNumber() == "B-20", "fourth object seatNumber");
        check(et4->getPrice() == 75.5, "fourth object price");
        check(et4->getEventDate() == parseDateTime("2026-12-31 20:00:00"), "fourth object eventDate");
        check(et4->getIsUsed() == false, "fourth object isUsed");
        check(et4->getId() == 3, "fourth object id is 3");
        check(EventTicket::getObjectCount() == 4, "objectCount is 4");

        cout << "\n=== TEST SUITE 5: Destructor & Object Count ===" << endl;
        delete et1;
        check(EventTicket::getObjectCount() == 3, "objectCount decreased to 3 after delete");
        delete et2;
        check(EventTicket::getObjectCount() == 2, "objectCount decreased to 2 after delete");
        delete et3;
        check(EventTicket::getObjectCount() == 1, "objectCount decreased to 1 after delete");
        delete et4;
        check(EventTicket::getObjectCount() == 0, "objectCount returns 0 after all deletes");

        cout << "\n=== TEST SUITE 6: Exception Handling ===" << endl;
        bool exceptionCaught = false;
        try {
            EventTicket* et5 = new EventTicket("Test", "E-1", -10.0, parseDateTime("2026-07-01 10:00:00"));
            delete et5;
        } catch (invalid_argument& e) {
            exceptionCaught = true;
            check(string(e.what()).find("price cannot be negative") != string::npos, "exception message correct");
        }
        check(exceptionCaught, "negative price throws exception");

        cout << "\n=== TEST SUITE 7: Date Format Validation ===" << endl;
        exceptionCaught = false;
        try {
            time_t invalidDate = parseDateTime("2026-13-01 10:00:00");
            EventTicket* et6 = new EventTicket("Test", "G-1", 50.0, invalidDate);
            delete et6;
        } catch (invalid_argument& e) {
            exceptionCaught = true;
            check(string(e.what()).find("parseDateTime") != string::npos, "invalid month throws exception");
        }
        check(exceptionCaught, "invalid month detected");

        exceptionCaught = false;
        try {
            time_t invalidDate = parseDateTime("not-a-date");
            EventTicket* et7 = new EventTicket("Test", "H-1", 50.0, invalidDate);
            delete et7;
        } catch (invalid_argument& e) {
            exceptionCaught = true;
            check(string(e.what()).find("invalid date format") != string::npos, "wrong format exception message");
        }
        check(exceptionCaught, "invalid format detected");

        exceptionCaught = false;
        try {
            time_t invalidDate = parseDateTime("2026-15-45 99:99:99");
            EventTicket* et8 = new EventTicket("Test", "I-1", 50.0, invalidDate);
            delete et8;
        } catch (invalid_argument& e) {
            exceptionCaught = true;
        }
        check(exceptionCaught, "invalid date values detected");

        exceptionCaught = false;
        try {
            time_t invalidDate = parseDateTime("");
            EventTicket* et9 = new EventTicket("Test", "J-1", 50.0, invalidDate);
            delete et9;
        } catch (invalid_argument& e) {
            exceptionCaught = true;
            check(string(e.what()).find("null or empty") != string::npos, "empty string exception message");
        }
        check(exceptionCaught, "empty date string detected");

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
