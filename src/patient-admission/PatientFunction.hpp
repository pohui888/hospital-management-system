#ifndef PATIENT_FUNCTION_HPP
#define PATIENT_FUNCTION_HPP

// #include "PatientAdmission.hpp"
#include "Queue.hpp"
#include <string>

class PatientFunction {
private:
    Queue *patientQueue;
    std::string filePath;
    int nextPatientId;

    void loadFromFile();
    void saveToFile();
    void saveAllToFile();
    int generatePatientId();

public:
    explicit PatientFunction(const std::string &filePath);
    ~PatientFunction(); // declaration only

    void registerPatient(const std::string &name, const std::string &condition);
    void admitPatient(int id);
    PatientAdmission dischargePatient();
    void viewPatientQueue() const;
    int getPatientCount() const;
    void run();
};

#endif
