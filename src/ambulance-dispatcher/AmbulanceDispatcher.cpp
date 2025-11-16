#include "AmbulanceDispatcher.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>
#include <iomanip>
using namespace std;

AmbulanceDispatcher::AmbulanceDispatcher() : ambulanceQueue(15) {}

AmbulanceDispatcher::AmbulanceDispatcher(const string &filename)
    : ambulanceQueue(15), dataFile(filename)
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

int AmbulanceDispatcher::getNextAmbulanceID()
{
    int maxID = 0;

    // Check active ambulances
    int size = ambulanceQueue.getSize();
    Ambulance *arr = new Ambulance[size];
    int actualSize = 0;
    ambulanceQueue.getAllAmbulances(arr, actualSize);
    for (int i = 0; i < actualSize; i++)
        if (arr[i].getId() > maxID)
            maxID = arr[i].getId();
    delete[] arr;

    // Check inactive file
    ifstream file("data/inactive_duty_ambulance.txt");
    if (file.is_open())
    {
        string line;
        getline(file, line);
        while (getline(file, line))
        {
            stringstream ss(line);
            string idStr;
            getline(ss, idStr, ',');
            if (!idStr.empty())
            {
                int id = stoi(idStr);
                if (id > maxID)
                    maxID = id;
            }
        }
        file.close();
    }

    return maxID + 1;
}

string getCurrentTime()
{
    time_t now = time(nullptr);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buf);
}

void AmbulanceDispatcher::addAmbulanceToInactive()
{
    try
    {
        string driver;
        int newId = getNextAmbulanceID();
        string formatted = formatAmbulanceID(newId);
        cout << "Generated Ambulance ID: " << formatted << "\n";
        cout << "Enter Driver Name: ";
        getline(cin, driver);
        driver = trim(driver);

        // Create new Ambulance object
        Ambulance newAmbulance(newId, driver);
        newAmbulance.setDutyStatus(false);
        newAmbulance.setShiftMode("None");
        newAmbulance.setWorkingHours(0.00);
        newAmbulance.setTimeStamp(getCurrentTime());

        string filePath = "data/inactive_duty_ambulance.txt";
        bool newFile = false;

        {
            ifstream check(filePath);
            if (!check.good() || check.peek() == ifstream::traits_type::eof())
                newFile = true;
        }

        ofstream inactive(filePath, ios::app);
        if (!inactive.is_open())
        {
            cerr << "Error: Unable to open inactive duty ambulance file!\n";
            return;
        }

        if (newFile)
        {
            inactive << "AmbulanceID,DriverName,Status,ShiftMode,WorkingHours,TimeStamp\n";
        }

        inactive << newAmbulance.getId() << ","
                 << newAmbulance.getDriverName() << ","
                 << "OffDuty" << ","
                 << newAmbulance.getShiftMode() << ","
                 << newAmbulance.getWorkingHours() << ","
                 << newAmbulance.getTimeStamp() << "\n";

        cout << "Ambulance added to inactive duty file.\n";
    }
    catch (const exception &e)
    {
        cerr << e.what() << "\n";
    }
}

bool AmbulanceDispatcher::checkDriverExists(const string &driverName)
{
    ifstream file("data/inactive_duty_ambulance.txt");
    if (!file.is_open())
        return false;

    string line;
    getline(file, line);
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, name;
        getline(ss, id, ',');
        getline(ss, name, ',');
        if (trim(name) == trim(driverName))
        {
            return true;
        }
    }
    return false;
}

void AmbulanceDispatcher::removeDriverFromInactive(const string &driverName)
{
    string filePath = "data/inactive_duty_ambulance.txt";
    string tempPath = "data/temp_inactive.txt";

    ifstream inFile(filePath);
    ofstream outFile(tempPath);

    if (!inFile.is_open() || !outFile.is_open())
    {
        cerr << "Error: Unable to open inactive file for update.\n";
        return;
    }

    string line;
    bool isHeader = true;

    while (getline(inFile, line))
    {
        if (isHeader)
        {
            outFile << line << "\n";
            isHeader = false;
            continue;
        }

        stringstream ss(line);
        string id, name;
        getline(ss, id, ',');
        getline(ss, name, ',');

        if (trim(name) != trim(driverName))
        {
            outFile << line << "\n";
        }
    }

    inFile.close();
    outFile.close();

    remove(filePath.c_str());
    rename(tempPath.c_str(), filePath.c_str());
}

