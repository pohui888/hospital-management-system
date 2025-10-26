#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include "EmergencyCase.hpp"

class PriorityQueue
{
private:
    EmergencyCase *heap;
    int capacity;
    int size;

    // Helper functions for heap operations
    int parent(int i) const;
    int leftChild(int i) const;
    int rightChild(int i) const;

    void heapifyUp(int index);
    void heapifyDown(int index);
    void resize();

public:
    // Constructor and Destructor
    PriorityQueue(int cap = 100);
    ~PriorityQueue();

    // Core operations
    void insert(const EmergencyCase &emergencyCase);
    EmergencyCase extractMin(); // Get and remove highest priority case
    EmergencyCase peek() const; // View highest priority case without removing

    // Utility functions
    bool isEmpty() const;
    bool isFull() const;
    int getSize() const;
    void clear();

    // Display all cases
    void displayAll() const;

    // Get all cases as array
    EmergencyCase *getAllCases() const;
};

#endif