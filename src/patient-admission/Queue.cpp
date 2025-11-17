#include "Queue.hpp"

Queue::Queue() : front(0), rear(0) {}

bool Queue::isEmpty() const {
    return front == rear;
}

bool Queue::isFull() const {
    return rear == MAX_SIZE;
}

int Queue::size() const {
    return rear - front;
}

PatientAdmission& Queue::at(int index) {
    return patients[front + index];
}

void Queue::enqueue(const PatientAdmission &p) {
    if (isFull()) {
        cout << "\nQueue full! Cannot add patient.\n";
        return;
    }
    patients[rear] = p;
    rear++;
}

PatientAdmission Queue::dequeue() {
    if (isEmpty()) {
        cout << "\nQueue empty! No admitted patients to remove.\n";
        return PatientAdmission();
    }

    int qSize = size();
    int targetIndex = -1;

    // Find earliest admitted patient
    for (int i = 0; i < qSize; ++i) {
        PatientAdmission &p = patients[front + i];
        if (p.getStatus() == "Admitted") {
            if (targetIndex == -1) {
                targetIndex = front + i;
            } else {
                string currentDT = p.getDate() + " " + p.getTime();
                string targetDT = patients[targetIndex].getDate() + " " +
                                  patients[targetIndex].getTime();
                if (currentDT < targetDT) {
                    targetIndex = front + i;
                }
            }
        }
    }

    if (targetIndex == -1) {
        cout << "\nNo admitted patients to discharge.\n";
        return PatientAdmission();
    }

    PatientAdmission discharged = patients[targetIndex];

    for (int i = targetIndex; i < rear - 1; i++) {
        patients[i] = patients[i + 1];
    }

    rear--; 

    return discharged;
}

void Queue::viewQueue() const {
    if (isEmpty()) {
        cout << "\nNo patients in the queue.\n";
        return;
    }

    cout << "\n===== Patient Queue =====\n";
    for (int i = front; i < rear; ++i) {
        const PatientAdmission &p = patients[i];
        cout << p.getId() << ". " << p.getName()
             << " | Condition: " << p.getCondition()
             << " | Status: " << p.getStatus()
             << " | Date: " << p.getDate()
             << " | Time: " << p.getTime() << "\n";
    }
    cout << "========================\n";
}
