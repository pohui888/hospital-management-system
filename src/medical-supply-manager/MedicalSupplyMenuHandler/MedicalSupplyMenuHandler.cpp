#include "MedicalSupplyMenuHandler.hpp"
#include "../utils/utils.hpp"
#include <iostream>

using namespace std;

MenuHandler::MenuHandler() {
    manager = new SupplyManager();
    isRunning = true;
}

MenuHandler::MenuHandler(const string& filename) {
    manager = new SupplyManager(filename);
    isRunning = true;
}

MenuHandler::~MenuHandler() {
    delete manager;
}

void MenuHandler::displayWelcomeBanner() {
    Utils::clearScreen();
    cout << "\n";
    Utils::displaySeparator('*', 80);
    cout << "*" << string(78, ' ') << "*" << endl;
    cout << "*" << string(25, ' ') << "MEDICAL SUPPLY MANAGER MODULE" << string(24, ' ') << "*" << endl;
    cout << "*" << string(78, ' ') << "*" << endl;
    Utils::displaySeparator('*', 80);
    cout << "\n";
    cout << "  Welcome to the Medical Supply Management System!" << endl;
    cout << "  This module manages hospital medical supplies using Stack (LIFO) data structure." << endl;
    cout << "\n";
    Utils::pauseScreen();
}

void MenuHandler::displayMainMenu() {
    Utils::clearScreen();
    Utils::displaySeparator('=', 80);
    cout << "||" << string(25, ' ') << "MEDICAL SUPPLY MANAGEMENT MENU" << string(23, ' ') << "||" << endl;
    Utils::displaySeparator('=', 80);
    cout << endl;
    
    cout << "  [1] Add Supply Stock" << endl;
    cout << "      └─ Record new supply items (type, quantity, batch)" << endl;
    cout << endl;
    
    cout << "  [2] Use Last Added Supply" << endl;
    cout << "      └─ Remove the most recently added supply (LIFO)" << endl;
    cout << endl;
    
    cout << "  [3] View Current Supplies" << endl;
    cout << "      └─ Display all supplies in stock" << endl;
    cout << endl;
    
    cout << "  [4] System Statistics" << endl;
    cout << "      └─ View system information and statistics" << endl;
    cout << endl;
    
    cout << "  [5] Save and Exit" << endl;
    cout << "      └─ Save data and close the application" << endl;
    cout << endl;
    
    Utils::displaySeparator('=', 80);
    cout << "  Current Supplies in Stock: " << manager->getStackSize() << endl;
    Utils::displaySeparator('=', 80);
    cout << endl;
}

void MenuHandler::displayExitMessage() {
    Utils::clearScreen();
    cout << "\n";
    Utils::displaySeparator('*', 80);
    cout << "*" << string(78, ' ') << "*" << endl;
    cout << "*" << string(22, ' ') << "THANK YOU FOR USING THE SYSTEM!" << string(25, ' ') << "*" << endl;
    cout << "*" << string(78, ' ') << "*" << endl;
    cout << "*" << string(18, ' ') << "Medical Supply Management System - Closing" << string(20, ' ') << "*" << endl;
    cout << "*" << string(78, ' ') << "*" << endl;
    Utils::displaySeparator('*', 80);
    cout << "\n";
    cout << "  Data has been saved successfully." << endl;
    cout << "  All supplies have been recorded to file." << endl;
    cout << "\n";
    cout << "  System developed for Hospital Patient Care Management" << endl;
    cout << "  Role: Medical Supply Manager" << endl;
    cout << "  Data Structure: Stack (LIFO)" << endl;
    cout << "\n";
    Utils::displaySeparator('*', 80);
    cout << "\n";
}

void MenuHandler::processChoice(int choice) {
    switch (choice) {
        case 1:
            // Functionality 1: Add Supply Stock
            manager->addSupplyStock();
            break;
            
        case 2:
            // Functionality 2: Use Last Added Supply
            manager->useLastAddedSupply();
            break;
            
        case 3:
            // Functionality 3: View Current Supplies
            manager->viewCurrentSupplies();
            break;
            
        case 4:
            // System Statistics
            manager->displayStatistics();
            break;
            
        case 5:
            // Exit
            isRunning = false;
            break;
            
        default:
            Utils::displayError("Invalid choice! Please select 1-5.");
            Utils::pauseScreen();
            break;
    }
}

void MenuHandler::run() {
    // Display welcome banner
    displayWelcomeBanner();
    
    // Main menu loop
    while (isRunning) {
        displayMainMenu();
        
        // Get user choice
        int choice = Utils::getIntInputInRange("Enter your choice (1-5): ", 1, 5);
        
        // Process the choice
        processChoice(choice);
    }
    
    // Display exit message
    displayExitMessage();
}