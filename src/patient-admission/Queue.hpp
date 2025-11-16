#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include "PatientAdmission.hpp"  // Include the new class
using namespace std;

class Queue {
private:
    static const int MAX_SIZE = 100;
    PatientAdmission patients[MAX_SIZE];  // Use PatientAdmission instead of struct
    int front;
    int rear;

public:
    Queue();

    bool isEmpty() const;
    bool isFull() const;

    void enqueue(const PatientAdmission &p);
    PatientAdmission dequeue();
    void viewQueue() const;

    int size() const;
    PatientAdmission& at(int index);
};

#endif
