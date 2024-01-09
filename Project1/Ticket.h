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




class Ticket {
private:
    static int ID_COUNTER;   // counter unique ticket IDs
    const int ticketID;      // Unique ID for each ticket
    char* category;          // ticket category
    int seatNumber;          // Seat number 
    int price;               // Price of ticket

public:
    // Default constructor
    Ticket() : ticketID(++ID_COUNTER), category(nullptr), seatNumber(0), price(0) {}

    // Parameterized constructor
    Ticket(const char* category, int seatNumber, int price)
        : ticketID(++ID_COUNTER), seatNumber(seatNumber), price(price) {
        this->category = new char[strlen(category) + 1];
        strcpy(this->category, category);
    }

    // Copy constructor
    Ticket(const Ticket& other) : ticketID(other.ticketID), seatNumber(other.seatNumber), price(other.price) {
        category = new char[strlen(other.category) + 1];
        strcpy(category, other.category);
    }

    // Assignment operator
    Ticket& operator=(const Ticket& other) {
        if (this != &other) {
            delete[] category;
            category = new char[strlen(other.category) + 1];
            strcpy(category, other.category);
            seatNumber = other.seatNumber;
            price = other.price;
        }
        return *this;
    }

    // Destructor
    ~Ticket() {
        delete[] category;
    }

    // Getters
    int getTicketID() const {
        return ticketID;
    }

    const char* getCategory() const {
        return category;
    }

    int getSeatNumber() const {
        return seatNumber;
    }

    int getPrice() const {
        return price;
    }

    // Setters
    void setCategory(const char* newCategory) {
        delete[] category;
        category = new char[strlen(newCategory) + 1];
        strcpy(category, newCategory);
    }

    void setSeatNumber(int newSeatNumber) {
        seatNumber = newSeatNumber;
    }

    void setPrice(int newPrice) {
        price = newPrice;
    }

    // Overloading + and - 
    Ticket operator+(int value) {
        Ticket newTicket = *this;
        newTicket.price += value;
        return newTicket;
    }

    Ticket operator-(int value) {
        Ticket newTicket = *this;
        newTicket.price -= value;
        return newTicket;
    }


    // Overloading ++ (Prefix)
    Ticket& operator++() {
        // Increment the ticket's price
        price++;
        return *this;
    }

    // Overloading ++ (Postfix)
    Ticket operator++(int) {
        Ticket temp = *this; // Create a copy of the current state
        ++(*this);           // Increment the price using the prefix version
        return temp;         // Return the original state
    }


    // Explicit cast to std::string
    explicit operator std::string() const {
        ostringstream oss;
        oss << "Ticket Category: " << category << ", Seat Number: " << seatNumber
            << ", Price: $" << price;
        return oss.str();
    }

    // operator !
    bool operator!() const {
        return price == 0; // True if the ticket is free
    }

    // operator <
    bool operator<(const Ticket& other) const {
        // Compare based on ticket price
        return price < other.price;
    }

    // Overloading == (equality) operator
    bool operator==(const Ticket& other) const {
        return strcmp(category, other.category) == 0 &&
            seatNumber == other.seatNumber &&
            price == other.price;
    }

    // Friend functions for input and output
    friend ostream& operator<<(ostream& os, const Ticket& ticket);
    friend istream& operator>>(istream& is, Ticket& ticket);

    void serialize(ostream& out) const {
        
        size_t length = strlen(category); // Get the length of the C-style string
        out.write(reinterpret_cast<const char*>(&length), sizeof(length)); // Write the length
        out.write(category, length); // Write the string data

        // Serialize other members
        out.write(reinterpret_cast<const char*>(&seatNumber), sizeof(seatNumber));
        out.write(reinterpret_cast<const char*>(&price), sizeof(price));
    }

    Ticket(const char* category, int seatNumber, int price) {
        this->category = new char[strlen(category) + 1];
        strcpy(this->category, category);
        this->seatNumber = seatNumber;
        this->price = price;
    }

    void deserialize(istream& in) {
        // Deserialize 'category' (C-style string)
        size_t length;
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        char* categoryBuffer = new char[length + 1];
        in.read(categoryBuffer, length);
        categoryBuffer[length] = '\0';

        setCategory(categoryBuffer); // Assuming 'setCategory' is a method of 'Ticket'
        delete[] categoryBuffer;

        // Deserialize other members
        in.read(reinterpret_cast<char*>(&seatNumber), sizeof(seatNumber));
        in.read(reinterpret_cast<char*>(&price), sizeof(price));
    }

};

int Ticket::ID_COUNTER = 0;

ostream& operator<<(ostream& os, const Ticket& ticket) {
    os << "Ticket ID: " << ticket.ticketID << "\nCategory: " << ticket.category
        << "\nSeat Number: " << ticket.seatNumber << "\nPrice: $" << ticket.price;
    return os;
}

istream& operator>>(istream& is, Ticket& ticket) {
    char buffer[256];


    cout << "Enter ticket category: ";
    is.getline(buffer, 256);
    ticket.setCategory(buffer);

    cout << "Enter seat number: ";
    is >> ticket.seatNumber;
    is.ignore(); // To ignore the newline character after reading seatNumber

    cout << "Enter ticket price: ";
    is >> ticket.price;
    is.ignore(); // To ignore the newline character after reading price

    return is;
}
