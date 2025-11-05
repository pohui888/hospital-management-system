#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <string>
#include "../models/Supply/Supply.hpp"

using namespace std;

class FileHandler {
private:
    string filename;
    
    Supply parseLineToSupply(const string& line);
    string supplyToLine(const Supply& supply);

public:
    FileHandler(const string& file = "supplies.txt");
    ~FileHandler();
    
    // Load all supplies from file into array and return nums of row loaded
    int loadSupplies(Supply* supplies, int maxSize);
    bool saveSupplies(Supply* supplies, int count);
    
    bool fileExists();
    void createNewFile();
    
    string getFilename() const;
    void setFilename(const string& file);
    
    int countRecords();
};

#endif