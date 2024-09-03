// Include necessary libraries for input/output and the DynamicQueue and Patient header files
#include <iostream>
#include "DynamicQueue.h"
#include "Patient.h"

// Use the standard namespace for C++ (std)
using namespace std;

// Default constructor for the DynamicQueue class
DynamicQueue::DynamicQueue() {
    // Set the default size of the queue to 10
    size = 10;

    // Create an array of Patient objects to represent the queue
    queueArray = new Patient[size];

    // Initialize front and rear indices for an empty queue
    front = rear = -1;

    // Initialize the number of items in the queue
    numItems = 0;
}

// Parameterized constructor for the DynamicQueue class
DynamicQueue::DynamicQueue(int size) {
    // Set the size of the queue based on the provided parameter
    this->size = size;

    // Create an array of Patient objects to represent the queue
    queueArray = new Patient[size];

    // Initialize front and rear indices for an empty queue
    front = rear = -1;

    // Initialize the number of items in the queue
    numItems = 0;
}

// Destructor for the DynamicQueue class
DynamicQueue::~DynamicQueue() {
    // Deallocate the memory used by the queue array
    delete[] queueArray;
}

// Function to count the number of items in the queue
int DynamicQueue::count() {
    return numItems;
}

// Function to check if the queue is empty
bool DynamicQueue::isEmpty() const {
    return numItems == 0;
}

// Function to check if the queue is full
bool DynamicQueue::isFull() const {
    return numItems == size;
}

// Function to enqueue a Patient object into the queue
void DynamicQueue::enQueue(const Patient &patient) {
    // Check if the queue is full
    if (isFull()) {
        cout << "The queue is full!" << endl;
    } else {
        // Update the rear index and enqueue the patient
        rear = (rear + 1) % size;
        queueArray[rear] = patient;

        // Increment the number of items in the queue
        numItems++;
    }
}

// Function to dequeue a Patient object from the queue
void DynamicQueue::deQueue(Patient &patient) {
    // Check if the queue is empty
    if (isEmpty()) {
        cout << "The queue is empty!" << endl;
    } else {
        // Update the front index and dequeue the patient
        front = (front + 1) % size;
        patient = queueArray[front];

        // Decrement the number of items in the queue
        numItems--;
    }
}

// Function to clear the contents of the queue
void DynamicQueue::clear() {
    // Reset the number of items and front and rear indices for an empty queue
    numItems = 0;
    front = rear = -1;
}

