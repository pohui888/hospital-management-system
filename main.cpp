#include "src/emergency-department/EmergencyDepartment.hpp"
#include "src/patient-admission/PatientFunction.hpp"
#include "src/ambulance-dispatcher/AmbulanceDispatcher.hpp"
#include "src/medical-supply-manager/MedicalSupplyMenuHandler/MedicalSupplyMenuHandler.hpp"
#include "src/medical-supply-manager/utils/utils.hpp"
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
            std::cout << "  1. Patient Admission Clerk\n";
            std::cout << "  2. Medical Supply Manager\n";
            std::cout << "  3. Emergency Department Officer\n";
            std::cout << "  4. Ambulance Dispatcher\n";
            std::cout << "  5. Exit\n";
            std::cout << "Enter choice (1-5): ";
            std::cin >> roleChoice;

            switch (roleChoice)
            {
            case 1:{
                PatientFunction admission("./data/patient.txt");  // path to your patient file
                admission.run();  // show the patient admission menu
                break;
                }
            case 2:
                try
                {
                    MedicalSupplyMenuHandler menu;

                    menu.run();
                }
                catch (const exception &e)
                {
                    Utils::displayError("Fatal error occurred!");
                    cerr << "Exception: " << e.what() << endl;
                    return 1;
                }
                break;
            case 3:
            {
                EmergencyDepartment emergencyDept("./data/emergency_cases.txt");
                emergencyDept.run();
                break;
            }
            case 4:
            {
                AmbulanceDispatcher ambulanceDispatcher("./data/active_duty_ambulance.txt");
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
