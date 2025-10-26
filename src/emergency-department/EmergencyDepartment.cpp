#include "EmergencyDepartment.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>

// Constructor
EmergencyDepartment::EmergencyDepartment(const std::string &filePath)
    : dataFilePath(filePath), nextCaseNumber(1)
{
    emergencyQueue = new PriorityQueue();
    loadFromFile();
}

// Destructor
EmergencyDepartment::~EmergencyDepartment()
{
    saveToFile();
    delete emergencyQueue;
}

// Generate unique case ID
std::string EmergencyDepartment::generateCaseID()
{
    std::stringstream ss;
    ss << "EC" << std::setw(4) << std::setfill('0') << nextCaseNumber++;
    return ss.str();
}

// Get current timestamp
std::string EmergencyDepartment::getCurrentTimestamp()
{
    time_t now = time(0);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return std::string(buffer);
}

// Trim whitespace from string
std::string EmergencyDepartment::trim(const std::string &str)
{
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

// Load cases from file
void EmergencyDepartment::loadFromFile()
{
    std::ifstream file(dataFilePath.c_str());
    if (!file.is_open())
    {
        std::cout << "Creating new data file: " << dataFilePath << std::endl;
        return;
    }

    std::string line;
    // Skip header line
    std::getline(file, line);

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        std::string caseID, name, type, priorityStr, timestamp;

        std::getline(ss, caseID, ',');
        std::getline(ss, name, ',');
        std::getline(ss, type, ',');
        std::getline(ss, priorityStr, ',');
        std::getline(ss, timestamp);

        // Trim whitespace
        caseID = trim(caseID);
        name = trim(name);
        type = trim(type);
        priorityStr = trim(priorityStr);
        timestamp = trim(timestamp);

        if (!caseID.empty() && !name.empty())
        {
            int priority = std::stoi(priorityStr);
            EmergencyCase emergencyCase(caseID, name, type, priority, timestamp);
            emergencyQueue->insert(emergencyCase);

            // Update case number counter
            if (caseID.substr(0, 2) == "EC")
            {
                int num = std::stoi(caseID.substr(2));
                if (num >= nextCaseNumber)
                {
                    nextCaseNumber = num + 1;
                }
            }
        }
    }

    file.close();
    std::cout << "Loaded " << emergencyQueue->getSize() << " emergency cases from file.\n";
}

// Save cases to file
void EmergencyDepartment::saveToFile()
{
    std::ofstream file(dataFilePath.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: Unable to save data to file!\n";
        return;
    }

    // Write header
    file << "CaseID,PatientName,EmergencyType,PriorityLevel,Timestamp\n";

    // Write all cases
    int size = emergencyQueue->getSize();
    EmergencyCase *cases = emergencyQueue->getAllCases();
    for (int i = 0; i < size; i++)
    {
        file << cases[i].toString() << "\n";
    }

    file.close();
}

// Functionality 1: Log Emergency Case
void EmergencyDepartment::logEmergencyCase()
{
    std::cout << "\n"
              << std::string(60, '=') << std::endl;
    std::cout << "LOG NEW EMERGENCY CASE\n";
    std::cout << std::string(60, '=') << std::endl;

    std::string name, type;
    int priority;

    std::cout << "Enter patient name: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "\nEmergency Types:\n";
    std::cout << "  - Cardiac Arrest\n";
    std::cout << "  - Severe Trauma\n";
    std::cout << "  - Stroke\n";
    std::cout << "  - Severe Bleeding\n";
    std::cout << "  - Major Fracture\n";
    std::cout << "  - Moderate Injury\n";
    std::cout << "  - Other\n";
    std::cout << "Enter emergency type: ";
    std::getline(std::cin, type);

    std::cout << "\nPriority Levels:\n";
    std::cout << "  1 - Critical (Life-threatening)\n";
    std::cout << "  2 - Emergency (Severe)\n";
    std::cout << "  3 - Urgent (Moderate)\n";
    std::cout << "  4 - Semi-urgent (Minor)\n";
    std::cout << "  5 - Non-urgent (Follow-up)\n";
    std::cout << "Enter priority level (1-5): ";
    std::cin >> priority;

    if (priority < 1 || priority > 5)
    {
        std::cout << "Invalid priority level! Setting to 3 (Urgent).\n";
        priority = 3;
    }

    std::string caseID = generateCaseID();
    std::string timestamp = getCurrentTimestamp();

    EmergencyCase newCase(caseID, name, type, priority, timestamp);
    emergencyQueue->insert(newCase);

    std::cout << "\n"
              << std::string(60, '-') << std::endl;
    std::cout << "Emergency case logged successfully!\n";
    std::cout << "Case ID: " << caseID << std::endl;
    std::cout << "Priority: " << priority << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    saveToFile();
}

