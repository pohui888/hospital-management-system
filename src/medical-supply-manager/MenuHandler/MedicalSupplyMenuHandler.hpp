#ifndef MEDICAL_SUPPLY_MENU_HANDLER
#define MEDICAL_SUPPLY_MENU_HANDLER

#include "../models/SupplyStack/SupplyStack.hpp"
#include "../controllers/SupplyManager/SupplyManager.hpp"

class MedicalSupplyMenuHandler {
    private:
        SupplyManager* supplyManager;

    public:
        MedicalSupplyMenuHandler(SupplyManager* manager);

        void displayMenu();
        void handleUserChoice();
};

#endif