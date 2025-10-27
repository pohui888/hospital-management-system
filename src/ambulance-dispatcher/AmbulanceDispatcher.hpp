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
    void registerAmbulance(const Ambulance &a);
    void rotateShift();
    void displaySchedule() const;
    void saveToFile(const string &filename) const;
    void loadFromFile(const string &filename);
    void run();
};

#endif
