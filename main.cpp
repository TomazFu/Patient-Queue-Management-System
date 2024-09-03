#include <iostream>  // Include the input/output stream library for basic input/output operations.
#include <ctime>     // Include the time library for time-related functions.
#include <string>    // Include the string library for string manipulation.
#include "DynamicQueue.h"  // Include the header file for the DynamicQueue class.
#include "Patient.h"      // Include the header file for the Patient class.

using namespace std;

// Function declarations
void showMainPage();  // Function to display the main page options
int enterOption();    // Function to get user input for the option
void processOption(int option, int &counterNo, DynamicQueue& NormalQueue, DynamicQueue& PriorityQueue);  // Function to process the selected option
int ageCalculation(string icNo, int currentYear);  // Function to calculate age based on IC number and current year
void showQueueMenu(DynamicQueue& NormalQueue, DynamicQueue& PriorityQueue);  // Function to display the queue menu options
void showQueue(DynamicQueue& NormalQueue, DynamicQueue& PriorityQueue);  // Function to display the combined patient queue
void processQueue(int option, DynamicQueue& NormalQueue, DynamicQueue& PriorityQueue);  // Function to process the selected queue option
void processPatientQueue(DynamicQueue& queue);  // Function to process the selected queue operation
void mergeQueue(DynamicQueue& NormalQueue, DynamicQueue& PriorityQueue);  // Function to merge the NormalQueue and PriorityQueue
void showDoctorMenu();  // Function to display the doctor's menu options
void processQueueOperation(int option, DynamicQueue& queue);  // Function to process the selected queue operation
bool isValidIC(string icNo);

int main() {
    // Variable initialization
    int option = 0;  // Variable to store the user's selected option
    int counterNo = 0;  // Counter for patient numbers
    DynamicQueue NormalQueue;  // Queue for normal patients
    DynamicQueue PriorityQueue;  // Queue for priority patients

    do {
        // Display main page options
        showMainPage();
        // Get user option
        option = enterOption();
        // Process the selected option
        processOption(option, counterNo, NormalQueue, PriorityQueue);
    } while (option != 3);

    return 0;
}

void showMainPage() {
    // Display the main page for the Patient Queue Management System
    cout << "\nPatient Queue Management System\n\n\n";
    // Display the available options
    cout << "1 [Patient Registration]\n";
    cout << "2 [Queue Processing    ]\n";
    cout << "3 [Exit                ]\n\n";
}

int enterOption() {
    int option;
    // Prompt the user to enter an option
    cout << "Enter Option: ";
    // Read the user's input into the 'option' variable
    cin >> option;
    // Return the entered option
    return option;
}

