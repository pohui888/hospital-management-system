#include "Ambulance.hpp"
using namespace std;

Ambulance::Ambulance() : id(0), driverName(""), onDuty(false), shiftMode(""), workingHours(0.00), timeStamp("") {}

Ambulance::Ambulance(int id, const string &driverName)
    : id(id), driverName(driverName), onDuty(false), shiftMode(""), workingHours(0.00), timeStamp("") {}

int Ambulance::getId() const
{
    return id;
}

string Ambulance::getDriverName() const
{
    return driverName;
}

bool Ambulance::getDutyStatus() const
{
    return onDuty;
}

string Ambulance::getShiftMode() const
{
    return shiftMode;
}

float Ambulance::getWorkingHours() const
{
    return workingHours;
}

string Ambulance::getTimeStamp() const
{
    return timeStamp;
}

void Ambulance::setId(int id)
{
    this->id = id;
}

void Ambulance::setDriverName(const string &driverName)
{
    this->driverName = driverName;
}

void Ambulance::setDutyStatus(bool status)
{
    this->onDuty = status;
}

void Ambulance::setShiftMode(const string &shiftMode)
{
    this->shiftMode = shiftMode;
}

void Ambulance::setWorkingHours(const float &hours)
{
    this->workingHours = hours;
}

void Ambulance::setTimeStamp(const string &timeStamp)
{
    this->timeStamp = timeStamp;
}
