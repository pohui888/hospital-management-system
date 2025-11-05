#ifndef PATIENT_ADMISSION_HPP
#define PATIENT_ADMISSION_HPP

#include <string>

class PatientAdmission {
private:
    int id;
    std::string name;
    std::string condition;
    std::string status;
    std::string date;
    std::string time;

public:
    // Constructors
    PatientAdmission(); // declaration only
    PatientAdmission(int id, const std::string &name, const std::string &condition,
                     const std::string &status, const std::string &date, const std::string &time);

    // Getters
    int getId() const;
    std::string getName() const;
    std::string getCondition() const;
    std::string getStatus() const;
    std::string getDate() const;
    std::string getTime() const;

    // Setters
    void setId(int value);
    void setName(const std::string &value);
    void setCondition(const std::string &value);
    void setStatus(const std::string &value);
    void setDate(const std::string &value);
    void setTime(const std::string &value);

    // Utility
    std::string toString() const;
};

#endif
