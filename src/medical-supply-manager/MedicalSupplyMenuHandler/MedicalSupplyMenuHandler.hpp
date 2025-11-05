#ifndef MENUHANDLER_HPP
#define MENUHANDLER_HPP

#include "../controllers/SupplyManager/SupplyManager.hpp"

class MedicalSupplyMenuHandler {
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
    MedicalSupplyMenuHandler();
    
    // Constructor with custom filename
    MedicalSupplyMenuHandler(const string& filename);
    
    // Destructor
    ~MedicalSupplyMenuHandler();
    
    // Run the main application loop
    void run();
    
    // Process user menu choice
    void processChoice(int choice);
};

#endif