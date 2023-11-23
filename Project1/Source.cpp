#include <iostream>
#include <string>
#include <cstring>  
using namespace std;

class Event {
    const int id;     // identifier 
    char* name;       // Dynamically allocated string
    char* date;       
    char* time;       
    static int NO_EVENTS;        // static variable for number of events
    static int ID_COUNTER;       // static counter for unique ids for events

   
    Event() : id(0), name(nullptr), date(nullptr), time(nullptr) {}

public:
    //  constructor
    Event(const char* name, const char* date, const char* time) : id(++ID_COUNTER) {
        this->name = new char[strlen(name) + 1];
        strcpy_s(this->name, strlen(name) + 1, name);

        this->date = new char[strlen(date) + 1];
        strcpy_s(this->date, strlen(date) + 1, date);

        this->time = new char[strlen(time) + 1];
        strcpy_s(this->time, strlen(time) + 1, time);

        NO_EVENTS += 1;
    }

    // destructor
    ~Event() {
        cout << endl << "Event Destructor";
        delete[] name;
        delete[] date;
        delete[] time;
        NO_EVENTS -= 1;
    }

    // copy constructor
    Event(const Event& e) : id(e.id) {
        cout << endl << "Event Copy Constructor";
        this->setName(string(e.name));
        this->setDate(string(e.date));
        this->setTime(string(e.time));
        NO_EVENTS += 1;
    }


    // = operator
    Event& operator=(const Event& source) {
        cout << endl << "Event Assignment Operator";
        if (this != &source) {
            this->setName(string(source.name));
            this->setDate(string(source.date));
            this->setTime(string(source.time));
        }
        return *this;
    }



    // set w/ dynamic memory 
    void setName(string name) {
        delete[] this->name;
        this->name = new char[name.size() + 1];
        strcpy_s(this->name, name.size() + 1, name.c_str());
    }


    void setDate(string date) {
        delete[] this->date;
        this->date = new char[date.size() + 1];
        strcpy_s(this->date, date.size() + 1, date.c_str());
    }

    void setTime(string time) {
        delete[] this->time;
        this->time = new char[time.size() + 1];
        strcpy_s(this->time, time.size() + 1, time.c_str());
    }



    // getters
    string getName() const { return string(this->name); }
    string getDate() const { return string(this->date); }
    string getTime() const { return string(this->time); }

    // friend fct for input and output
    friend ostream& operator<<(ostream& console, const Event& e);
    friend istream& operator>>(istream& console, Event& e);

    
};
int Event::NO_EVENTS = 0;
int Event::ID_COUNTER = 0;



// overloaded << operator
ostream& operator<<(ostream& console, const Event& e) {
    console << "Event ID: " << e.id << "\nName: " << e.name << "\nDate: " << e.date << "\nTime: " << e.time;
    return console;
}


// overloaded >> operator 
istream& operator>>(istream& console, Event& e) {
    
    return console;
}