// Helper: get driver ID from inactive file
int AmbulanceDispatcher::getDriverID(const string &driverName)
{
    ifstream file("data/inactive_duty_ambulance.txt");
    if (!file.is_open())
        return -1;

    string line;
    getline(file, line);
    while (getline(file, line))
    {
        stringstream ss(line);
        string idStr, name;
        getline(ss, idStr, ',');
        getline(ss, name, ',');

        if (trim(name) == trim(driverName))
            return stoi(idStr);
    }
    return -1;
}

void AmbulanceDispatcher::registerAmbulance()
{
    try
    {
        string driver, shift, workingHours;

        cout << "Enter Driver Name: ";
        getline(cin, driver);
        driver = trim(driver);

        int driverID = getDriverID(driver);
        if (driverID == -1)
        {
            cout << "Error: Driver not found in inactive list. Cannot register.\n";
            return;
        }

        do
        {
            cout << "Enter Shift Mode (A/B/C): ";
            getline(cin, shift);
            shift = trim(shift);
        } while (shift != "A" && shift != "B" && shift != "C");

        // Create Ambulance object
        Ambulance newAmbulance(driverID, driver);
        newAmbulance.setDutyStatus(true);
        newAmbulance.setShiftMode(shift);
        newAmbulance.setWorkingHours(0.00);
        newAmbulance.setTimeStamp(getCurrentTime());

        ambulanceQueue.enqueue(newAmbulance);
        cout << "Ambulance registered successfully.\n";

        removeDriverFromInactive(driver);

        if (!dataFile.empty())
            saveToFile();
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << "\n";
    }
}

void AmbulanceDispatcher::rotateShift()
{
    try
    {
        cout << "\n================ BEFORE ROTATION ================\n";
        ambulanceQueue.display();

        cout << "\nRotating ambulance shifts...\n";
        ambulanceQueue.rotateDuty();

        cout << "\n================ AFTER ROTATION =================\n";
        ambulanceQueue.display();

        if (!dataFile.empty())
            saveToFile();
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
    getline(file, line);

    while (getline(file, line))
    {
        stringstream ss(line);
        string idStr, name, status, shiftMode, workingHours, timestamp;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, status, ',');
        getline(ss, shiftMode, ',');
        getline(ss, workingHours, ',');
        getline(ss, timestamp, ',');

        if (!idStr.empty() && !name.empty())
        {
            Ambulance ambulance(stoi(idStr), name);
            ambulance.setDutyStatus(status == "OnDuty");
            ambulance.setShiftMode(shiftMode);
            ambulance.setWorkingHours(stof(workingHours));
            ambulance.setTimeStamp(timestamp);
            ambulanceQueue.enqueue(ambulance);
        }
    }

    file.close();
}

void AmbulanceDispatcher::saveToFile() const
{
    ofstream active("data/active_duty_ambulance.txt");

    if (!active.is_open())
    {
        cerr << "Error: Unable to save data to files!\n";
        return;
    }

    active << "AmbulanceID,DriverName,Status,ShiftMode,WorkingHours,TimeStamp\n";

    int size = ambulanceQueue.getSize();
    Ambulance *ambulances = new Ambulance[size];
    int actualSize = 0;
    ambulanceQueue.getAllAmbulances(ambulances, actualSize);

    for (int i = 0; i < actualSize; i++)
    {
        Ambulance &ambulance = ambulances[i];
        active << fixed << setprecision(2)
               << ambulance.getId() << ","
               << ambulance.getDriverName() << ","
               << (ambulance.getDutyStatus() ? "OnDuty" : "OffDuty") << ","
               << ambulance.getShiftMode() << ","
               << ambulance.getWorkingHours() << ","
               << ambulance.getTimeStamp() << "\n";
    }

    delete[] ambulances;
    active.close();
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
        cout << "1. Add New Ambulance to Inactive Duty\n";
        cout << "2. Register Ambulance to Active Duty\n";
        cout << "3. Rotate Shift\n";
        cout << "4. Display Schedule\n";
        cout << "5. Exit to Main Menu\n";
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
            addAmbulanceToInactive();
            break;
        }
        case 2:
        {
            registerAmbulance();
            break;
        }
        case 3:
            rotateShift();
            break;
        case 4:
            displaySchedule();
            break;
        case 5:
            cout << "Exiting to Main Menu...\n";
            break;
        default:
            cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 5);
}
