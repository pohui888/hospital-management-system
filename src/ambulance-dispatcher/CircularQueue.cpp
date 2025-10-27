#include "CircularQueue.hpp"
#include <stdexcept>
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
        return;

    rotate();

    // Set duty status
    for (int i = 0; i < count; i++)
    {
        int index = (front + i) % capacity;
        if (i == 0)
            arr[index].setDutyStatus(true); // front is OnDuty
        else
            arr[index].setDutyStatus(false); // others OffDuty
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
    for (int i = 0; i < count; i++)
    {
        int index = (front + i) % capacity;
        const Ambulance &ambulance = arr[index];

        cout << "- Ambulance ID: " << ambulance.getId()
             << ", Driver: " << ambulance.getDriverName()
             << ", Status: " << (ambulance.getDutyStatus() ? "OnDuty" : "OffDuty")
             << ", TimeStamp: " << ambulance.getTimeStamp() << "\n";
    }
}
