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




class Seat {
private:
    int row;           // Row nr of the seat
    int number;        // Seat nr
    char* type;        // Dynamically allocated string for seat type

public:
    // Default constructor
    Seat() : row(0), number(0), type(new char[1]) {
        strcpy(type, "");
    }

    // Parameterized constructor
    Seat(int row, int number, const char* type) : row(row), number(number) {
        this->type = new char[strlen(type) + 1];
        strcpy(this->type, type);
    }

    // Copy constructor
    Seat(const Seat& other) : row(other.row), number(other.number) {
        type = new char[strlen(other.type) + 1];
        strcpy(type, other.type);
    }

    // Assignment operator
    Seat& operator=(const Seat& other) {
        if (this != &other) {
            delete[] type;
            type = new char[strlen(other.type) + 1];
            strcpy(type, other.type);
            row = other.row;
            number = other.number;
        }
        return *this;
    }

    // Destructor
    ~Seat() {
        delete[] type;
    }

    // Getters
    int getRow() const {
        return row;
    }

    int getNumber() const {
        return number;
    }

    const char* getType() const {
        return type;
    }

    // Setters
    void setRow(int newRow) {
        row = newRow;
    }

    void setNumber(int newNumber) {
        number = newNumber;
    }

    void setType(const char* newType) {
        delete[] type;
        type = new char[strlen(newType) + 1];
        strcpy(type, newType);
    }

    //  indexing operator []
    const char* operator[](int index) const {
        switch (index) {
        case 0:
            static char rowNumBuffer[20];
            sprintf(rowNumBuffer, "%d", row);
            return rowNumBuffer;
        case 1:
            static char seatNumBuffer[20];
            sprintf(seatNumBuffer, "%d", number);
            return seatNumBuffer;
        case 2: return type;
        default: throw out_of_range("Invalid index");
        }
    }

    // Overloading + 
    Seat operator+(int value) {
        Seat newSeat = *this;
        newSeat.number += value;  // Adjust seat number
        return newSeat;
    }

    // Overloading - 
    Seat operator-(int value) {
        Seat newSeat = *this;
        newSeat.number -= value;  // Adjust seat number
        return newSeat;
    }

    // Overloading ++ (Prefix)
    Seat& operator++() {
        // Increment the seat number
        number++;
        return *this;
    }

    // Overloading ++ (Postfix)
    Seat operator++(int) {
        Seat temp = *this;
        ++(*this);
        return temp;
    }

    // Explicit cast to std::string
    explicit operator std::string() const {
        ostringstream oss;
        oss << "Seat Row: " << row << ", Number: " << number
            << ", Type: " << (type ? type : "Unknown");
        return oss.str();
    }

    // Overloading !
    bool operator!() const {
        return number == 0; // True if the seat is unassigned
    }

    // Overloading <
    bool operator<(const Seat& other) const {
        if (row == other.row) {
            return number < other.number; // Compare by seat number if rows are the same
        }
        return row < other.row; // Compare by row number
    }

    // Overloading == (equality) operator
    bool operator==(const Seat& other) const {
        return row == other.row &&
            number == other.number &&
            strcmp(type, other.type) == 0;
    }


    // Friend functions for input and output
    friend ostream& operator<<(ostream& os, const Seat& seat);
    friend istream& operator>>(istream& is, Seat& seat);
};

ostream& operator<<(ostream& os, const Seat& seat) {
    os << "Seat Row: " << seat.row << ", Number: " << seat.number << ", Type: " << seat.type;
    return os;
}

istream& operator>>(istream& is, Seat& seat) {
    cout << "Enter seat row: ";
    is >> seat.row;
    is.ignore(); // Ignore newline character

    cout << "Enter seat number: ";
    is >> seat.number;
    is.ignore(); // Ignore newline character

    cout << "Enter seat type: ";
    char buffer[256];
    is.getline(buffer, 256);
    seat.setType(buffer);

    return is;
}