// Functionality 2: Process Most Critical Case
void EmergencyDepartment::processMostCriticalCase()
{
    std::cout << "\n"
              << std::string(60, '=') << std::endl;
    std::cout << "PROCESS MOST CRITICAL CASE\n";
    std::cout << std::string(60, '=') << std::endl;

    if (emergencyQueue->isEmpty())
    {
        std::cout << "No pending emergency cases to process.\n";
        std::cout << std::string(60, '=') << std::endl;
        return;
    }

    try
    {
        EmergencyCase criticalCase = emergencyQueue->extractMin();

        std::cout << "\nProcessing the following case:\n";
        std::cout << std::string(60, '-') << std::endl;
        std::cout << "Case ID       : " << criticalCase.getCaseID() << std::endl;
        std::cout << "Patient Name  : " << criticalCase.getPatientName() << std::endl;
        std::cout << "Emergency Type: " << criticalCase.getEmergencyType() << std::endl;
        std::cout << "Priority Level: " << criticalCase.getPriorityLevel() << std::endl;
        std::cout << "Logged Time   : " << criticalCase.getTimestamp() << std::endl;
        std::cout << std::string(60, '-') << std::endl;
        std::cout << "\nCase has been attended to and removed from queue.\n";
        std::cout << "Remaining cases: " << emergencyQueue->getSize() << std::endl;
        std::cout << std::string(60, '=') << std::endl;

        saveToFile();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// Functionality 3: View Pending Emergency Cases
void EmergencyDepartment::viewPendingEmergencyCases()
{
    emergencyQueue->displayAll();
}

// Display menu
void EmergencyDepartment::displayMenu()
{
    std::cout << "\n"
              << std::string(60, '=') << std::endl;
    std::cout << "     EMERGENCY DEPARTMENT MANAGEMENT SYSTEM\n";
    std::cout << std::string(60, '=') << std::endl;
    std::cout << "1. Log Emergency Case\n";
    std::cout << "2. Process Most Critical Case\n";
    std::cout << "3. View Pending Emergency Cases\n";
    std::cout << "4. Exit\n";
    std::cout << std::string(60, '-') << std::endl;
    std::cout << "Enter your choice: ";
}

// Run the system
void EmergencyDepartment::run()
{
    int choice;

    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════════╗\n";
    std::cout << "║     HOSPITAL EMERGENCY DEPARTMENT MANAGEMENT SYSTEM        ║\n";
    std::cout << "║              Emergency Department Officer Module           ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════╝\n";

    do
    {
        displayMenu();
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            logEmergencyCase();
            break;
        case 2:
            processMostCriticalCase();
            break;
        case 3:
            viewPendingEmergencyCases();
            break;
        case 4:
            std::cout << "\nSaving data and exiting...\n";
            std::cout << "Thank you for using the Emergency Department System!\n";
            break;
        default:
            std::cout << "\nInvalid choice! Please try again.\n";
        }
    } while (choice != 4);
}

// Get case count
int EmergencyDepartment::getCaseCount() const
{
    return emergencyQueue->getSize();
}