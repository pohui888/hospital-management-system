#include "EmergencyCase.hpp"
#include <iostream>
#include <iomanip>

// Default constructor
EmergencyCase::EmergencyCase()
    : caseID(""), patientName(""), emergencyType(""),
      priorityLevel(5), timestamp(""), status("Pending") {}

// Parameterized constructor
EmergencyCase::EmergencyCase(std::string id, std::string name,
                             std::string type, int priority, std::string time, std::string stat)
    : caseID(id), patientName(name), emergencyType(type),
      priorityLevel(priority), timestamp(time), status(stat) {}

// Getters
std::string EmergencyCase::getCaseID() const { return caseID; }
std::string EmergencyCase::getPatientName() const { return patientName; }
std::string EmergencyCase::getEmergencyType() const { return emergencyType; }
int EmergencyCase::getPriorityLevel() const { return priorityLevel; }
std::string EmergencyCase::getTimestamp() const { return timestamp; }
std::string EmergencyCase::getStatus() const { return status; }

// Setters
void EmergencyCase::setCaseID(const std::string &id) { caseID = id; }
void EmergencyCase::setPatientName(const std::string &name) { patientName = name; }
void EmergencyCase::setEmergencyType(const std::string &type) { emergencyType = type; }
void EmergencyCase::setPriorityLevel(int priority) { priorityLevel = priority; }
void EmergencyCase::setTimestamp(const std::string &time) { timestamp = time; }
void EmergencyCase::setStatus(const std::string &stat) { status = stat; }

// Comparison operators
// CRITICAL: Pending cases must come BEFORE Completed cases
// Strategy: Pending = 0, Completed = 1 for comparison
bool EmergencyCase::operator<(const EmergencyCase &other) const
{
    // Convert status to numeric value
    // Pending = 0 (comes first), Completed = 1 (comes last)
    int thisStatusValue = (status == "Pending") ? 0 : 1;
    int otherStatusValue = (other.status == "Pending") ? 0 : 1;

    // FIRST: Sort by status (Pending before Completed)
    if (thisStatusValue != otherStatusValue)
    {
        return thisStatusValue < otherStatusValue; // 0 < 1, so Pending comes first
    }

    // SECOND: Within same status, sort by priority level
    if (priorityLevel != other.priorityLevel)
    {
        return priorityLevel < other.priorityLevel;
    }

    // THIRD: If same priority, earlier timestamp has higher priority
    return timestamp < other.timestamp;
}

bool EmergencyCase::operator>(const EmergencyCase &other) const
{
    int thisStatusValue = (status == "Pending") ? 0 : 1;
    int otherStatusValue = (other.status == "Pending") ? 0 : 1;

    if (thisStatusValue != otherStatusValue)
    {
        return thisStatusValue > otherStatusValue;
    }

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
              << std::setw(12) << status
              << std::setw(20) << timestamp << std::endl;
}

// Convert to string for file writing
std::string EmergencyCase::toString() const
{
    return caseID + "," + patientName + "," + emergencyType + "," + std::to_string(priorityLevel) + "," + status + "," + timestamp;
}