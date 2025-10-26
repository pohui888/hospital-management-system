#ifndef EMERGENCY_DEPARTMENT_HPP
#define EMERGENCY_DEPARTMENT_HPP

#include "PriorityQueue.hpp"
#include <string>

class EmergencyDepartment
{
private:
    PriorityQueue *emergencyQueue;
    std::string dataFilePath;
    int nextCaseNumber;

    // Helper functions
    std::string generateCaseID();
    std::string getCurrentTimestamp();
    void loadFromFile();
    void saveToFile();
    std::string trim(const std::string &str);

public:
    // Constructor and Destructor
    EmergencyDepartment(const std::string &filePath = "../../data/emergency_cases.txt");
    ~EmergencyDepartment();

    // Core functionalities (as per assignment)
    void logEmergencyCase();          // Functionality 1
    void processMostCriticalCase();   // Functionality 2
    void viewPendingEmergencyCases(); // Functionality 3

    // Menu system
    void displayMenu();
    void run();

    // Utility
    int getCaseCount() const;
};

#endif