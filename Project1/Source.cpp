
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
#include "Ticket.h"
#include "Venue.h"
#include "Event.h"
#include "Seat.h"
using namespace std;



void saveTicketsToFile(const vector<Ticket>& tickets, const string& filename) {
    ofstream outFile(filename, ios::out | ios::binary);
    if (!outFile) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    for (const auto& ticket : tickets) {
        ticket.serialize(outFile);
    }

    outFile.close();
}

void loadTicketsFromFile(vector<Ticket>& tickets, const string& filename) {
    ifstream inFile(filename, ios::in | ios::binary);
    if (!inFile) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    while (inFile.peek() != EOF) {
        Ticket ticket;
        ticket.deserialize(inFile);
        if (inFile) {
            tickets.push_back(ticket);
        }
    }

    inFile.close();
}


int main(int argc, char* argv[]) {
    vector<Ticket> tickets;
    vector<Event> events;
    vector<Seat> seats;
    Venue venue;

    // Check for command-line argument
    if (argc > 1) {
        string filename = argv[1];
        ifstream file(filename);
        if (file.is_open()) {
            // Code to read from file and populate tickets, events, etc.
            // Example: while (file >> ticket) { tickets.push_back(ticket); }
            file.close();
        }
    }

    bool exitProgram = false;
    while (!exitProgram) {
        cout << "Menu:" << endl;
        cout << "1. Add Ticket" << endl;
        cout << "2. Display Tickets" << endl;
        cout << "3. Save Tickets to File" << endl;
        cout << "4. Print File" << endl;
        cout << "5. Exit" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            string category;
            int seatNumber;
            int price;

            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

            cout << "Enter ticket name: ";
            getline(cin, category);

            cout << "Enter seat number: ";
            cin >> seatNumber;

            // Check and clear any extraneous input in the buffer
            if (cin.fail()) {
                cin.clear(); // Clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the input buffer
                cout << "Invalid input for seat number. Please try again." << endl;
                continue; // Skip the rest of this iteration
            }

       

            cout << "Enter ticket price: ";
            cin >> price;

            Ticket newTicket(category.c_str(), seatNumber, price);
            tickets.push_back(newTicket);
            cout << "Ticket added successfully!" << endl;

            break;
        }
        case 2: {
            if (tickets.empty()) {
                cout << "No tickets available." << endl;
            }
            else {
                cout << "Tickets:" << endl;
                for (const auto& ticket : tickets) {
                    cout << ticket << endl;
                   
                }
            }
            break;
        }
        case 3: {
            string filename;
            cout << "Enter the filename to save tickets: ";
            cin >> filename;

            saveTicketsToFile(tickets, filename);
            cout << "Tickets saved successfully to " << filename << endl;
            break;
        }
        case 4: { 
            int ticketID;
            cout << "Enter Ticket ID: ";
            cin >> ticketID;

            bool found = false;
            for (const auto& ticket : tickets) {
                if (ticket.getTicketID() == ticketID) {
                    ticket.print(); 
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Ticket with ID " << ticketID << " not found." << endl;
            }
            break;
        }
        case 5: {
            exitProgram = true;
            break;
        }
        default: {
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        }
    }

    return 0;
}
