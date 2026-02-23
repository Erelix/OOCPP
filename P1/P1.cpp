#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

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
        EventTicket(string eventName, string seatNumber, double price, time_t eventDate, bool isUsed){
            init(eventName, seatNumber, price, eventDate, isUsed);
        }
        ~EventTicket(){
            --objectCount;
        }

    private:
        void init(string eventName, string seatNumber, double price, time_t eventDate, bool isUsed){
            id = lastId++;
            setEventDate(eventDate);
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
            ss << getEventName() << " seat: " << getSeatNumber() << ", price: " << getPrice() << "eur " << getEventDate() << endl;
            return ss.str();
        }
};

int EventTicket::lastId = 0;
int EventTicket::objectCount = 0;

int main (){
    EventTicket *et1 = new EventTicket("Kopelija", "F-23", 37.5, time(0), false);
    EventTicket *et2 = new EventTicket("Don Juan", "C-15", 27.0, time(0), true);

    cout << et1->toString() << endl;
    cout << et2->toString() << endl;
    cout << "Obj. count: " << EventTicket::getObjectCount() << endl;

    delete et1;
    delete et2;

    cout << "Obj. count: " << EventTicket::getObjectCount() << endl;
    return 0;
}
