#include "CircularQueue.hpp"
#include <stdexcept>
#include <iomanip>
using namespace std;

CircularQueue::CircularQueue(int size)
    : front(0), rear(-1), count(0), capacity(size)
{
    arr = new Ambulance[capacity];
}

CircularQueue::~CircularQueue()
{
    delete[] arr;
}

bool CircularQueue::isFull() const
{
    return count == capacity;
}

bool CircularQueue::isEmpty() const
{
    return count == 0;
}

void CircularQueue::enqueue(const Ambulance &a)
{
    if (isFull())
        throw overflow_error("Queue is full.");
    rear = (rear + 1) % capacity;
    arr[rear] = a;
    count++;
}

void CircularQueue::dequeue()
{
    if (isEmpty())
        throw underflow_error("Queue is empty.");
    front = (front + 1) % capacity;
    count--;
}

Ambulance CircularQueue::peekFront() const
{
    if (isEmpty())
        throw underflow_error("Queue is empty.");
    return arr[front];
}

void CircularQueue::rotate()
{
    if (!isEmpty())
    {
        Ambulance temp = arr[front];
        dequeue();
        enqueue(temp);
    }
}

void CircularQueue::rotateDuty()
{
    if (isEmpty())
    {
        cout << "No ambulances to rotate.\n";
        return;
    }

    Ambulance current = arr[front];
    string shift = current.getShiftMode();

    // Count ambulances in same shift
    int shiftCount = 0;
    for (int i = 0; i < count; i++)
    {
        int idx = (front + i) % capacity;
        if (arr[idx].getShiftMode() == shift)
            shiftCount++;
    }

    if (shiftCount == 0)
    {
        cout << "No ambulances found for shift " << shift << ".\n";
        return;
    }

    float hoursEach = 8.0f / shiftCount;

    // Check if all in this shift have already reached 8 hours
    bool allDone = true;
    for (int i = 0; i < count; i++)
    {
        int idx = (front + i) % capacity;
        if (arr[idx].getShiftMode() == shift && arr[idx].getWorkingHours() < 8.0f)
        {
            allDone = false;
            break;
        }
    }

    if (allDone)
    {
        cout << "Cannot rotate — all ambulances in Shift " << shift << " have completed their 8-hour duty.\n";
        return;
    }

    // Current front ambulance finishes its turn
    current.setDutyStatus(false);
    float newHours = current.getWorkingHours() + hoursEach;
    current.setWorkingHours(newHours > 8.0f ? 8.0f : newHours);

    // Move it to back of queue
    dequeue();
    enqueue(current);

    // Find the next available same-shift ambulance with <8 hours
    int nextIdx = -1;
    for (int i = 0; i < count; i++)
    {
        int idx = (front + i) % capacity;
        if (arr[idx].getShiftMode() == shift && arr[idx].getWorkingHours() < 8.0f)
        {
            nextIdx = idx;
            break;
        }
    }

    if (nextIdx != -1)
    {
        arr[nextIdx].setDutyStatus(true);
        cout << fixed << setprecision(2)
             << "Ambulance " << arr[nextIdx].getId() << " (" << arr[nextIdx].getDriverName()
             << ") is now OnDuty. Working Hours = " << arr[nextIdx].getWorkingHours() << "\n";
    }
    else
    {
        cout << "All ambulances in Shift " << shift << " have reached 8 working hours.\n";
    }
}

void CircularQueue::clear()
{
    front = 0;
    rear = -1;
    count = 0;
}

int CircularQueue::getSize() const
{
    return count;
}

void CircularQueue::getAllAmbulances(Ambulance *outputArr, int &outSize) const
{
    outSize = count;
    for (int i = 0; i < count; i++)
    {
        int index = (front + i) % capacity;
        outputArr[i] = arr[index];
    }
}

void CircularQueue::display() const
{
    if (isEmpty())
    {
        cout << "No ambulances in the schedule.\n";
        return;
    }

    cout << "\n=== Ambulance Rotation Schedule ===\n";
    cout << fixed << setprecision(2);

    for (int i = 0; i < count; i++)
    {
        int index = (front + i) % capacity;
        const Ambulance &ambulance = arr[index];

        cout << "- Ambulance ID: " << ambulance.getId()
             << ", Driver: " << ambulance.getDriverName()
             << ", Status: " << (ambulance.getDutyStatus() ? "OnDuty" : "OffDuty")
             << ", Shift: " << ambulance.getShiftMode()
             << ", Working Hours: " << ambulance.getWorkingHours()
             << ", TimeStamp: " << ambulance.getTimeStamp() << "\n";
    }
}
