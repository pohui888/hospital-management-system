#ifndef CIRCULARQUEUE_HPP
#define CIRCULARQUEUE_HPP

#include "Ambulance.hpp"
#include <iostream>

class CircularQueue
{
private:
    int front;
    int rear;
    int count;
    int capacity;
    Ambulance *arr;

public:
    CircularQueue(int size = 10);
    ~CircularQueue();

    bool isFull() const;
    bool isEmpty() const;
    void enqueue(const Ambulance &a);
    void dequeue();
    void rotate();
    void rotateDuty();
    void clear();
    int getSize() const;
    void getAllAmbulances(Ambulance *outputArr, int &outSize) const;
    void display() const;
    Ambulance peekFront() const;
};

#endif
