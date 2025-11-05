#include "AmbulanceDispatcher.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>
#include <iomanip>
using namespace std;

AmbulanceDispatcher::AmbulanceDispatcher() : ambulanceQueue(10) {}

AmbulanceDispatcher::AmbulanceDispatcher(const string &filename)
    : ambulanceQueue(10), dataFile(filename)
{
    loadFromFile(filename);
}

string AmbulanceDispatcher::trim(const string &str)
{
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

string AmbulanceDispatcher::formatAmbulanceID(int id)
{
    ostringstream oss;
    oss << "A" << setw(3) << setfill('0') << id;
    return oss.str();
}

string getCurrentTime()
{
    time_t now = time(nullptr);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buf);
}

void AmbulanceDispatcher::registerAmbulance(const Ambulance &ambulance)
{
    try
    {
        Ambulance newAmbulance = ambulance;
        newAmbulance.setTimeStamp(getCurrentTime());
        ambulanceQueue.enqueue(newAmbulance);
        cout << "Ambulance registered successfully.\n";

        if (!dataFile.empty())
            saveToFile(dataFile);
    }
    catch (const exception &e)
    {
        cerr << e.what() << "\n";
    }
}

void AmbulanceDispatcher::rotateShift()
{
    try
    {
        ambulanceQueue.rotateDuty();
        cout << "Ambulance shift rotated successfully.\n";

        if (!dataFile.empty())
            saveToFile(dataFile);
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << "\n";
    }
}

void AmbulanceDispatcher::displaySchedule() const
{
    ambulanceQueue.display();
}

void AmbulanceDispatcher::loadFromFile(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
        return;

    string line;
    getline(file, line); // skip header

    while (getline(file, line))
    {
        stringstream ss(line);
        string idStr, name, status, timestamp;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, status, ',');
        getline(ss, timestamp, ',');

        if (!idStr.empty() && !name.empty())
        {
            Ambulance ambulance(stoi(idStr), name);
            ambulance.setDutyStatus(status == "OnDuty");
            ambulance.setTimeStamp(timestamp);
            ambulanceQueue.enqueue(ambulance);
        }
    }

    file.close();
}

void AmbulanceDispatcher::saveToFile(const string &filename) const
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Unable to save data to file!\n";
        return;
    }

    file << "AmbulanceID,DriverName,Status,TimeStamp\n";

    int size = ambulanceQueue.getSize();
    Ambulance *ambulances = new Ambulance[size];
    int actualSize = 0;
    ambulanceQueue.getAllAmbulances(ambulances, actualSize);

    for (int i = 0; i < actualSize; i++)
    {
        file << ambulances[i].getId() << ","
             << ambulances[i].getDriverName() << ","
             << (ambulances[i].getDutyStatus() ? "OnDuty" : "OffDuty") << ","
             << ambulances[i].getTimeStamp() << "\n";
    }

    delete[] ambulances;
    file.close();
}

void AmbulanceDispatcher::run()
{
    int choice;
    do
    {
        cout << "\n";
        cout << "╔══════════════════════════════════════════════════════╗\n";
        cout << "║             AMBULANCE DISPATCHER MENU                ║\n";
        cout << "╚══════════════════════════════════════════════════════╝\n";
        cout << "1. Register Ambulance\n";
        cout << "2. Rotate Shift\n";
        cout << "3. Display Schedule\n";
        cout << "4. Exit to Main Menu\n";
        cout << "Enter your choice: ";
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        }
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            string driver;
            int newId = ambulanceQueue.getSize() + 1;
            string formatted = formatAmbulanceID(newId);
            cout << "Generated Ambulance ID: " << formatted << "\n";
            cout << "Enter Driver Name: ";
            getline(cin, driver);
            registerAmbulance(Ambulance(newId, driver));
            break;
        }
        case 2:
            rotateShift();
            break;
        case 3:
            displaySchedule();
            break;
        case 4:
            saveToFile(dataFile);
            cout << "Returning to main menu...\n";
            break;
        default:
            cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 4);
}
