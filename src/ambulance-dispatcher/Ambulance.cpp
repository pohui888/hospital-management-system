#include "Ambulance.hpp"
using namespace std;

Ambulance::Ambulance() : id(0), driverName(""), onDuty(false), timeStamp("") {}

Ambulance::Ambulance(int id, const string &driverName)
    : id(id), driverName(driverName), onDuty(false), timeStamp("") {}

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

void Ambulance::setTimeStamp(const string &timeStamp)
{
    this->timeStamp = timeStamp;
}
