#ifndef SUPPLY_HPP
#define SUPPLY_HPP

#include <string>
using namespace std;

class Supply {
private:
    string supplyId;
    string type;
    int quantity;
    string batch;
    string dateAdded;

public:
    // constructors & destructor
    Supply();
    Supply(string id, string t, int qty, string b, string date);
    Supply(const Supply& other);
    ~Supply();
    
    // Getters
    string getSupplyId() const;
    string getType() const;
    int getQuantity() const;
    string getBatch() const;
    string getDateAdded() const;
    
    // Setters
    void setSupplyID(const string& id);
    void setType(const string& t);
    void setQuantity(int qty);
    void setBatch(const string& b);
    void setDateAdded(const string& date);
    
    void displaySupply() const;
    string toString() const;
    
    Supply& operator=(const Supply& other);
};

class SupplyNode {
public:
    Supply data;
    SupplyNode* next;
    
    SupplyNode();
    SupplyNode(const Supply& supply);
    
    ~SupplyNode();
};

#endif