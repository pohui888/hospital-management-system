#include "SupplyManager.hpp"
#include "../../utils/utils.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

SupplyManager::SupplyManager()
{
    stack = new SupplyStack();
    fileHandler = new FileHandler("data/supplies.txt");
    nextSupplyIDNumber = 1;

    loadFromFile();
}

SupplyManager::SupplyManager(const string &filename)
{
    stack = new SupplyStack();
    fileHandler = new FileHandler(filename);
    nextSupplyIDNumber = 1;

    loadFromFile();
}

SupplyManager::~SupplyManager()
{
    saveToFile();

    delete stack;
    delete fileHandler;
}

string SupplyManager::generateSupplyID()
{
    stringstream ss;
    ss << "SUP" << setfill('0') << setw(3) << nextSupplyIDNumber;
    nextSupplyIDNumber++;
    return ss.str();
}

int SupplyManager::extractIDNumber(const string &supplyID)
{
    if (supplyID.length() >= 4 && supplyID.substr(0, 3) == "SUP")
    {
        try
        {
            return stoi(supplyID.substr(3));
        }
        catch (...)
        {
            return 0;
        }
    }
    return 0;
}

void SupplyManager::addSupplyStock()
{
    Utils::clearScreen();
    Utils::displayHeader("ADD SUPPLY STOCK");

    cout << "\nEnter supply details:\n"
         << endl;

    // Get supply type
    string type = Utils::getNonEmptyStringInput("Supply Type (e.g., Surgical Gloves, Syringes): ");

    // Get quantity
    int quantity;
    while (true)
    {
        quantity = Utils::getIntInput("Quantity: ");
        if (Utils::isValidQuantity(quantity))
        {
            break;
        }
        else
        {
            Utils::displayError("Quantity must be greater than 0!");
        }
    }

    // Get batch number
    string batch = Utils::getNonEmptyStringInput("Batch Number (e.g., BATCH2024-001): ");

    // Generate supply ID and date
    string supplyID = generateSupplyID();
    string dateAdded = Utils::getCurrentDateTime();

    // Create supply object
    Supply newSupply(supplyID, type, quantity, batch, dateAdded);

    // Add to stack
    stack->push(newSupply);

    cout << "\n";
    Utils::displaySeparator('=', 70);
    Utils::displaySuccess("Supply added successfully!");
    cout << "Supply ID: " << supplyID << endl;
    cout << "Type: " << type << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Batch: " << batch << endl;
    cout << "Date Added: " << dateAdded << endl;
    Utils::displaySeparator('=', 70);

    Utils::pauseScreen();
}

void SupplyManager::useLastAddedSupply()
{
    Utils::clearScreen();
    Utils::displayHeader("USE LAST ADDED SUPPLY");

    // Check if stack is empty
    if (stack->isEmpty())
    {
        cout << "\n";
        Utils::displayWarning("No supplies available in stock!");
        cout << "Please add supplies first before using them.\n"
             << endl;
        Utils::pauseScreen();
        return;
    }

    // Show the supply that will be used
    cout << "\nLast Added Supply (Top of Stack):\n"
         << endl;
    Utils::displaySeparator('-', 70);

    try
    {
        Supply topSupply = stack->peek();

        cout << left << setw(15) << "Supply ID:" << topSupply.getSupplyId() << endl;
        cout << left << setw(15) << "Type:" << topSupply.getType() << endl;
        cout << left << setw(15) << "Quantity:" << topSupply.getQuantity() << endl;
        cout << left << setw(15) << "Batch:" << topSupply.getBatch() << endl;
        cout << left << setw(15) << "Date Added:" << topSupply.getDateAdded() << endl;
        Utils::displaySeparator('-', 70);

        // Ask for confirmation
        cout << endl;
        bool confirm = Utils::getConfirmation("Are you sure you want to use this supply?");

        if (confirm)
        {
            // Remove the supply
            Supply usedSupply = stack->pop();

            cout << "\n";
            Utils::displaySeparator('=', 70);
            Utils::displaySuccess("Supply used and removed from stock!");
            cout << "Supply ID: " << usedSupply.getSupplyId() << " has been consumed." << endl;
            Utils::displaySeparator('=', 70);
        }
        else
        {
            cout << "\n";
            Utils::displayWarning("Operation cancelled. Supply remains in stock.");
        }
    }
    catch (const exception &e)
    {
        Utils::displayError(e.what());
    }

    Utils::pauseScreen();
}

void SupplyManager::viewCurrentSupplies()
{
    Utils::clearScreen();
    Utils::displayHeader("CURRENT SUPPLIES IN STOCK");

    // Display the stack with formatted table
    stack->displayWithHeader();

    Utils::pauseScreen();
}

void SupplyManager::loadFromFile()
{
    cout << "\nLoading supplies from file..." << endl;

    // First, count how many records are in file
    int recordCount = fileHandler->countRecords();

    if (recordCount == 0)
    {
        cout << "No existing supplies found. Starting with empty stock." << endl;
        return;
    }

    // Create temporary array to load supplies
    const int MAX_SUPPLIES = 1000;
    Supply *tempArray = new Supply[MAX_SUPPLIES];

    // Load supplies from file
    int loadedCount = fileHandler->loadSupplies(tempArray, MAX_SUPPLIES);

    // Push supplies to stack (from first to last, so last becomes top)
    for (int i = 0; i < loadedCount; i++)
    {
        stack->push(tempArray[i]);

        // Update next ID number if needed
        int idNum = extractIDNumber(tempArray[i].getSupplyId());
        if (idNum >= nextSupplyIDNumber)
        {
            nextSupplyIDNumber = idNum + 1;
        }
    }

    // Clean up temporary array
    delete[] tempArray;

    cout << "Loaded " << loadedCount << " supplies into the system." << endl;
}

void SupplyManager::saveToFile()
{
    if (stack->isEmpty())
    {
        cout << "\nNo supplies to save." << endl;
        return;
    }

    cout << "\nSaving supplies to file..." << endl;

    // Create array to store supplies
    const int MAX_SUPPLIES = 1000;
    Supply *saveArray = new Supply[MAX_SUPPLIES];

    // Get all supplies from stack
    int count = stack->getAllSupplies(saveArray, MAX_SUPPLIES);

    // Save to file
    bool success = fileHandler->saveSupplies(saveArray, count);

    // Clean up
    delete[] saveArray;

    if (success)
    {
        cout << "Data saved successfully!" << endl;
    }
    else
    {
        Utils::displayError("Failed to save data to file!");
    }
}

int SupplyManager::getStackSize() const
{
    return stack->getSize();
}

bool SupplyManager::isStackEmpty() const
{
    return stack->isEmpty();
}

void SupplyManager::displayStatistics() const
{
    Utils::clearScreen();
    Utils::displayHeader("SYSTEM STATISTICS");

    cout << "\n";
    cout << left << setw(30) << "Total Supplies in Stock:" << stack->getSize() << endl;
    cout << left << setw(30) << "Next Supply ID:" << "SUP" << setfill('0') << setw(3) << nextSupplyIDNumber << setfill(' ') << endl;
    cout << left << setw(30) << "Data File:" << fileHandler->getFilename() << endl;
    cout << left << setw(30) << "Stack Status:" << (stack->isEmpty() ? "Empty" : "Contains Data") << endl;

    cout << "\n";
    Utils::pauseScreen();
}