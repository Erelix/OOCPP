#ifndef SIMPLECLASS_H_921223
#define SIMPLECLASS_H_921223

#include <stdexcept>

using std::logic_error;

//using namespace std;

#define string std::string

namespace MySpace {

class NotInitializedException : public std::logic_error {
    public:
        NotInitializedException(const string &className);
        
};
  
class Student {
    private:
        class Inner;
        Inner *impl;
    public:
        Student();
        Student(const string &name, const string &surname);
        Student(const string &name, const string &surname, int year);
        Student(const Student &other);
        const Student& operator=(const Student &other);
        ~Student();

        void setYear(int year);

        int getId();
        static int getObjectCount();
        string getName() const;
        string getSurname() const;
        int getYear() const;
        
        string toString() const;
        
        #undef string

        friend std::ostream& operator<<(std::ostream& out, const Student& s);
        friend std::istream& operator>>(std::istream& in, Student& s);
};
}


#endif