#include <iostream>
#include <sstream>
#include <stdexcept>

#include <cassert>
#include <vector>
#include <ctime>

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


// From: https://www.geeksforgeeks.org/cpp/date-and-time-parsing-in-cpp/
time_t parseDateTime(const char* datetimeString){
    struct tm tmStruct;
    strptime(datetimeString, DATETIME_FORMAT, &tmStruct);
    return mktime(&tmStruct);
}
string DateTime(time_t time){
    char buffer[90];
    struct tm* timeinfo = localtime(&time);
    strftime(buffer, sizeof(buffer), DATETIME_FORMAT, timeinfo);
    return buffer;
}

int testsPassed = 0;
int testsFailed = 0;

void check(bool condition, const string& testName) {
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

        //EventTicket *et1 = new EventTicket("La Strada", "F-23", 37.5, parseDateTime("2026-01-15 12:00:00"));
        //EventTicket *et2 = new EventTicket("Don Juan", "C-15", 27.0, parseDateTime("2026-05-20 18:30:00"), true);

        //cout << et1->toString() << endl;
        //cout << et2->toString() << endl;
        EventTicket* et1 = new EventTicket("Kopelija", "A-10", 50.0, parseDateTime("2026-03-15 12:00:00"));

        check(et1->getEventName() == "Kopelija", "eventName (Setter, Getter)");
        check(et1->getSeatNumber() == "A-10", "seatNumber (Setter, Getter)");
        check(et1->getPrice() == 50.0, "price (Setter, Getter)");
        check(et1->getEventDate() == parseDateTime("2026-03-15 12:00:00"), "eventDate (Setter, Getter)");
        check(et1->getIsUsed() == false, "isUsed default false (Setter, Getter)");
        check(et1->getId() == 0, "id (Getter)");
        check(EventTicket::getObjectCount() == 1, "objectCount increased");

//string txt = t1->toString();
//
//check(txt.find("Swan Lake") != string::npos, "toString contains event name");
//check(txt.find("A-10") != string::npos, "toString contains seat");
//check(txt.find("50") != string::npos, "toString contains price");
//check(txt.find(to_string(t1->getId())) != string::npos, "toString contains id");

        delete et1;
        check(EventTicket::getObjectCount() == 0, "Object count returns to 0 after delete");

        // cout << "Obj. count: " << EventTicket::getObjectCount() << " (Before deconstructor is called)" << endl;

        // delete et1;
        // delete et2;

        } catch (...){
            cout << "Unexpected error occured!" << endl;
        }

        cout << "Obj. count: " << EventTicket::getObjectCount() << endl;

        cout << "\nTEST REPORT" << endl;
        cout << "Tests passed: " << testsPassed << endl;
        cout << "Tests failed: " << testsFailed << endl;

    return 0;
}
