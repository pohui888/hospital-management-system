#ifndef AMBULANCE_HPP
#define AMBULANCE_HPP

#include <string>
using namespace std;

class Ambulance
{
private:
    int id;
    string driverName;
    bool onDuty;
    string shiftMode;
    int workingHours;
    string timeStamp;

public:
    Ambulance();
    Ambulance(int id, const string &driverName);

    // Getters
    int getId() const;
    string getDriverName() const;
    bool getDutyStatus() const;
    string getShiftMode() const;
    float getWorkingHours() const;
    string getTimeStamp() const;

    // Setters
    void setId(int id);
    void setDriverName(const string &driverName);
    void setDutyStatus(bool status);
    void setShiftMode(const string &shiftMode);
    void setWorkingHours(const float &hours);
    void setTimeStamp(const string &timeStamp);
};

#endif
