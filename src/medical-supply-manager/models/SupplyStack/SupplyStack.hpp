#ifndef SUPPLYSTACK_HPP
#define SUPPLYSTACK_HPP

#include "Supply.hpp"

class SupplyStack {
private:
    SupplyNode* top;
    int size;

public:
    SupplyStack();
    ~SupplyStack();
    
    void push(const Supply& supply);
    Supply pop();
    Supply peek() const;
    
    bool isEmpty() const;
    int getSize() const;
    void display() const;
    int getAllSupplies(Supply* suppliesArray, int maxSize) const;
    void clear();
    void displayWithHeader() const;
};

#endif