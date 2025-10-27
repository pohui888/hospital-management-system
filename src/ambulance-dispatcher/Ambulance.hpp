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
    string timeStamp;

public:
    Ambulance();
    Ambulance(int id, const string &driverName);

    // Getters
    int getId() const;
    string getDriverName() const;
    bool getDutyStatus() const;
    string getTimeStamp() const;

    // Setters
    void setId(int id);
    void setDriverName(const string &driverName);
    void setDutyStatus(bool status);
    void setTimeStamp(const string &timeStamp);
};

#endif
