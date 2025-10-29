#include "FileHandler.hpp"
#include "../models/Supply/Supply.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

FileHandler::FileHandler(const string& file) : filename(file) {
    if (!fileExists()) {
        createNewFile();
    }
}

FileHandler::~FileHandler() {
    //
}

Supply FileHandler::parseLineToSupply(const string& line) {
    stringstream ss(line);
    string supplyID, type, quantityStr, batch, dateAdded;
    
    // Parse comma-separated line
    getline(ss, supplyID, ',');
    getline(ss, type, ',');
    getline(ss, quantityStr, ',');
    getline(ss, batch, ',');
    getline(ss, dateAdded, ',');
    
    // Convert quantity string to integer
    int quantity = 0;
    try {
        quantity = stoi(quantityStr);
    } catch (const exception& e) {
        cerr << "Error parsing quantity: " << e.what() << endl;
        quantity = 0;
    }
    
    // Create and return Supply object
    Supply supply(supplyID, type, quantity, batch, dateAdded);
    return supply;
}


string FileHandler::supplyToLine(const Supply& supply) {
    stringstream ss;
    ss << supply.getSupplyId() << ","
       << supply.getType() << ","
       << supply.getQuantity() << ","
       << supply.getBatch() << ","
       << supply.getDateAdded();
    return ss.str();
}


int FileHandler::loadSupplies(Supply* supplies, int maxSize) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error: Unable to open file '" << filename << "' for reading." << endl;
        return 0;
    }
    
    string line;
    bool isFirstLine = true;
    int count = 0;
    
    while (getline(file, line) && count < maxSize) {
        // Skip header line
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }
        
        // Skip empty lines
        if (line.empty() || line.find_first_not_of(" \t\r\n") == string::npos) {
            continue;
        }
        
        try {
            supplies[count] = parseLineToSupply(line);
            count++;
        } catch (const exception& e) {
            cerr << "Error parsing line: " << line << endl;
            cerr << "Exception: " << e.what() << endl;
        }
    }
    
    file.close();
    
    if (count > 0) {
        cout << "Successfully loaded " << count << " supplies from file." << endl;
    } else {
        cout << "No supplies found in file." << endl;
    }
    
    return count;
}


bool FileHandler::saveSupplies(Supply* supplies, int count) {
    ofstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error: Unable to open file '" << filename << "' for writing." << endl;
        return false;
    }
    
    // Write header
    file << "SupplyID,Type,Quantity,Batch,DateAdded" << endl;
    
    // Write each supply
    for (int i = 0; i < count; i++) {
        file << supplyToLine(supplies[i]) << endl;
    }
    
    file.close();
    cout << "Successfully saved " << count << " supplies to file." << endl;
    return true;
}


bool FileHandler::fileExists() {
    ifstream file(filename);
    bool exists = file.good();
    file.close();
    return exists;
}

void FileHandler::createNewFile() {
    ofstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error: Unable to create file '" << filename << "'." << endl;
        return;
    }
    
    // Write header
    file << "SupplyID,Type,Quantity,Batch,DateAdded" << endl;
    
    file.close();
    cout << "Created new file: " << filename << endl;
}


string FileHandler::getFilename() const {
    return filename;
}


void FileHandler::setFilename(const string& file) {
    filename = file;
}


int FileHandler::countRecords() {
    ifstream file(filename);
    
    if (!file.is_open()) {
        return 0;
    }
    
    string line;
    int count = 0;
    bool isFirstLine = true;
    
    while (getline(file, line)) {
        // Skip header
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }
        
        // Skip empty lines
        if (line.empty() || line.find_first_not_of(" \t\r\n") == string::npos) {
            continue;
        }
        
        count++;
    }
    
    file.close();
    return count;
}