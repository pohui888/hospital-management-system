#include "src/emergency-department/EmergencyDepartment.hpp"
#include "src/ambulance-dispatcher/AmbulanceDispatcher.hpp"
#include <iostream>

int main()
{
    try
    {
        int roleChoice = 0;

        do
        {
            std::cout << "\n";
            std::cout << "╔════════════════════════════════════════════════════════════╗\n";
            std::cout << "║    HOSPITAL PATIENT CARE MANAGEMENT SYSTEM                 ║\n";
            std::cout << "╚════════════════════════════════════════════════════════════╝\n\n";
            std::cout << "Select your role:\n";
            std::cout << "  1. PATIENT ADMISSION CLERK\n";
            std::cout << "  2. MEDICAL SUPPLY MANAGER\n";
            std::cout << "  3. EMERGENCY DEPARTMENT OFFICER\n";
            std::cout << "  4. AMBULANCE DISPATCHER\n";
            std::cout << "  5. Exit\n";
            std::cout << "Enter choice (1-5): ";
            std::cin >> roleChoice;

            switch (roleChoice)
            {
            case 1:
                std::cout << "\n----LOGIC HERE.----\n";
                break;
            case 2:
                std::cout << "\n---LOGIC HERE.----\n";
                break;
            case 3:
            {
                EmergencyDepartment emergencyDept("./data/emergency_cases.txt");
                emergencyDept.run();
                break;
            }
            case 4:
            {
                AmbulanceDispatcher ambulanceDispatcher("./data/ambulances.txt");
                ambulanceDispatcher.run();
                break;
            }
            case 5:
                std::cout << "\nExiting system. Thank you!\n";
                break;
            default:
                std::cout << "\nInvalid choice! Please try again.\n";
            }
        } while (roleChoice != 5);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fatal Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