void processOption(int option, int &counterNo, DynamicQueue& NormalQueue, DynamicQueue& PriorityQueue) {
    switch (option) {
        case 1: {
            // Get the current time
            time_t now = time(0);
            tm *ltm = localtime(&now);

            // Determine whether it's AM or PM
            string beforeOrAfterNoon = (ltm->tm_hour < 12) ? "am" : "pm";

            // Format the hour to be in the range 1 to 12
            if (ltm->tm_hour > 12) {
                ltm->tm_hour -= 12;
            } else if (ltm->tm_hour == 0) {
                ltm->tm_hour = 12; // Midnight (12:00 AM)
            }

            // Create a string representation of the current time
            string time = to_string(ltm->tm_hour) + "." + (ltm->tm_min < 10 ? "0" : "") + to_string(ltm->tm_min) + beforeOrAfterNoon;

            // Display registration details and get user input
            cout << "Time: " << time << endl;
            cout << "Counter Number: " << ++counterNo << endl;
            string icNo, name;
            int age;
            char gender;
            bool isPregnant, isOKU;

			// Checks the validation of IC number
			while (isValidIC(icNo) != true){
				cout << "Enter Patient IC: ";
				cin >> icNo;
				if(isValidIC(icNo) != true){
					cout << "Incorrect IC No format. Please try again." << endl;
				}
			}
            // Derive gender from the last digit of IC number
            gender = ((icNo.back() - '0') % 2 ? 'M' : 'F');

            // Calculate age based on IC number
            age = ageCalculation(icNo, ltm->tm_year + 1900);

            cout << "Enter Name: ";
            cin >> name;

            // If the patient is female, prompt for pregnancy status
            if (gender == 'F') {
                char pregnantInput;
                cout << "Pregnant [Y/N]: ";
                cin >> pregnantInput;
                isPregnant = (pregnantInput == 'Y' || pregnantInput == 'y');
            } else {
                isPregnant = false;
            }

            // Prompt for OKU (disabled) status
            cout << "OKU (Disabled) [Y/N]: ";
            char isOKUInput;
            cin >> isOKUInput;
            isOKU = (isOKUInput == 'Y' || isOKUInput == 'y');

            // Confirm patient registration
            char confirmStatusInput;
            cout << "Confirm [Y/N]: ";
            cin >> confirmStatusInput;

            if (confirmStatusInput == 'Y' || confirmStatusInput == 'y') {
                // Create a new patient record
                Patient newPatient(time, counterNo, icNo, name, age, gender, isPregnant, isOKU);

                // Enqueue the patient based on priority
                if (newPatient.age >= 65 || newPatient.isPregnant || newPatient.isOKU) {
                    PriorityQueue.enQueue(newPatient);
                } else {
                    NormalQueue.enQueue(newPatient);
                }

                cout << "Patient's record created successfully." << endl;
            } else {
                cout << "Patient's record creation cancelled." << endl;
            }

            break;
        }
        case 2: {
            // Initialize option and counterNo for queue processing
            int option = 0;
            int counterNo = 1;

            do {
                // Display queue menu options
                showQueueMenu(NormalQueue, PriorityQueue);

                // Get user option for queue processing
                option = enterOption();

                // Process the selected queue option
                processQueue(option, NormalQueue, PriorityQueue);
            } while (option != 4);

            break;
        }
        case 3: {
		    // Display an exit message when option 3 is selected
		    cout << "Exiting Program..." << endl;
		    break;
		}
		default: {
		    // Display a message for an invalid option
		    cout << "Invalid option!" << endl;
		    cout << "Please try again..." << endl;
		}
    }
}

int ageCalculation(string icNo, int currentYear) {
    // Extract the two-digit year of birth from the IC number
    int yearBorn = stoi(icNo.substr(0, 2));

    // Adjust the birth year based on the current year
    if (yearBorn <= currentYear % 100) {
        yearBorn += 2000; // Born in the current century (20YY)
    } else {
        yearBorn += 1900; // Born in the previous century (19YY)
    }

    // Calculate the age by subtracting the birth year from the current year
    int age = currentYear - yearBorn;

    // Return the calculated age
    return age;
}

void showQueue(DynamicQueue& queue) {
    // Create a temporary queue to store and process patients
    DynamicQueue tempQueue;

    // Process patients and display their details
    while (!queue.isEmpty()) {
        Patient patient;
        queue.deQueue(patient);

        // Display details of the current patient
        patient.showDetails();

        // Enqueue the patient into the temporary queue
        tempQueue.enQueue(patient);

        // Display a separator if there are more patients in the queue
        if (!queue.isEmpty()) {
            cout << "\t|" << endl;
            cout << "\t\\/" << endl;
        }
    }

    // Restore patients from the temporary queue to the original queue
    while (!tempQueue.isEmpty()) {
        Patient patient;
        tempQueue.deQueue(patient);
        queue.enQueue(patient);
    }

    // Clear the temporary queue
    tempQueue.clear();
}

void showQueueMenu(DynamicQueue& NormalQueue, DynamicQueue& PriorityQueue) {
    // Display the active queue menu
    cout << "\t\t\n[Active Queue Menu]\n\n\n";

    // Display options for Normal Queue and Priority Queue
    cout << "1. Normal Queue (" << NormalQueue.count() << " Patients)\n";
    cout << "2. Priority Queue (" << PriorityQueue.count() << " patients)\n";
    cout << "3. Merge Queue\n";
    cout << "4. Return\n\n";
}

