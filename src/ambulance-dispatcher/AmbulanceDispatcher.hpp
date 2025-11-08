#ifndef AMBULANCEDISPATCHER_HPP
#define AMBULANCEDISPATCHER_HPP

#include "CircularQueue.hpp"
#include "Ambulance.hpp"
#include <string>
using namespace std;

class AmbulanceDispatcher
{
private:
    CircularQueue ambulanceQueue;
    string dataFile;

public:
    AmbulanceDispatcher();
    AmbulanceDispatcher(const string &filename);

    string trim(const string &str);
    string formatAmbulanceID(int id);
    int getNextAmbulanceID();
    int getDriverID(const string &driverName);
    void addAmbulanceToInactive();
    bool checkDriverExists(const string &driverName);
    void removeDriverFromInactive(const string &driverName);
    void registerAmbulance();
    void rotateShift();
    void displaySchedule() const;
    void saveToFile() const;
    void loadFromFile(const string &filename);
    void run();
};

#endif
