#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Class to represent a date with month, day, and year
class Date {
public:
    int month, day, year;
    Date(int m, int d, int y) : month(m), day(d), year(y) {}
};

// Base class for appointments with a description and a date
class Appointment {
protected:
    string description;
    Date date;
public:
    Appointment(string desc, Date d) : description(desc), date(d) {}
    // Pure virtual function to check if the appointment occurs on the given date
    virtual bool occurs_on(int y, int m, int d) = 0;
    string getDescription() { return description; }
};

// Derived class for one-time day appointments (all three date fields must match)
class Day : public Appointment {
public:
    Day(string desc, Date d) : Appointment(desc, d) {}
    bool occurs_on(int y, int m, int d) override {
        return date.year == y && date.month == m && date.day == d;
    }
};

// Derived class for monthly recurring appointments (only day and year must match)
class Monthly : public Appointment {
public:
    Monthly(string desc, Date d) : Appointment(desc, d) {}
    bool occurs_on(int y, int m, int d) override {
        return date.year == y && date.day == d;
    }
};

int main() {
    ofstream out("output.txt");
    if (!out) {
        cout << "Error opening output file." << endl;
        return 1;
    }
    out << "outPut" << endl;

    // Test the occurs_on functions for both Day and Monthly appointments
    out << "=== Appointment Functions ===" << endl << endl;

    out << "Day Appointment:" << endl;
    Day dayAppt("Dentist visit", Date(4, 18, 2026));
    out << "  - Occurs on 2026-04-18: " << (dayAppt.occurs_on(2026, 4, 18) ? "Yes" : "No") << endl;
    out << "  - Occurs on 2026-04-19: " << (dayAppt.occurs_on(2026, 4, 19) ? "Yes" : "No") << endl;
    out << "  - Occurs on 2027-04-18: " << (dayAppt.occurs_on(2027, 4, 18) ? "Yes" : "No") << endl;

    out << endl << "Monthly Appointment:" << endl;
    Monthly monthlyAppt("Pay bills", Date(1, 15, 2026));
    out << "  - Occurs on 2026-01-15: " << (monthlyAppt.occurs_on(2026, 1, 15) ? "Yes" : "No") << endl;
    out << "  - Occurs on 2026-02-15: " << (monthlyAppt.occurs_on(2026, 2, 15) ? "Yes" : "No") << endl;
    out << "  - Occurs on 2027-01-15: " << (monthlyAppt.occurs_on(2027, 1, 15) ? "Yes" : "No") << endl;
    out << "  - Occurs on 2026-01-16: " << (monthlyAppt.occurs_on(2026, 1, 16) ? "Yes" : "No") << endl;

    // Vector of Appointment pointers with a mixture of Day and Monthly appointments
    vector<Appointment*> appointments;
    appointments.push_back(new Day("Dentist", Date(4, 18, 2026)));
    appointments.push_back(new Monthly("Pay bills", Date(1, 15, 2026)));
    appointments.push_back(new Day("Meeting", Date(4, 20, 2026)));
    appointments.push_back(new Monthly("Gym", Date(5, 10, 2026)));

    // Have the user enter a date and print out all appointments that occur on that date
    int year, month, day;
    cout << endl << "=== Appointment Checker ===" << endl;
    cout << "Enter a date (year month day): ";
    cin >> year >> month >> day;

    out << endl << "=== Appointment Checker ===" << endl;
    out << "Entered date: " << year << "-" << (month < 10 ? "0" : "") << month << "-" << (day < 10 ? "0" : "") << day << endl;
    out << "Appointments on this date:" << endl;
    cout << endl << "Appointments on " << year << "-" << (month < 10 ? "0" : "") << month << "-" << (day < 10 ? "0" : "") << day << ":" << endl;
    bool found = false;
    for (auto appt : appointments) {
        if (appt->occurs_on(year, month, day)) {
            out << "  - " << appt->getDescription() << endl;
            cout << "  - " << appt->getDescription() << endl;
            found = true;
        }
    }
    if (!found) {
        out << "  No appointments on this date." << endl;
        cout << "  No appointments on this date." << endl;
    }

    out.close();

    // Delete dynamically allocated appointments
    for (auto appt : appointments) {
        delete appt;
    }

    return 0;
}