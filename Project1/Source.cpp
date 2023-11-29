#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>  
#include <vector>
using namespace std;

class Event {
    const int id;     // identifier 
    char* name;       // dynamically alloc string
    char* date;       
    char* time;       
    static int NO_EVENTS;        // static variable for nr of events
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
    friend istream& operator>>(istream& is, Event& event);

    
};
int Event::NO_EVENTS = 0;
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







class Ticket {
private:
    const int ticketID;       // ID for ticket
    char* category;           // category (VIP, etc.)
    int seatNumber;           // seat number 
    static int TICKET_COUNTER; // static counter to assign unique ticket IDs

    // default constructor
    Ticket() : ticketID(0), category(nullptr), seatNumber(0) {}

public:
    // constructor
    Ticket(const char* category, int seatNumber) : ticketID(++TICKET_COUNTER), seatNumber(seatNumber) {
        this->category = new char[strlen(category) + 1];
        strcpy_s(this->category, strlen(category) + 1, category);
    }

    // destructor
    ~Ticket() {
        cout << endl << "Ticket Destructor";
        delete[] category;
    }

    // copy constructor
    Ticket(const Ticket& t) : ticketID(t.ticketID), seatNumber(t.seatNumber) {
        cout << endl << "Ticket Copy Constructor";
        this->setCategory(string(t.category));
    }

    // assignment operator
    Ticket& operator=(const Ticket& source) {
        cout << endl << "Ticket Assignment Operator";
        if (this != &source) {
            this->setCategory(string(source.category));
            this->seatNumber = source.seatNumber;
        }
        return *this;
    }

    // setters and getters
    void setCategory(string category) {
        delete[] this->category;
        this->category = new char[category.size() + 1];
        strcpy_s(this->category, category.size() + 1, category.c_str());
    }

    string getCategory() const {
        return string(this->category);
    }

    void setSeatNumber(int seatNumber) {
        this->seatNumber = seatNumber;
    }

    int getSeatNumber() const {
        return seatNumber;
    }

    int getTicketID() const {
        return ticketID;
    }

    // Friend functions
    friend ostream& operator<<(ostream& console, const Ticket& t);
    // next i need to implement >> operator for ticket input

    friend istream& operator>>(istream& is, Ticket& ticket);
    
};


int Ticket::TICKET_COUNTER = 0;

// Overloaded << operator
ostream& operator<<(ostream& console, const Ticket& t) {
    console << "Ticket ID: " << t.ticketID << "\nCategory: " << t.category << "\nSeat Number: " << t.seatNumber;
    return console;
}

istream& operator>>(istream& is, Ticket& ticket) {
    char buffer[256]; // Buffer for input

    cout << "Enter ticket category: ";
    is.getline(buffer, 256);
    delete[] ticket.category;
    ticket.category = new char[strlen(buffer) + 1];
    strcpy(ticket.category, buffer);

    cout << "Enter seat number: ";
    is >> ticket.seatNumber;
    is.ignore(); // To ignore the newline character after reading seatNumber

    return is;
}




class Seat {
private:
    int row;        // row nr
    int number;     // seat nr in row
    string type;    // seat type (regular, VIP, etc)

public:
    // constructor
    Seat() : row(0), number(0), type("regular") {}

    //constructor
    Seat(int row, int number, string type) : row(row), number(number), type(type) {}

    // getters and setters
    int getRow() const { return row; }
    void setRow(int newRow) { row = newRow; }

    int getNumber() const { return number; }
    void setNumber(int newNumber) { number = newNumber; }

    string getType() const { return type; }
    void setType(string newType) { type = newType; }

    // overload the stream insertion operator for easy output
    friend ostream& operator<<(ostream& os, const Seat& seat) {
        os << "Seat Row: " << seat.row << ", Number: " << seat.number << ", Type: " << seat.type;
        return os;
    }

    friend istream& operator>>(istream& is, Seat& seat);

   
};


istream& operator>>(istream& is, Seat& seat) {
    cout << "Enter row number: ";
    is >> seat.row;

    cout << "Enter seat number: ";
    is >> seat.number;

    cout << "Enter seat type: ";
    is >> seat.type;

    return is;
}




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

   
    // overload 
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
    getline(is, venue.name);

    cout << "Enter number of rows: ";
    is >> venue.rows;

    cout << "Enter number of seats per row: ";
    is >> venue.seatsPerRow;

    // Assuming you need to update or set up the seating arrangement
    delete[] venue.seats; // Clear existing seats
    venue.seats = new Seat[venue.rows * venue.seatsPerRow];
    for (int i = 0; i < venue.rows * venue.seatsPerRow; ++i) {
        // Read each seat details here
        // ...
    }

    return is;
}


int main()
{
    return 0;
}