void processQueue(int option, DynamicQueue& NormalQueue, DynamicQueue& PriorityQueue) {
    switch (option) {
        case 1:
            // Process the Normal Queue
            processPatientQueue(NormalQueue);
            break;

        case 2:
            // Process the Priority Queue
            processPatientQueue(PriorityQueue);
            break;

        case 3:
            // Merge the Normal Queue and Priority Queue
            mergeQueue(NormalQueue, PriorityQueue);
            break;

        case 4:
            // Display message and exit the Queue Menu
            cout << "Exiting Queue Menu..." << endl;
            break;

        default:
            // Display message for an invalid option
            cout << "Invalid option!" << endl;
            cout << "Please try again..." << endl;
    }
}

void mergeQueue(DynamicQueue& NormalQueue, DynamicQueue& PriorityQueue) {
    // Check if Priority Queue is not empty
    if (!PriorityQueue.isEmpty()) {
        // Dequeue and enqueue patients from Priority Queue to Normal Queue
        while (!PriorityQueue.isEmpty()) {
            Patient patient;
            PriorityQueue.deQueue(patient);
            NormalQueue.enQueue(patient);
        }

        // Sort patients in Normal Queue by counterNumber in ascending order
        for (int i = 0; i < NormalQueue.count(); i++) {
            for (int j = 0; j < NormalQueue.count() - 1; j++) {
                Patient patient1, patient2;
                NormalQueue.deQueue(patient1);
                NormalQueue.deQueue(patient2);

                // Compare counterNumber and enqueue patients in ascending order
                if (patient1.getCounterNo() > patient2.getCounterNo()) {
                    NormalQueue.enQueue(patient2);
                    NormalQueue.enQueue(patient1);
                } else {
                    NormalQueue.enQueue(patient1);
                    NormalQueue.enQueue(patient2);
                }
            }
        }

        // Clear Priority Queue after merging
        PriorityQueue.clear();

        cout << "Queue Merged." << endl;
    } else {
    	// Display message if queue is empty
        cout << "Priority Queue is empty. No actions occurred." << endl;
    }
}

void showDoctorMenu(){
	// Display doctor menu options
    cout << "\n[1] Call Next Patient\n";
    cout << "[2] Call Patient No#\n";
    cout << "[3] Delete Patient\n";
    cout << "[4] Reset Queue\n";
    cout << "[5] Return\n\n";
}

void processPatientQueue(DynamicQueue& queue) {
    int option = 0;
    do {
        // Check if the queue is not empty
        if (!queue.isEmpty()) {
            // Display the patient queue and doctor menu
            showQueue(queue);
            showDoctorMenu();

            // Get and process the doctor's menu option
            option = enterOption();
            processQueueOperation(option, queue);
        } else {
            // Display a message if the queue is empty
            cout << "Queue is empty." << endl;
            break;
        }
    } while (option != 5);
}

