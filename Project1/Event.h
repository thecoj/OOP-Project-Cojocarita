#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>  
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std; 




class Event {
private:
    const int id;        // ID for event
    char* name;          // event name
    char* date;          // event date
    char* time;          // event time
    static int ID_COUNTER; // Static counter for generating unique IDs

    

    // Private default constructor
    Event() : id(++ID_COUNTER), name(nullptr), date(nullptr), time(nullptr) {}

public:

  

    // Parameterized constructor
    Event(const char* name, const char* date, const char* time) : id(++ID_COUNTER) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->date = new char[strlen(date) + 1];
        strcpy(this->date, date);
        this->time = new char[strlen(time) + 1];
        strcpy(this->time, time);
    }

    // Copy constructor
    Event(const Event& other) : id(other.id) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        date = new char[strlen(other.date) + 1];
        strcpy(date, other.date);
        time = new char[strlen(other.time) + 1];
        strcpy(time, other.time);
    }

    // Assignment operator
    Event& operator=(const Event& other) {
        if (this != &other) {
            delete[] name;
            delete[] date;
            delete[] time;
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
            date = new char[strlen(other.date) + 1];
            strcpy(date, other.date);
            time = new char[strlen(other.time) + 1];
            strcpy(time, other.time);
        }
        return *this;
    }

    // Destructor
    ~Event() {
        delete[] name;
        delete[] date;
        delete[] time;
    }

    // Getters
    const char* getName() const {
        return name;
    }

    const char* getDate() const {
        return date;
    }

    const char* getTime() const {
        return time;
    }

    int getId() const {
        return id;
    }

    // Setters
    void setName(const char* newName) {
        delete[] name;
        name = new char[strlen(newName) + 1];
        strcpy(name, newName);
    }

    void setDate(const char* newDate) {
        delete[] date;
        date = new char[strlen(newDate) + 1];
        strcpy(date, newDate);
    }

    void setTime(const char* newTime) {
        delete[] time;
        time = new char[strlen(newTime) + 1];
        strcpy(time, newTime);
    }

    //  indexing operator []
    const char* operator[](int index) const {
        switch (index) {
        case 0: return name;
        case 1: return date;
        case 2: return time;
        default: throw out_of_range("Invalid index");
        }
    }

    // Overloading + 
    Event operator+(int days) {
        std::tm tm = {};
        std::stringstream ss(date);
        ss >> std::get_time(&tm, "%Y-%m-%d");
        tm.tm_mday += days;
        mktime(&tm);

        std::stringstream result;
        result << std::put_time(&tm, "%Y-%m-%d");
        return Event(name, result.str().c_str(), time);
    }

    // Overloading - 
    Event operator-(int days) {
        std::tm tm = {};
        std::stringstream ss(date);
        ss >> std::get_time(&tm, "%Y-%m-%d");
        tm.tm_mday -= days;
        mktime(&tm);

        std::stringstream result;
        result << std::put_time(&tm, "%Y-%m-%d");
        return Event(name, result.str().c_str(), time);
    }



    // Overloading ++ (Prefix)
    Event& operator++() {
        std::tm tm = {};
        std::stringstream ss(date);
        ss >> std::get_time(&tm, "%Y-%m-%d");
        tm.tm_mday += 1;
        mktime(&tm);

        char newDate[11]; // Buffer to hold the new date string
        strftime(newDate, sizeof(newDate), "%Y-%m-%d", &tm);

        delete[] date; // Free the old date
        date = new char[11];
        strcpy(date, newDate); // Update the date

        return *this;
    }

    // Overloading ++ (Postfix)
    Event operator++(int) {
        Event temp(*this); // Create a copy of the current object

        // Increment date logic
        std::tm tm = {};
        std::stringstream ss(this->date);
        ss >> std::get_time(&tm, "%Y-%m-%d");
        tm.tm_mday += 1;
        mktime(&tm);

        char newDate[11];
        strftime(newDate, sizeof(newDate), "%Y-%m-%d", &tm);

        delete[] this->date;
        this->date = new char[11];
        strcpy(this->date, newDate);

        return temp; // Return the original state
    }

    explicit operator std::string() const {
        std::string result = "Event Name: ";
        result += name;
        result += ", Date: ";
        result += date;
        result += ", Time: ";
        result += time;
        return result;
    }

    // Overloading !
    bool operator!() const {
        return strcmp(date, "") == 0; // True if date is empty
    }


    // Overloading < (less than) operator
    bool operator<(const Event& other) const {
        // Compare based on dates
        return strcmp(date, other.date) < 0;
    }

    // Overloading == (equality) operator
    bool operator==(const Event& other) const {
        return strcmp(name, other.name) == 0 &&
            strcmp(date, other.date) == 0 &&
            strcmp(time, other.time) == 0;
    }

    // friend fct for input and output
    friend ostream& operator<<(ostream& console, const Event& e);
    friend istream& operator>>(istream& is, Event& event);


};

int Event::ID_COUNTER = 0;

// overloaded << operator
ostream& operator<<(ostream& console, const Event& e) {
    console << "Event ID: " << e.id << "\nName: " << e.name << "\nDate: " << e.date << "\nTime: " << e.time;
    return console;
}


// overloaded >> operator 


istream& operator>>(istream& is, Event& event) {
    char buffer[256]; // Buffer for input

    cout << "Enter event name: ";
    is.getline(buffer, 256);
    delete[] event.name;
    event.name = new char[strlen(buffer) + 1];
    strcpy(event.name, buffer);

    cout << "Enter event date: ";
    is.getline(buffer, 256);
    delete[] event.date;
    event.date = new char[strlen(buffer) + 1];
    strcpy(event.date, buffer);

    cout << "Enter event time: ";
    is.getline(buffer, 256);
    delete[] event.time;
    event.time = new char[strlen(buffer) + 1];
    strcpy(event.time, buffer);

    return is;
}



