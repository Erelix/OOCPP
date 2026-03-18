#ifndef SIMPLECLASS_H_921223
#define SIMPLECLASS_H_921223

#include <stdexcept>

//using std::logic_error;

using namespace std;


class NotInitializedException : public logic_error {
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

        friend ostream& operator<<(std::ostream& out, const Student& s);
        friend istream& operator>>(std::istream& in, Student& s);
};

#endif