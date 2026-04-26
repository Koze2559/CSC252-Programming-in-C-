#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Base class Person with name, phone number, email address, and a virtual toString method for formatted output
class Person {
protected:
    string name, phone, email;
public:
    Person(string n, string p, string e) : name(n), phone(p), email(e) {}
    // Virtual method to output a description with name, contact info, and subclass-specific details
    virtual string toString() {
        return name + "\nContact info:\n\tPhone: " + phone + "\n\tEmail: " + email;
    }
};

// Student class that subclasses Person, adds year in college and role
class Student : public Person {
private:
    string year;
public:
    Student(string n, string p, string e, string y) : Person(n, p, e), year(y) {}
    string toString() override {
        return Person::toString() + "\n\tYear: " + year + "\n\tRole: student";
    }
};

// Employee class that subclasses Person and adds salary
class Employee : public Person {
protected:
    double salary;
public:
    Employee(string n, string p, string e, double s) : Person(n, p, e), salary(s) {}
    string toString() override {
        return Person::toString() + "\n\tSalary: " + to_string(salary);
    }
};

// Faculty class that subclasses Employee, adds title and role
class Faculty : public Employee {
private:
    string title;
public:
    Faculty(string n, string p, string e, double s, string t) : Employee(n, p, e, s), title(t) {}
    string toString() override {
        return Employee::toString() + "\n\tTitle: " + title + "\n\tRole: faculty";
    }
};

// Staff class that subclasses Employee, adds role and title
class Staff : public Employee {
private:
    string role;
public:
    Staff(string n, string p, string e, double s, string r) : Employee(n, p, e, s), role(r) {}
    string toString() override {
        return Employee::toString() + "\n\tRole: " + role + "\n\tTitle: staff";
    }
};

int main() {
    // Vector of pointers to Person to store different types polymorphically
    vector<Person*> people;

    // Add at least one instance of each class: Person, Student, Employee, Faculty, Staff
    people.push_back(new Person("Susan Smith", "800-555-1212", "susan@quirkymail.com"));
    people.push_back(new Student("Jerry Johnson", "123-456-7890", "jerjer@nat.edu", "sophomore"));
    people.push_back(new Employee("Larry Larson", "333-444-5555", "larry@threestooges.org", 123456.0));
    people.push_back(new Faculty("Linda Lee", "987-654-3210", "lindalou@whoknew.edu", 150000.0, "adjunct professor"));
    people.push_back(new Staff("Jane Jones", "567-123-6565", "jane@whizkid.com", 100000.0, "registration"));

    // Iterate over all Person instances and call toString() to display formatted information
    for (auto p : people) {
        cout << p->toString() << endl << endl;
    }

    // Delete dynamically allocated memory
    for (auto p : people) {
        delete p;
    }

    return 0;
}