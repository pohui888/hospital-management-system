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

bool CircularQueue::allCompletedHours() const
{
    if (isEmpty())
        return false;

    for (int i = 0; i < count; i++)
    {
        int idx = (front + i) % capacity;
        if (arr[idx].getWorkingHours() < 8.0f)
            return false;
    }
    return true;
}

void CircularQueue::rotateDuty()
{
    if (isEmpty())
    {
        cout << "No ambulances to rotate.\n";
        return;
    }

    // If all ambulances already hit their allocated hours, rotation locked
    if (allCompletedHours())
    {
        cout << "All ambulances have completed their working hours. "
             << "Rotation locked until next day.\n";
        return;
    }

    // Current ambulance at front
    int currentIndex = front;
    Ambulance &current = arr[currentIndex];
    string shift = current.getShiftMode();

    // Count how many ambulances are in this shift
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

    // Hours allocated per ambulance in this shift
    float hoursPerAmbulance = 8.0f / shiftCount;

    // ADD hours to current ambulance
    float newHours = current.getWorkingHours() + hoursPerAmbulance;
    current.setWorkingHours(newHours > hoursPerAmbulance ? hoursPerAmbulance : newHours);

    // Set current to OffDuty
    current.setDutyStatus(false);

    // CHECK NEXT AMBULANCE BEFORE ROTATING
    int nextIndex = (front + 1) % capacity;
    Ambulance &nextAmb = arr[nextIndex];

    // If next ambulance has completed its allocated hours, STOP
    if (nextAmb.getWorkingHours() >= hoursPerAmbulance)
    {
        cout << "Next ambulance (ID: " << nextAmb.getId()
             << ") has completed its allocated working hours. Rotation stopped.\n";
        return;
    }

    // Move current to back
    Ambulance finished = current;
    dequeue();
    enqueue(finished);

    // Activate next ambulance
    nextAmb.setDutyStatus(true);

    cout << fixed << setprecision(2)
         << "Ambulance " << nextAmb.getId() << " ("
         << nextAmb.getDriverName()
         << ") is now OnDuty. Working Hours = "
         << nextAmb.getWorkingHours() << "\n";
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
