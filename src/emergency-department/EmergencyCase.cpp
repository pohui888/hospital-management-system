#include "EmergencyCase.hpp"
#include <iostream>
#include <iomanip>

// Default constructor
EmergencyCase::EmergencyCase()
    : caseID(""), patientName(""), emergencyType(""),
      priorityLevel(5), timestamp("") {}

// Parameterized constructor
EmergencyCase::EmergencyCase(std::string id, std::string name,
                             std::string type, int priority, std::string time)
    : caseID(id), patientName(name), emergencyType(type),
      priorityLevel(priority), timestamp(time) {}

// Getters
std::string EmergencyCase::getCaseID() const { return caseID; }
std::string EmergencyCase::getPatientName() const { return patientName; }
std::string EmergencyCase::getEmergencyType() const { return emergencyType; }
int EmergencyCase::getPriorityLevel() const { return priorityLevel; }
std::string EmergencyCase::getTimestamp() const { return timestamp; }

// Setters
void EmergencyCase::setCaseID(const std::string &id) { caseID = id; }
void EmergencyCase::setPatientName(const std::string &name) { patientName = name; }
void EmergencyCase::setEmergencyType(const std::string &type) { emergencyType = type; }
void EmergencyCase::setPriorityLevel(int priority) { priorityLevel = priority; }
void EmergencyCase::setTimestamp(const std::string &time) { timestamp = time; }

// Comparison operators (lower priority number = higher priority)
bool EmergencyCase::operator<(const EmergencyCase &other) const
{
    if (priorityLevel != other.priorityLevel)
    {
        return priorityLevel < other.priorityLevel;
    }
    // If same priority, earlier timestamp has higher priority
    return timestamp < other.timestamp;
}

bool EmergencyCase::operator>(const EmergencyCase &other) const
{
    if (priorityLevel != other.priorityLevel)
    {
        return priorityLevel > other.priorityLevel;
    }
    return timestamp > other.timestamp;
}

// Display case details
void EmergencyCase::display() const
{
    std::cout << std::left
              << std::setw(12) << caseID
              << std::setw(25) << patientName
              << std::setw(25) << emergencyType
              << std::setw(10) << priorityLevel
              << std::setw(20) << timestamp << std::endl;
}

// Convert to string for file writing
std::string EmergencyCase::toString() const
{
    return caseID + "," + patientName + "," + emergencyType + "," + std::to_string(priorityLevel) + "," + timestamp;
}