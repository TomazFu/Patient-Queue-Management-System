// Header guard to prevent multiple definitions of the Patient struct
#ifndef _PATIENT_
#define _PATIENT_

// Include necessary libraries for string manipulation and output formatting
#include <iostream>
#include <iomanip>

// Use the standard namespace for C++ (std)
using namespace std;

// Definition of the Patient struct
struct Patient {
    // Member variables to store patient information
    string time;
    int counterNo;
    string icNo;
    string name;
    int age;
    char gender;
    bool isPregnant;
    bool isOKU;

    // Default constructor for the Patient struct
    Patient();

    // Parameterized constructor for the Patient struct
    Patient(string time, int counter, string ic, string n, int a, char g, bool pregnant, bool oku);

    // Getter function to retrieve the counter number of the patient
    int getCounterNo();

    // Getter function to retrieve the time of the patient
    string getTime();

    // Getter function to retrieve the name of the patient
    string getName();

    // Getter function to retrieve the gender of the patient
    char getGender();

    // Getter function to retrieve the age of the patient
    int getAge();

    // Function to display the details of the patient
    void showDetails() const;
};

// End of the header guard
#endif

