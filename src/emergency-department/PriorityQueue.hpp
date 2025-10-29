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

    // Private helper for heap sort (internal use only)
    EmergencyCase extractMin();

public:
    // Constructor and Destructor
    PriorityQueue(int cap = 100);
    ~PriorityQueue();

    // Core operations
    void insert(const EmergencyCase &emergencyCase);
    EmergencyCase *findMostCriticalPending();        // Find but don't remove
    void markAsCompleted(const std::string &caseID); // Mark status as completed
    EmergencyCase peek() const;                      // View highest priority case without removing

    // Utility functions
    bool isEmpty() const;
    bool isFull() const;
    int getSize() const;
    int getPendingCount() const;   // Count only pending cases
    int getCompletedCount() const; // Count completed cases
    void clear();

    // Display all cases
    void displayAll() const;

    // Get all cases as array (for file operations)
    EmergencyCase *getAllCases() const;
};

#endif