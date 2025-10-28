#include "MedicalSupplyMenuHandler.hpp"

#include <iostream>
#include <string>
using namespace std;

MedicalSupplyMenuHandler::MedicalSupplyMenuHandler(SupplyManager* manager) {
    this->supplyManager = manager;
}

void MedicalSupplyMenuHandler::displayMenu() {
    cout << "\n========= Medical Supply Manager =========";
    cout << "\n1. Add Supply Stock";
    cout << "\n2. Use 'Last Added' Supply";
    cout << "\n3. View Current Supplies";
    cout << "\n4. Exit";
    cout << "\n==========================================";
}

void MedicalSupplyMenuHandler::handleUserChoice() {
    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                supplyManager->addSupplyStock();
                break;

            case 2:
                supplyManager->useLastSupply();
                break;

            case 3:
                supplyManager->viewCurrentSupplies();
                break;

            case 4:
                cout << "\nReturning to main menu...\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 4);
}