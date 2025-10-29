#include "PatientAdmission.hpp"
#include <sstream>

// Constructors
PatientAdmission::PatientAdmission()
    : id(0), name(""), condition(""), status(""), date(""), time("") {}

PatientAdmission::PatientAdmission(int id, const std::string &name, const std::string &condition,
                                   const std::string &status, const std::string &date, const std::string &time)
    : id(id), name(name), condition(condition), status(status), date(date), time(time) {}

// Getters
int PatientAdmission::getId() const { return id; }
std::string PatientAdmission::getName() const { return name; }
std::string PatientAdmission::getCondition() const { return condition; }
std::string PatientAdmission::getStatus() const { return status; }
std::string PatientAdmission::getDate() const { return date; }
std::string PatientAdmission::getTime() const { return time; }

// Setters
void PatientAdmission::setId(int value) { id = value; }
void PatientAdmission::setName(const std::string &value) { name = value; }
void PatientAdmission::setCondition(const std::string &value) { condition = value; }
void PatientAdmission::setStatus(const std::string &value) { status = value; }
void PatientAdmission::setDate(const std::string &value) { date = value; }
void PatientAdmission::setTime(const std::string &value) { time = value; }

// Utility
std::string PatientAdmission::toString() const {
    std::stringstream ss;
    ss << id << "," << name << "," << condition << "," << status << "," << date << "," << time;
    return ss.str();
}
