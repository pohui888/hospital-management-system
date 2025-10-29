#ifndef MENUHANDLER_HPP
#define MENUHANDLER_HPP

#include "SupplyManager.hpp"

class MenuHandler {
private:
    SupplyManager* manager;
    bool isRunning;
    
    // Display main menu
    void displayMainMenu();
    
    // Display welcome banner
    void displayWelcomeBanner();
    
    // Display exit message
    void displayExitMessage();

public:
    // Constructor
    MenuHandler();
    
    // Constructor with custom filename
    MenuHandler(const string& filename);
    
    // Destructor
    ~MenuHandler();
    
    // Run the main application loop
    void run();
    
    // Process user menu choice
    void processChoice(int choice);
};

#endif