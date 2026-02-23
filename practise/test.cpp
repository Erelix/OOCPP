#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

class Student {
    private:

        int id;
        string name, surname;
        int year;
        static int lastId;
        bool isInitialized = false;
        static int objectCount;
    public:
        Student(string name, string surname){
            init(name, surname, 1);
        }
        Student(string name, string surname, int year){
            init(name, surname, year);
        }
        ~Student(){
            --objectCount;
            //cout << "Destructor was called" << endl;
        }

    private:
        void init(string name, string surname, int year){
            cout << "Constructor was called;" << endl;
            ++objectCount;
            id = lastId++;
            setName(name);
            setSurname(surname);
            setYear(year);
            isInitialized = true;
        }
        void setName(string name){
            this->name = name;
        }
        void setSurname(string surname){
            this->surname = surname;
        }

    public:
        void setYear(int year){
            if (year > 0){
                if (!isInitialized || year >= this->year){
                    this->year = year;
                } else {
                   throw invalid_argument("Exception in Student: year cannot decrease!");
                }
            } else {
                throw invalid_argument("Exception in Student: year must be positive!");
            }
        }

        string getName(){
            return name;
        }
        string getSurname(){
            return surname;
        }
        int getYear(){
            return year;
        }
        int getId(){
            return id;
        }
        static int getObjectCount(){
            return objectCount;
        }

        string toString(){
            stringstream ss;
            ss << getName() << " " << getSurname() << " " << getYear() << " " << getId() << endl;
            return ss.str();
        }
};
int Student::lastId = 0;
int Student::objectCount = 0;

int main(){

    try {
//        // Testas:
//        try {
//            Student s("Adrian", "Klimasevski", 3);
//            cout << "FAILURE" << endl;
//        } catch(exception &e){
//            //cout << e.what() << endl;
//            cout << "SUCESS" << endl;
//        }

        Student s0("Adrian", "Klimasevski", 3);
        Student *s1 = new Student("Adrian", "Klimasevski", 3);
        Student *s2 = new Student("Adrian", "Klimasevski", 3);

        cout << s0.toString() << endl;
        cout << s1->toString() << endl;
        cout << s2->toString() << endl;

        delete s2;
        delete s1;

        cout << Student::getObjectCount() << endl;

//        try {
//            s.setYear(2);
//        } catch (exception &e){
//            cout << s.toString() << endl;
//        }

//        cout << s.toString() << endl;

    } catch(...) {
        cout << "Unexpected error occured!" << endl;
    }

    cout << Student::getObjectCount() << endl;
    return 0;
}
