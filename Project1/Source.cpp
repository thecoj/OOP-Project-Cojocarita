
//Cojocarita Cristian, year 3, Ticketing App, 
//4 classes: Event, Ticket, Seat and Venue.
//Class Venue doesn't have all the overloading required


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

/*

int main() {
    try {


        // Testing Event
        Event event("Concert", "2023-08-15", "20:00");
        cout << "Original Event: " << event << endl;
        ++event; // Prefix increment
        cout << "Event after Prefix Increment: " << event << endl;
        event++; // Postfix increment
        cout << "Event after Postfix Increment: " << event << endl;
        // Explicit cast to std::string
        std::string eventString = static_cast<std::string>(event);
        std::cout << "Event as String: " << eventString << std::endl;
        cout << "Event is default? " << (!event ? "Yes" : "No") << endl;
        //overloading <
        Event event1("Concert", "2023-08-15", "20:00");
        Event event2("Seminar", "2023-08-20", "10:00");
        cout << "Is event1 earlier than event2? " << (event1 < event2 ? "Yes" : "No") << endl;
        //== operator
        cout << "Are event1 and event2 equal? " << (event1 == event2 ? "Yes" : "No") << endl;


        // Testing Ticket
        Ticket ticket("VIP", 101, 50);
        cout << "Original Ticket: " << ticket << endl;
        ++ticket; // Prefix increment
        cout << "Ticket after Prefix Increment: " << ticket << endl;
        ticket++; // Postfix increment
        cout << "Ticket after Postfix Increment: " << ticket << endl;
        // Explicit cast to std::string
        std::string ticketString = static_cast<std::string>(ticket);
        std::cout << "Ticket as String: " << ticketString << std::endl;
        cout << "Ticket is free? " << (!ticket ? "Yes" : "No") << endl;
        //overloading <
        Ticket ticket1("VIP", 101, 50); // price 50
        Ticket ticket2("Standard", 102, 30); // price 30
        cout << "Is ticket1 cheaper than ticket2? " << (ticket1 < ticket2 ? "Yes" : "No") << endl;
        //overloading ==
        cout << "Are ticket1 and ticket2 equal? " << (ticket1 == ticket2 ? "Yes" : "No") << endl;



        // Testing Seat
        Seat seat(5, 10, "Regular");
        cout << "Original Seat: " << seat << endl;
        ++seat; // Prefix increment
        cout << "Seat after Prefix Increment: " << seat << endl;
        seat++; // Postfix increment
        cout << "Seat after Postfix Increment: " << seat << endl;
        // Explicit cast to std::string
        std::string seatString = static_cast<std::string>(seat);
        std::cout << "Seat as String: " << seatString << std::endl;
        cout << "Seat is unassigned? " << (!seat ? "Yes" : "No") << endl;
        //overloading <
        Seat seat1(5, 10, "Regular"); // Seat in row 5, number 10
        Seat seat2(5, 15, "Regular"); // Seat in row 5, number 15

        cout << "Is seat1 closer to the front than seat2? " << (seat1 < seat2 ? "Yes" : "No") << endl;
        //overloading ==
        cout << "Are seat1 and seat2 equal? " << (seat1 == seat2 ? "Yes" : "No") << endl;




        // Testing Venue
        Venue venue("Theater", 2, 5, 10);
        cout << "Venue Details: " << venue << endl;
        Venue expandedVenue = venue + 1; // Add one more row
        cout << "Expanded Venue: " << expandedVenue << endl;
        // Explicit cast to std::string
        std::string venueString = static_cast<std::string>(venue);
        std::cout << "Venue as String: " << venueString << std::endl;
        cout << "Venue has no seats? " << (!venue ? "Yes" : "No") << endl;



    }
    catch (const std::exception& e) {
        cout << "An error occurred: " << e.what() << endl;
    }

    return 0;
}

*/

int main(int argc, char* argv[]) {
    // Check if a command line parameter is provided
    if (argc < 2) {
        // If no command line parameter is provided => display menu for console input
        cout << "Welcome to the Ticketing App!\n";
        
        int choice;

        do {
            // Display menu options
            cout << "Ticketing App Menu:\n";
            cout << "1. Book Ticket\n";
            cout << "2. View Tickets\n";
            cout << "3. Save Tickets to Binary File\n";
            cout << "4. Load Tickets from Binary File\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                Ticket newTicket;

                // Prompt the user for ticket details
                cout << "Enter ticket details:\n";
                cout << "Enter event name: ";
                cin >> newTicket.eventName;

                cout << "Enter seat row: ";
                cin >> newTicket.seatRow;

                cout << "Enter seat number: ";
                cin >> newTicket.seatNumber;

                cout << "Enter ticket price: ";
                cin >> newTicket.price;

                // Display booking confirmation
                cout << "\nTicket booked successfully!\n";

                break;
            case 2:
                if (ticketsVector.empty()) {
                    cout << "\nNo tickets booked yet.\n";
                }
                else {
                    // Display header
                    cout << "\nList of booked tickets:\n";
                    cout << "-------------------------------------------\n";

                    // Display each booked ticket
                    for (const Ticket& ticket : ticketsVector) {
                        cout << "Event: " << ticket.eventName << "\n";
                        cout << "Seat: Row " << ticket.seatRow << ", Number " << ticket.seatNumber << "\n";
                        cout << "Price: $" << ticket.price << "\n";
                        cout << "-------------------------------------------\n";
                    }
                }
                break;
            case 3:
                // Add code for saving tickets to a binary file
                break;
            case 4:
                // Add code for loading tickets from a binary file
                break;
            case 0:
                cout << "Exiting the Ticketing App. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 0);
    }
    else {
        
        string filename = argv[1];
        ifstream file(filename);

        if (!file.is_open()) {
            // failed to open file
            cerr << "Error: Could not open file '" << filename << "'.\n";
            return 1;
        }

        // Process data 
        cout << "Processing data from file: " << filename << "\n";
        // Next => code to read data from the file

       
        file.close();
    }

    return 0;
}