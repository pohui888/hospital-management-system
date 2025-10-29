#include "Queue.hpp"

Queue::Queue() : front(0), rear(0) {}

bool Queue::isEmpty() const {
    return front == rear;
}

bool Queue::isFull() const {
    return (rear + 1) % MAX_SIZE == front;
}

int Queue::size() const {
    return (rear - front + MAX_SIZE) % MAX_SIZE;
}

PatientAdmission& Queue::at(int index) {
    return patients[(front + index) % MAX_SIZE];
}

void Queue::enqueue(const PatientAdmission &p) {
    if (isFull()) {
        cout << "\nQueue full! Cannot add patient.\n";
        return;
    }
    patients[rear] = p;
    rear = (rear + 1) % MAX_SIZE;
}

PatientAdmission Queue::dequeue() {
    if (isEmpty()) {
        std::cout << "\nQueue empty! No admitted patients to remove.\n";
        return PatientAdmission();
    }

    int qSize = size();
    int targetIndex = -1;

    // Find the admitted patient with the earliest admission datetime
    for (int i = 0; i < qSize; ++i) {
        int idx = (front + i) % MAX_SIZE;
        PatientAdmission &p = patients[idx];
        if (p.getStatus() == "Admitted") {
            if (targetIndex == -1) {
                targetIndex = idx;
            } else {
                // Compare date & time
                std::string currentDT = p.getDate() + " " + p.getTime();
                std::string targetDT = patients[targetIndex].getDate() + " " + patients[targetIndex].getTime();
                if (currentDT < targetDT) {
                    targetIndex = idx;
                }
            }
        }
    }

    if (targetIndex == -1) {
        std::cout << "\nNo admitted patients to discharge.\n";
        return PatientAdmission();
    }

    PatientAdmission discharged = patients[targetIndex];

    // Shift remaining patients to remove the discharged one
    int i = targetIndex;
    while (i != rear) {
        int next = (i + 1) % MAX_SIZE;
        patients[i] = patients[next];
        i = next;
    }

    rear = (rear - 1 + MAX_SIZE) % MAX_SIZE;

    return discharged;
}

void Queue::viewQueue() const {
    if (isEmpty()) {
        cout << "\nNo patients in the queue.\n";
        return;
    }

    cout << "\n===== Patient Queue =====\n";
    int qSize = size();
    for (int i = 0; i < qSize; ++i) {
        int idx = (front + i) % MAX_SIZE;
        const PatientAdmission &p = patients[idx];
        cout << p.getId() << ". " << p.getName()
             << " | Condition: " << p.getCondition()
             << " | Status: " << p.getStatus()
             << " | Date: " << p.getDate()
             << " | Time: " << p.getTime() << "\n";
    }
    cout << "========================\n";
}
