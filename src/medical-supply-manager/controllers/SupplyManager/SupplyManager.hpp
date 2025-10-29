#ifndef SUPPLYMANAGER_HPP
#define SUPPLYMANAGER_HPP

#include "../models/SupplyStack/SupplyStack.hpp"
#include "../FileHandler/FileHandler.hpp"
#include <string>

using namespace std;

class SupplyManager {
    private:
        SupplyStack* stack;
        FileHandler* fileHandler;
        int nextSupplyIDNumber;

        string generateSupplyID();
        int extractIDNumber(const string& supplyID);

    public:
        // Constructor
        SupplyManager();
        SupplyManager(const string& filename);
        
        // Destructor
        ~SupplyManager();

        void addSupplyStock();
        void useLastAddedSupply();
        void viewCurrentSupplies();

        void loadFromFile();
        void saveToFile();

        int getStackSize() const;
        bool isStackEmpty() const;
        void displayStatistics() const;
};

#endif