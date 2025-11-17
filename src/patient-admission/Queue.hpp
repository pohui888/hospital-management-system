#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include "PatientAdmission.hpp"
using namespace std;

class Queue {
private:
    static const int MAX_SIZE = 100;
    PatientAdmission patients[MAX_SIZE];
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
