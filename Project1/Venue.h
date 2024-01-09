#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>  
#include <vector>
#include <sstream>
#include <iomanip>
#include "Seat.h"
using namespace std;





class Venue {
private:
    string name;          // venue name
    Seat* seats;          // pointer to vector Seats
    int rows;             // Nr of rows
    int seatsPerRow;      // Nr of seats per row
    int maxCapacity;      // Max capacity of venue

    // fct to calculate index in the array
    int calculateIndex(int row, int seatNumber) const {
        return (row - 1) * seatsPerRow + (seatNumber - 1);
    }

public:
    // constructor
    Venue() : name(""), seats(nullptr), rows(0), seatsPerRow(0), maxCapacity(0) {}

    // constructor
    Venue(string name, int rows, int seatsPerRow, int maxCapacity)
        : name(name), rows(rows), seatsPerRow(seatsPerRow), maxCapacity(maxCapacity) {
        seats = new Seat[rows * seatsPerRow];
        // init seats
        for (int i = 0; i < rows * seatsPerRow; ++i) {
            seats[i] = Seat(); // default seat init
        }
    }

    // copy constructor
    Venue(const Venue& other)
        : name(other.name), rows(other.rows), seatsPerRow(other.seatsPerRow), maxCapacity(other.maxCapacity) {
        seats = new Seat[rows * seatsPerRow];
        for (int i = 0; i < rows * seatsPerRow; ++i) {
            seats[i] = other.seats[i];
        }
    }

    // assignment operator
    Venue& operator=(const Venue& other) {
        if (this != &other) {
            delete[] seats;  // Free existing seats

            name = other.name;
            rows = other.rows;
            seatsPerRow = other.seatsPerRow;
            maxCapacity = other.maxCapacity;

            seats = new Seat[rows * seatsPerRow];
            for (int i = 0; i < rows * seatsPerRow; ++i) {
                seats[i] = other.seats[i];
            }
        }
        return *this;
    }

    // destructor
    ~Venue() {
        delete[] seats;
    }

    // Getters
    string getName() const {
        return name;
    }

    int getRows() const {
        return rows;
    }

    int getSeatsPerRow() const {
        return seatsPerRow;
    }

    int getMaxCapacity() const {
        return maxCapacity;
    }

    Seat getSeat(int row, int seatNumber) const {
        int index = calculateIndex(row, seatNumber);
        if (index >= 0 && index < rows * seatsPerRow) {
            return seats[index];
        }
        else {
            throw out_of_range("Index out of range");
        }
    }

    // Setters
    void setName(const string& newName) {
        name = newName;
    }

    void setRows(int newRows) {
        rows = newRows;
        resizeSeats();
    }

    void setSeatsPerRow(int newSeatsPerRow) {
        seatsPerRow = newSeatsPerRow;
        resizeSeats();
    }

    void setMaxCapacity(int newMaxCapacity) {
        maxCapacity = newMaxCapacity;
    }

    void setSeat(int row, int seatNumber, const Seat& seat) {
        int index = calculateIndex(row, seatNumber);
        if (index >= 0 && index < rows * seatsPerRow) {
            seats[index] = seat;
        }
        else {
            throw out_of_range("Index out of range");
        }
    }

    //  indexing operator []
    Seat& operator[](int index) {
        if (index >= 0 && index < rows * seatsPerRow) {
            return seats[index];
        }
        else {
            throw out_of_range("Index out of range");
        }
    }

    const Seat& operator[](int index) const {
        if (index >= 0 && index < rows * seatsPerRow) {
            return seats[index];
        }
        else {
            throw out_of_range("Index out of range");
        }
    }


    // Helper method to resize the seats array when rows or seatsPerRow change
    void resizeSeats() {
        delete[] seats;
        seats = new Seat[rows * seatsPerRow];
        for (int i = 0; i < rows * seatsPerRow; ++i) {
            seats[i] = Seat(); // Reinitialize seats
        }
    }

    // Overloading + 
    Venue operator+(int additionalRows) {
        Venue newVenue = *this;
        newVenue.rows += additionalRows;
        newVenue.maxCapacity = newVenue.rows * newVenue.seatsPerRow;
        delete[] newVenue.seats;
        newVenue.seats = new Seat[newVenue.rows * newVenue.seatsPerRow];
        // Initialize new seats
        for (int i = 0; i < newVenue.rows * newVenue.seatsPerRow; ++i) {
            newVenue.seats[i] = Seat(); // Default initialization
        }
        return newVenue;
    }

    // Overloading - 
    Venue operator-(int removedRows) {
        Venue newVenue = *this;
        newVenue.rows = max(0, newVenue.rows - removedRows); // Ensure rows don't go below 0
        newVenue.maxCapacity = newVenue.rows * newVenue.seatsPerRow;
        delete[] newVenue.seats;
        newVenue.seats = new Seat[newVenue.rows * newVenue.seatsPerRow];
        // Initialize new seats
        for (int i = 0; i < newVenue.rows * newVenue.seatsPerRow; ++i) {
            newVenue.seats[i] = Seat(); // Default initialization
        }
        return newVenue;
    }

    // Explicit cast to std::string
    explicit operator std::string() const {
        ostringstream oss;
        oss << "Venue Name: " << name
            << ", Rows: " << rows
            << ", Seats Per Row: " << seatsPerRow
            << ", Max Capacity: " << maxCapacity;
        return oss.str();
    }

    // Overloading !
    bool operator!() const {
        return rows == 0 || seatsPerRow == 0; // True if the venue has no seats
    }


    // overload << >>
    friend ostream& operator<<(ostream& os, const Venue& venue);

    friend istream& operator>>(istream& is, Venue& venue);

};

// overloaded << operator
ostream& operator<<(ostream& os, const Venue& venue) {
    os << "Venue Name: " << venue.name << "\nMax Capacity: " << venue.maxCapacity;
    return os;
}


istream& operator>>(istream& is, Venue& venue) {
    cout << "Enter venue name: ";
    string buffer;
    getline(is, buffer);
    venue.name = buffer;

    cout << "Enter number of rows: ";
    is >> venue.rows;

    cout << "Enter number of seats per row: ";
    is >> venue.seatsPerRow;

    // Clear any existing seats and allocate new space
    delete[] venue.seats;
    venue.seats = new Seat[venue.rows * venue.seatsPerRow];

    is.ignore(); // Ignore newline character after reading numbers

    for (int r = 0; r < venue.rows; ++r) {
        for (int s = 0; s < venue.seatsPerRow; ++s) {
            int index = r * venue.seatsPerRow + s;
            Seat seat;

            cout << "Seat " << index + 1 << " (Row " << r + 1 << ", Seat " << s + 1 << "): " << endl;
            is >> seat; // Assuming Seat class has appropriate >> operator overloaded

            venue.seats[index] = seat;
        }
    }

    return is;
}