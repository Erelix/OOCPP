#include <iostream>
#include <sstream>
#include <stdexcept>
#include <exception>

#include "simpleclass.h"

using namespace std;

NotInitializedException::NotInitializedException(const string &className) : logic_error(string("Not initialized: class") + className){
}
  

class Student::Inner{
    private:
        int id;
        string name, surname;
        int year;
        static int lastId;
        bool isInitialized = false;
        static int objectCount;
    public:
        Inner();
        Inner(const string &name, const string &surname);
        Inner(const string &name, const string &surname, int year);
        Inner(const Inner &other);
        const Inner& operator=(const Inner &other);
        ~Inner();

    private:
        void init(const string &name, const string &surname, int year);
        void setID();
        void setID(int id);
        void setName(const string &name);
        void setSurname(const string &surname);

    public:
        void setYear(int year);
        string getName() const;
        string getSurname() const;
        int getYear() const;
        int getId() const;
        static int getObjectCount();

        string toString() const;
};

int Student::Inner::lastId = 0;
int Student::Inner::objectCount = 0;

Student::Inner::Inner(){
    ++objectCount;
}
Student::Inner::Inner(const string &name, const string &surname){
    ++objectCount;
    setID();
    init(name, surname, 1);
}
Student::Inner::Inner(const string &name, const string &surname, int year){
    ++objectCount;
    setID();
    init(name, surname, year);
}
Student::Inner::Inner(const Student::Inner &other){
    ++objectCount;
    setID(other.id);
    init(other.name, other.surname, other.year);
}
const Student::Inner &Student::Inner::operator=(const Student::Inner &other){
    setID(other.id);
    init(other.name, other.surname, other.year);
    return *this;
}
Student::Inner::~Inner(){
    --objectCount;
    // cout << "Destructor was called" << endl;
}
void Student::Inner::init(const string &name, const string &surname, int year){
    // cout << "Constructor was called;" << endl;
    ++objectCount;
    setID();
    setName(name);
    setSurname(surname);
    setYear(year);
    isInitialized = true;
}
void Student::Inner::setName(const string &name){
    this->name = name;
}
void Student::Inner::setSurname(const string &surname){
    this->surname = surname;
}
void Student::Inner::setID(){
    id = lastId++;
}
void Student::Inner::setID(int id){
    this->id = id;
}

void Student::Inner::setYear(int year){
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

string Student::Inner::getName() const{
    if (isInitialized)
        return name;
    else
        throw NotInitializedException("Student");
}
string Student::Inner::getSurname() const{
    if (isInitialized)
        return surname;
    else
        throw NotInitializedException("Student");
}
int Student::Inner::getYear() const{
    return year;
}
int Student::Inner::getId() const{
    if (isInitialized)
        return id;
    else
        throw NotInitializedException("Student");
}
int Student::Inner::getObjectCount(){
    return objectCount;
}

string Student::Inner::toString() const{
    if (isInitialized){
        stringstream ss;
        ss << getId() << " " << getName() << " " << getSurname() << " " << getYear() << endl;
        return ss.str();
    } else {
        throw NotInitializedException("Student");
    }
}

// Student implementation delegates it
// to the Student::Inner class

Student::Student(){
    impl = new Student::Inner();
}
Student::Student(const string &name, const string &surname){
    impl = new Student::Inner(name, surname);
}
Student::Student(const string &name, const string &surname, int year){
    impl = new Student::Inner(name, surname, year);
}
Student::Student(const Student &other){
    impl = new Student::Inner(*(other.impl));
}
const Student &Student::operator=(const Student &other){
    if (&other != this){
        delete impl;
        impl = new Student::Inner(*(other.impl));
    }
    return other;
}
Student::~Student(){
    delete impl;
}
void Student::setYear(int year){
    impl->setYear(year);
}
int Student::getId(){
    return impl->getId();
}
int Student::getObjectCount(){
    return Student::Inner::getObjectCount();
}
string Student::getName() const{
    return impl->getName();
}
string Student::getSurname() const{
    return impl->getSurname();
}
int Student::getYear() const{
    return impl->getYear();
}
string Student::toString() const{
    return impl->toString();
}

ostream& operator<<(ostream& out, const Student& s){
    out << s.toString();
    return out;
}
istream& operator>>(istream& in, Student& s){
    string name, surname;
    int id, year;
    cout << "Enter id: ";
        in >> id;
    cout << "Enter name: ";
        in >> name;
    cout << "Enter surname: ";
        in >> surname;
    cout << "Enter year: ";
        in >> year;

    cout << in.good() << in.bad() << in.fail() << in.eof() << endl;

    if(in.fail()){
        in.clear();
        in.ignore(256, '\n');
        throw ios_base::failure("Student input failed!");
    }

    s = Student(name, surname, year);
    return in;
}




int main(){

    try {
        const Student s0("Adrian", "Klimasevski", 3);
        cout << s0 << endl;
        
        Student s1;
        cout << s1 << endl; 

        stringstream ss;
        ss << s0;
        ss >> s1;

        cout << s0 << endl;
        cout << s1 << endl;

        cout << Student::getObjectCount() << endl;

    } catch (exception &e){
        cout << e.what() << endl;
    } catch(...) {
        cout << "Unexpected error occured!" << endl;
    }

    cout << Student::getObjectCount() << endl;
    return 0;
}
