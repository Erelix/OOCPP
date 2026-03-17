#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

class NotInitializedException : public logic_error {
    private:
        string message;
    
    public:
        NotInitializedException(const string &className) : logic_error(string("Not initialized: class") + className){
        }
        virtual const char* what() const throw() {
            return "Hello";
        }
        
};
  
class Student {
    private:
        int id;
        string name, surname;
        int year;
        static int lastId;
        bool isInitialized = false;
        static int objectCount;
    public:
        Student(){
            ++objectCount;
        }
        Student(const string &name, const string &surname){
            ++objectCount;
            setID();
            init(name, surname, 1);
        }
        Student(const string &name, const string &surname, int year){
            ++objectCount;
            setID();
            init(name, surname, year);
        }
        Student(const Student &other){
            ++objectCount;
            setID(other.id);
            init(other.name, other.surname, other.year);
        }
        const Student& operator=(const Student &other){
            setID(other.id);
            init(other.name, other.surname, other.year);
            return other;
        }
        ~Student(){
            --objectCount;
            //cout << "Destructor was called" << endl;
        }

    private:
        void init(const string &name, const string &surname, int year){
            //cout << "Constructor was called;" << endl;
            ++objectCount;
            setID();
            setName(name);
            setSurname(surname);
            setYear(year);
            isInitialized = true;
        }
        void setName(const string &name){
            this->name = name;
        }
        void setSurname(const string &surname){
            this->surname = surname;
        }
        void setID(){
            id = lastId++;
        }
        void setID(int id){
            this->id = id;
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

        string getName() const {
            if (isInitialized)
                return name;
            else
                throw NotInitializedException("Student");
        }
        string getSurname() const{
            if (isInitialized)
                return surname;
            else
                throw NotInitializedException("Student");
        }
        int getYear() const{
            return year;
        }
        int getId() const{
            if (isInitialized)
                return id;
            else
                throw NotInitializedException("Student");
        }
        static int getObjectCount(){
            return objectCount;
        }

        string toString() const {
            if(isInitialized) {
                stringstream ss;
                ss << getId() << " " << getName() << " " << getSurname() << " " << getYear() << endl;
                return ss.str();
            } else {
                throw NotInitializedException("Student");
            }
        }
        friend ostream& operator<<(ostream& out, const Student& s);
        friend istream& operator>>(istream& in, Student& s);
};

int Student::lastId = 0;
int Student::objectCount = 0;

ostream& operator<<(ostream& out, const Student& s){
    if(s.isInitialized) {
        out << s.toString();
        return out;
    }
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

    Student temp;
    temp.setID(id);
    temp.init(name, surname, year);
    s = temp;
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
