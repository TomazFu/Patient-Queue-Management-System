// Header guard to prevent multiple definitions of the DynamicQueue class
#ifndef _QUEUE_
#define _QUEUE_

// Include the Patient header file for using the Patient class
#include "Patient.h"

// Use the standard namespace for C++ (std)
using namespace std;

// Definition of the DynamicQueue class
class DynamicQueue {
    private:
        // Pointer to an array of Patient objects to represent the queue
        Patient *queueArray;

        // Size of the queue
        int size;

        // Front and rear indices of the queue
        int front;
        int rear;

        // Number of items in the queue
        int numItems;

    public:
        // Default constructor for the DynamicQueue class
        DynamicQueue();

        // Parameterized constructor for the DynamicQueue class
        DynamicQueue(int);

        // Destructor for the DynamicQueue class
        ~DynamicQueue();

        // Function to count the number of items in the queue
        int count();

        // Function to enqueue a Patient object into the queue
        void enQueue(const Patient &);

        // Function to dequeue a Patient object from the queue
        void deQueue(Patient &);

        // Function to check if the queue is empty
        bool isEmpty() const;

        // Function to check if the queue is full
        bool isFull() const;

        // Function to clear the contents of the queue
        void clear();
};

// End of the header guard
#endif

