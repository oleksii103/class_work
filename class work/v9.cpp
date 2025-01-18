#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Flight {
public:
    Flight(const string& flightNumber, const string& destination, const string& departureTime, const string& gate)
        : flightNumber(flightNumber), destination(destination), departureTime(departureTime), gate(gate) {}

    string getFlightNumber() const { return flightNumber; }
    string getDestination() const { return destination; }
    string getDepartureTime() const { return departureTime; }
    string getGate() const { return gate; }

    void setDepartureTime(const string& newTime) { departureTime = newTime; }
    void setGate(const string& newGate) { gate = newGate; }

    void display() const {
        cout << "Flight number: " << flightNumber
            << ", Destination: " << destination
            << ", Departure time: " << departureTime
            << ", Gate: " << gate << endl;
    }

private:
    string flightNumber;
    string destination;
    string departureTime;
    string gate;
};

void addFlight(vector<Flight>& flights) {
    string flightNumber, destination, departureTime, gate;
    cout << "Add flight number: ";
    cin >> flightNumber;
    cout << "Add destination: ";
    cin >> destination;
    cout << "Add departure time: ";
    cin >> departureTime;
    cout << "Add gate: ";
    cin >> gate;
    flights.emplace_back(flightNumber, destination, departureTime, gate);
    cout << "Flight added successfully.\n";
}

void searchFlight(const vector<Flight>& flights) {
    int choice;
    cout << "1: Search by flight number | 2: Search by destination\nChoose: ";
    cin >> choice;

    if (choice == 1) {
        string flightNumber;
        cout << "Enter flight number: ";
        cin >> flightNumber;
        bool found = false;
        for (const auto& flight : flights) {
            if (flight.getFlightNumber() == flightNumber) {
                flight.display();
                found = true;
            }
        }
        if (!found) {
            cout << "Flight not found.\n";
        }
    }
    else if (choice == 2) {
        string destination;
        cout << "Enter destination: ";
        cin >> destination;
        bool found = false;
        for (const auto& flight : flights) {
            if (flight.getDestination() == destination) {
                flight.display();
                found = true;
            }
        }
        if (!found) {
            cout << "Flight not found.\n";
        }
    }
    else {
        cout << "Invalid option.\n";
    }
}

void editFlight(vector<Flight>& flights) {
    string flightNumber;
    cout << "Enter flight number to edit: ";
    cin >> flightNumber;

    for (auto& flight : flights) {
        if (flight.getFlightNumber() == flightNumber) {
            cout << "1. Edit Departure Time\n2. Edit Gate\nChoose option: ";
            int choice;
            cin >> choice;

            if (choice == 1) {
                string newTime;
                cout << "Enter new departure time (HH:MM): ";
                cin >> newTime;
                flight.setDepartureTime(newTime);
                cout << "Departure time updated.\n";
            }
            else if (choice == 2) {
                string newGate;
                cout << "Enter new gate: ";
                cin >> newGate;
                flight.setGate(newGate);
                cout << "Gate updated.\n";
            }
            else {
                cout << "Invalid choice.\n";
            }
            return;
        }
    }
    cout << "Flight not found.\n";
}

void deleteFlight(vector<Flight>& flights) {
    string flightNumber;
    cout << "Enter flight number to delete: ";
    cin >> flightNumber;

    auto it = remove_if(flights.begin(), flights.end(), [&flightNumber](const Flight& flight) {
        return flight.getFlightNumber() == flightNumber;
        });

    if (it != flights.end()) {
        flights.erase(it, flights.end());
        cout << "Flight deleted successfully.\n";
    }
    else {
        cout << "Flight not found.\n";
    }
}

void displayAllFlights(const vector<Flight>& flights) {
    if (flights.empty()) {
        cout << "No flights available.\n";
        return;
    }
    for (const auto& flight : flights) {
        flight.display();
    }
}

void loadFlights(vector<Flight>& flights, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file.\n";
        return;
    }

    string flightNumber, destination, departureTime, gate;
    while (file >> flightNumber >> destination >> departureTime >> gate) {
        flights.emplace_back(flightNumber, destination, departureTime, gate);
    }
    file.close();
    cout << "Flights loaded from file.\n";
}

void saveFlights(const vector<Flight>& flights, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Error opening file.\n";
        return;
    }

    for (const auto& flight : flights) {
        file << flight.getFlightNumber() << " "
            << flight.getDestination() << " "
            << flight.getDepartureTime() << " "
            << flight.getGate() << "\n";
    }
    file.close();
    cout << "Flights saved to file.\n";
}

int main() {
    vector<Flight> flights;
    string filename = "flights.txt";
    loadFlights(flights, filename);

    while (true) {
        cout << "\nMenu:\n1. Add Flight\n2. Search Flight\n3. Edit Flight\n4. Delete Flight\n5. Display All Flights\n6. Save and Exit\nChoose an option: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            addFlight(flights);
            break;
        case 2:
            searchFlight(flights);
            break;
        case 3:
            editFlight(flights);
            break;
        case 4:
            deleteFlight(flights);
            break;
        case 5:
            displayAllFlights(flights);
            break;
        case 6:
            saveFlights(flights, filename);
            return 0;
        default:
            cout << "Invalid option. Try again.\n";
        }
    }
}
