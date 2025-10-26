#ifndef EMERGENCY_CASE_HPP
#define EMERGENCY_CASE_HPP

#include <string>

class EmergencyCase
{
private:
    std::string caseID;
    std::string patientName;
    std::string emergencyType;
    int priorityLevel; // 1 = Critical, 5 = Non-urgent
    std::string timestamp;

public:
    // Constructors
    EmergencyCase();
    EmergencyCase(std::string id, std::string name, std::string type,
                  int priority, std::string time);

    // Getters
    std::string getCaseID() const;
    std::string getPatientName() const;
    std::string getEmergencyType() const;
    int getPriorityLevel() const;
    std::string getTimestamp() const;

    // Setters
    void setCaseID(const std::string &id);
    void setPatientName(const std::string &name);
    void setEmergencyType(const std::string &type);
    void setPriorityLevel(int priority);
    void setTimestamp(const std::string &time);

    // Comparison operator for priority queue
    bool operator<(const EmergencyCase &other) const;
    bool operator>(const EmergencyCase &other) const;

    // Display
    void display() const;
    std::string toString() const;
};

#endif