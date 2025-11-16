#include "PriorityQueue.hpp"
#include <iostream>
#include <stdexcept>
#include <iomanip>

// Constructor
PriorityQueue::PriorityQueue(int cap) : capacity(cap), size(0)
{
    heap = new EmergencyCase[capacity];
}

// Destructor
PriorityQueue::~PriorityQueue()
{
    delete[] heap;
}

// Helper functions
int PriorityQueue::parent(int i) const
{
    return (i - 1) / 2;
}

int PriorityQueue::leftChild(int i) const
{
    return 2 * i + 1;
}

int PriorityQueue::rightChild(int i) const
{
    return 2 * i + 2;
}

// Heapify up (used after insertion)
void PriorityQueue::heapifyUp(int index)
{
    while (index > 0 && heap[index] < heap[parent(index)])
    {
        // Swap with parent
        EmergencyCase temp = heap[index];
        heap[index] = heap[parent(index)];
        heap[parent(index)] = temp;
        index = parent(index);
    }
}

// Heapify down (used after extraction)
void PriorityQueue::heapifyDown(int index)
{
    int minIndex = index;
    int left = leftChild(index);
    int right = rightChild(index);

    if (left < size && heap[left] < heap[minIndex])
    {
        minIndex = left;
    }

    if (right < size && heap[right] < heap[minIndex])
    {
        minIndex = right;
    }

    if (minIndex != index)
    {
        // Swap
        EmergencyCase temp = heap[index];
        heap[index] = heap[minIndex];
        heap[minIndex] = temp;
        heapifyDown(minIndex);
    }
}

// Resize array when full
void PriorityQueue::resize()
{
    capacity *= 2;
    EmergencyCase *newHeap = new EmergencyCase[capacity];
    for (int i = 0; i < size; i++)
    {
        newHeap[i] = heap[i];
    }
    delete[] heap;
    heap = newHeap;
}

// Insert new emergency case
void PriorityQueue::insert(const EmergencyCase &emergencyCase)
{
    if (size >= capacity)
    {
        resize();
    }

    heap[size] = emergencyCase;
    heapifyUp(size);
    size++;
}

// Private helper: Extract minimum for heap sort (internal use only)
EmergencyCase PriorityQueue::extractMin()
{
    if (isEmpty())
    {
        throw std::runtime_error("Priority Queue is empty!");
    }

    EmergencyCase minCase = heap[0];
    heap[0] = heap[size - 1];
    size--;

    if (size > 0)
    {
        heapifyDown(0);
    }

    return minCase;
}

// Find most critical pending case (don't remove)
EmergencyCase *PriorityQueue::findMostCriticalPending()
{
    if (isEmpty())
    {
        return nullptr;
    }

    // Find first pending case (should be at or near root due to sorting)
    for (int i = 0; i < size; i++)
    {
        if (heap[i].getStatus() == "Pending")
        {
            return &heap[i];
        }
    }

    return nullptr; // No pending cases
}

// Mark a case as completed
void PriorityQueue::markAsCompleted(const std::string &caseID)
{
    for (int i = 0; i < size; i++)
    {
        if (heap[i].getCaseID() == caseID)
        {
            heap[i].setStatus("Completed");

            // Re-heapify to move completed case down
            heapifyDown(i);
            return;
        }
    }
}

// Peek at highest priority case without removing
EmergencyCase PriorityQueue::peek() const
{
    if (isEmpty())
    {
        throw std::runtime_error("Priority Queue is empty!");
    }
    return heap[0];
}

// Check if queue is empty
bool PriorityQueue::isEmpty() const
{
    return size == 0;
}

// Check if queue is full
bool PriorityQueue::isFull() const
{
    return size >= capacity;
}

// Get current size
int PriorityQueue::getSize() const
{
    return size;
}

// Get count of pending cases
int PriorityQueue::getPendingCount() const
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (heap[i].getStatus() == "Pending")
        {
            count++;
        }
    }
    return count;
}

// Get count of completed cases
int PriorityQueue::getCompletedCount() const
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (heap[i].getStatus() == "Completed")
        {
            count++;
        }
    }
    return count;
}

// Clear all cases
void PriorityQueue::clear()
{
    size = 0;
}

// Display all cases sorted by status and priority using HEAP SORT
void PriorityQueue::displayAll() const
{
    if (isEmpty())
    {
        std::cout << "No emergency cases.\n";
        return;
    }

    std::cout << "\n"
              << std::string(112, '=') << std::endl;
    std::cout << "ALL EMERGENCY CASES (Sorted by Status and Priority)\n";
    std::cout << std::string(112, '=') << std::endl;
    std::cout << std::left
              << std::setw(12) << "Case ID"
              << std::setw(25) << "Patient Name"
              << std::setw(25) << "Emergency Type"
              << std::setw(10) << "Priority"
              << std::setw(12) << "Status"
              << std::setw(20) << "Timestamp" << std::endl;
    std::cout << std::string(112, '-') << std::endl;

    // HEAP SORT APPROACH:
    // Create a temporary priority queue (min-heap)
    PriorityQueue *tempQueue = new PriorityQueue(capacity);

    // Insert all cases into temp queue
    // The heap will automatically organize them
    for (int i = 0; i < size; i++)
    {
        tempQueue->insert(heap[i]);
    }

    // Extract min repeatedly - this gives sorted order!
    // Each extractMin removes the smallest (highest priority) element
    while (!tempQueue->isEmpty())
    {
        EmergencyCase case_ = tempQueue->extractMin();
        case_.display();
    }

    delete tempQueue;

    std::cout << std::string(112, '=') << std::endl;
    std::cout << "Total cases: " << size
              << " (Pending: " << getPendingCount()
              << ", Completed: " << getCompletedCount() << ")" << std::endl;
}

// Get all cases as array
EmergencyCase *PriorityQueue::getAllCases() const
{
    return heap;
}