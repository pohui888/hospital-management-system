#include "PatientFunction.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
#include <limits>
#include <iomanip>

// Constructor
PatientFunction::PatientFunction(const std::string &filePath)
    : filePath(filePath), nextPatientId(1) {
    patientQueue = new Queue();
    loadFromFile();
}

// Destructor
PatientFunction::~PatientFunction() {
    saveAllToFile();
    delete patientQueue;
}

// Generate next patient ID
int PatientFunction::generatePatientId() {
    return nextPatientId++;
}

// Load patients from file
void PatientFunction::loadFromFile() {
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) return;

    std::string line;
    while (getline(inFile, line)) {
        std::stringstream ss(line);
        std::string idStr, name, condition, status, date, time;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, condition, ',');
        getline(ss, status, ',');
        getline(ss, date, ',');
        getline(ss, time, ',');

        PatientAdmission p(stoi(idStr), name, condition, status, date, time);
        patientQueue->enqueue(p);

        if (p.getId() >= nextPatientId)
            nextPatientId = p.getId() + 1;
    }

    inFile.close();
}

// Save last patient
void PatientFunction::saveToFile() {
    std::ofstream outFile(filePath, std::ios::app);
    if (!outFile.is_open()) return;

    if (patientQueue->size() > 0) {
        PatientAdmission &p = patientQueue->at(patientQueue->size() - 1);
        outFile << p.toString() << "\n";
    }

    outFile.close();
}

// Save all patients
void PatientFunction::saveAllToFile() {
    std::ofstream outFile(filePath, std::ios::out);
    if (!outFile.is_open()) return;

    int qSize = patientQueue->size();
    for (int i = 0; i < qSize; ++i) {
        PatientAdmission &p = patientQueue->at(i);
        outFile << p.toString() << "\n";
    }

    outFile.close();
}

// Register new patient
void PatientFunction::registerPatient(const std::string &name, const std::string &condition) {
    PatientAdmission newPatient(generatePatientId(), name, condition, "Treatment", "NULL", "NULL");
    patientQueue->enqueue(newPatient);
    saveToFile();

    std::cout << "Patient registered: ID = " << newPatient.getId() << "\n";
}

// Admit patient
void PatientFunction::admitPatient(int id) {
    int qSize = patientQueue->size();
    bool found = false;

    for (int i = 0; i < qSize; ++i) {
        PatientAdmission &p = patientQueue->at(i);
        if (p.getId() == id) {
            found = true;
            if (p.getStatus() == "Admitted") {
                std::cout << "Patient already admitted.\n";
                return;
            }

            time_t now = time(0);
            tm *ltm = localtime(&now);
            char dateBuf[11], timeBuf[9];
            strftime(dateBuf, sizeof(dateBuf), "%Y-%m-%d", ltm);
            strftime(timeBuf, sizeof(timeBuf), "%H:%M:%S", ltm);

            p.setStatus("Admitted");
            p.setDate(dateBuf);
            p.setTime(timeBuf);

            saveAllToFile();
            std::cout << "Patient admitted successfully.\n";
            return;
        }
    }

    if (!found) std::cout << "Patient ID not found.\n";
}

// Discharge patient
PatientAdmission PatientFunction::dischargePatient() {
    PatientAdmission discharged = patientQueue->dequeue();
    if (discharged.getStatus() == "") { 
        return discharged;
    }

    saveAllToFile();
    std::cout << "Discharged patient ID: " << discharged.getId() << "\n";
    return discharged;
}

// View all patients
void PatientFunction::viewPatientQueue() const {
    patientQueue->viewQueue();
}

// Get patient count
int PatientFunction::getPatientCount() const {
    return patientQueue->size();
}

void PatientFunction::run() {
    int choice;

    do {
        std::cout << "\n===== Patient Management Menu =====\n";
        std::cout << "1. Register Patient\n";
        std::cout << "2. Admit Patient\n";
        std::cout << "3. Discharge Patient\n";
        std::cout << "4. View All Patients\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Handle invalid input
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch(choice) {
            case 1: {
                std::cin.ignore(); // ignore leftover newline
                std::string name, condition;
                std::cout << "Enter patient name: ";
                getline(std::cin, name);
                std::cout << "Enter patient condition: ";
                getline(std::cin, condition);
                registerPatient(name, condition);
                break;
            }
            case 2: {
                int id;
                std::cout << "Enter patient ID to admit: ";
                std::cin >> id;
                admitPatient(id);
                break;
            }
            case 3: {
                dischargePatient();
                break;
            }
            case 4: {
                viewPatientQueue();
                break;
            }
            case 5: {
                std::cout << "Exiting patient menu.\n";
                break;
            }
            default:
                std::cout << "Invalid choice! Please select 1-5.\n";
        }

    } while (choice != 5);
}