// Function to process the doctor's selected option in the patient queue
void processQueueOperation(int option, DynamicQueue& queue) {
    // Variable to store the patient number entered by the user
    int patientNo = 0;

    // Switch statement to determine the action based on the selected option
    switch (option) {
        // Case 1: Call the next patient in the queue
        case 1:
            // Check if the queue is not empty
            if (!queue.isEmpty()) {
                // Dequeue the next patient
                Patient patient;
                queue.deQueue(patient);

                // Determine the title based on gender
                string title = (patient.getGender() == 'M') ? "Mr " : "Mrs ";

                // Display the calling message
                cout << "Calling " << title << patient.getName() << " ......No " << patient.getCounterNo() << "." << endl;
            } else {
                // Display a message if the queue is empty
                cout << "Queue is empty. No patients to call." << endl;
            }
            break;

        // Case 2: Call a specific patient by number
        case 2:
            // Prompt the user to enter the patient number
            cout << "Please enter the patient's number: ";
            cin >> patientNo;

            // Check if the queue is not empty
            if (!queue.isEmpty()) {
                // Create a temporary queue to store patients
                DynamicQueue tempQueue;

                // Flag to indicate if the patient with the specified number is found
                bool patientFound = false;

                // Process patients until the desired patient number is found
                while (!queue.isEmpty()) {
                    Patient patient;
                    queue.deQueue(patient);

                    // Check if the current patient matches the specified number
                    if (patientNo == patient.getCounterNo()) {
                        // Determine the title based on gender
                        string title = (patient.getGender() == 'M') ? "Mr " : "Mrs ";

                        // Display the calling message for the specific patient
                        cout << "Calling " << title << patient.getName() << " ......No " << patient.getCounterNo() << endl;
                        
                        // Set the flag to indicate that the patient is found
                        patientFound = true;
                    } else {
                        // Enqueue patients other than the one to be called into the temporary queue
                        tempQueue.enQueue(patient);
                    }
                }

                // Enqueue back the remaining patients from the temporary queue to the original queue
                while (!tempQueue.isEmpty()) {
                    Patient patient;
                    tempQueue.deQueue(patient);
                    queue.enQueue(patient);
                }

                // Display a message if the patient with the specified number is not found
                if (!patientFound) {
                    cout << "Patient with number " << patientNo << " not found in the queue." << endl;
                }
            } else {
                // Display a message if the queue is empty
                cout << "Queue is empty. No patients to call." << endl;
            }
            break;

        // Case 3: Delete a specific patient by number
        case 3:
            // Prompt the user to enter the patient number
            cout << "Please enter the patient's number: ";
            cin >> patientNo;

            // Check if the queue is not empty
            if (!queue.isEmpty()) {
                // Create a temporary queue to store patients
                DynamicQueue tempQueue;

                // Flag to indicate if the patient with the specified number is found
                bool patientFound = false;

                // Process patients until the desired patient number is found
                while (!queue.isEmpty()) {
                    Patient patient;
                    queue.deQueue(patient);

                    // Check if the current patient matches the specified number
                    if (patientNo == patient.getCounterNo()) {
                        // Set the flag to indicate that the patient is found
                        patientFound = true;

                        // Display a message indicating that the patient record is deleted
                        cout << "Patient record deleted." << endl;
                    } else {
                        // Enqueue patients other than the one to be deleted into the temporary queue
                        tempQueue.enQueue(patient);
                    }
                }

                // Enqueue back the remaining patients from the temporary queue to the original queue
                while (!tempQueue.isEmpty()) {
                    Patient patient;
                    tempQueue.deQueue(patient);
                    queue.enQueue(patient);
                }

                // Display a message if the patient with the specified number is not found
                if (!patientFound) {
                    cout << "Patient with number " << patientNo << " not found in the queue." << endl;
                }
            } else {
                // Display a message if the queue is empty
                cout << "Queue is empty. No patients to remove." << endl;
            }
            break;

        // Case 4: Reset the patient queue
        case 4:
            // Clear the patient queue
            queue.clear();
            
            // Display a message indicating that the queue has been reset
            cout << "Queue has been reset. No patients in the queue." << endl;
            break;

        // Case 5: Exit the Doctor Menu
        case 5:
            // Display a message indicating that the menu is exiting
            cout << "Exiting Menu..." << endl;
            break;

        // Default case: Display a message for an invalid option
        default:
            // Display a message for an invalid option
            cout << "Invalid option!" << endl;
            cout << "Please try again..." << endl;
    }
}

// Function to check if a string contains only digits and has a specified length
bool isValidIC(string icNo) {
    // Check if the string has the expected length
    if (icNo.length() != 12) {
        return false;
    }

    // Check if all characters in the string are digits
    for (char digit : icNo) {
        if (!isdigit(digit)) {
            return false;
        }
    }

    // If both conditions are met, the IC is valid
    return true;
}
