#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>  
#include <vector>
using namespace std;

class Event {
private:
    const int id;        // ID for the event
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





class Ticket {
private:
    static int ID_COUNTER;   // Static counter for generating unique ticket IDs
    const int ticketID;      // Unique ID for each ticket
    char* category;          // Dynamically allocated string for ticket category
    int seatNumber;          // Seat number associated with the ticket

public:
    // Default constructor
    Ticket() : ticketID(++ID_COUNTER), category(nullptr), seatNumber(0) {}

    // Parameterized constructor
    Ticket(const char* category, int seatNumber)
        : ticketID(++ID_COUNTER), seatNumber(seatNumber) {
        this->category = new char[strlen(category) + 1];
        strcpy(this->category, category);
    }

    // Copy constructor
    Ticket(const Ticket& other) : ticketID(other.ticketID), seatNumber(other.seatNumber) {
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

    // Setters
    void setCategory(const char* newCategory) {
        delete[] category;
        category = new char[strlen(newCategory) + 1];
        strcpy(category, newCategory);
    }

    void setSeatNumber(int newSeatNumber) {
        seatNumber = newSeatNumber;
    }

    // Friend functions for input and output
    friend ostream& operator<<(ostream& os, const Ticket& ticket);
    friend istream& operator>>(istream& is, Ticket& ticket);
};

int Ticket::ID_COUNTER = 0;

ostream& operator<<(ostream& os, const Ticket& ticket) {
    os << "Ticket ID: " << ticket.ticketID << "\nCategory: " << ticket.category << "\nSeat Number: " << ticket.seatNumber;
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

    // overload the stream insertion operator 
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



int main()
{
    return 0;
}