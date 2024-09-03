// Include the header file for the Patient class
#include "Patient.h"

// Include the standard input/output stream library
#include <iostream>

// Use the standard namespace for C++ (std)
using namespace std;

// Default constructor for the Patient class
Patient::Patient() : time(""), counterNo(0), icNo(""), name(""), age(0), gender(' '), isPregnant(false), isOKU(false) {
}

// Parameterized constructor for the Patient class
Patient::Patient(string time, int counter, string ic, string n, int a, char g, bool pregnant, bool oku)
    : time(time), counterNo(counter), icNo(ic), name(n), age(a), gender(g), isPregnant(pregnant), isOKU(oku) {
}

// Getter function to retrieve the counter number of the patient
int Patient::getCounterNo() {
    return counterNo;
}

// Getter function to retrieve the time of the patient
string Patient::getTime() {
    return time;
}

// Getter function to retrieve the name of the patient
string Patient::getName() {
    return name;
}

// Getter function to retrieve the gender of the patient
char Patient::getGender() {
    return gender;
}

// Getter function to retrieve the age of the patient
int Patient::getAge() {
    return age;
}

// Function to display the details of the patient
void Patient::showDetails() const {
    // Calculate the total content width by adding the lengths of time, name, age, and additional characters
    int contentWidth = time.length() + name.length() + to_string(age).length() + 13;

    // Set the box width based on the content width and additional characters
    int boxWidth = contentWidth + 2;

    // Display the top border of the box
    cout << "+" << string(boxWidth, '-') << "+" << endl;

    // Display the patient details in a formatted box
    cout << "| [" << counterNo << "] " << time << ", " << name << ", (" << gender << "), " << age << " |" << endl;

    // Display the bottom border of the box
    cout << "+" << string(boxWidth, '-') << "+" << endl;
}

