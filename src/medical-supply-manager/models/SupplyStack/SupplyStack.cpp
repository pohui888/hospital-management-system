#include "SupplyStack.hpp"
#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

SupplyStack::SupplyStack() {
    top = nullptr;
    size = 0;
}

SupplyStack::~SupplyStack() {
    clear();
}

void SupplyStack::push(const Supply& supply) {
    SupplyNode* newNode = new SupplyNode(supply);
    
    newNode->next = top;
    top = newNode;
    
    size++;
    
    cout << "Supply added successfully: " << supply.getSupplyId() << endl;
}

Supply SupplyStack::pop() {
    if (isEmpty()) {
        throw runtime_error("Error: Stack is empty! Cannot pop.");
    }
    
    SupplyNode* temp = top;
    Supply poppedSupply = temp->data;
    
    top = top->next;
    
    delete temp;
    
    size--;
    
    return poppedSupply;
}

Supply SupplyStack::peek() const {
    if (isEmpty()) {
        throw runtime_error("Error: Stack is empty! Cannot peek.");
    }
    
    return top->data;
}

bool SupplyStack::isEmpty() const {
    return (top == nullptr);
}

int SupplyStack::getSize() const {
    return size;
}

void SupplyStack::display() const {
    if (isEmpty()) {
        cout << "Stack is empty. No supplies to display." << endl;
        return;
    }
    
    cout << "\n--- Supplies in Stack (Top to Bottom) ---" << endl;
    
    SupplyNode* current = top;
    int position = 1;
    
    while (current != nullptr) {
        cout << "[" << position << "] ";
        current->data.displaySupply();
        current = current->next;
        position++;
    }
    
    cout << "Total supplies: " << size << endl;
}

void SupplyStack::displayWithHeader() const {
    if (isEmpty()) {
        cout << "\n+--------------------------------------------------+" << endl;
        cout << "|          No Supplies Currently in Stock          |" << endl;
        cout << "+--------------------------------------------------+" << endl;
        return;
    }
    
    cout << "\n+==============================================================================+" << endl;
    cout << "|                         CURRENT MEDICAL SUPPLIES                             |" << endl;
    cout << "+==============================================================================+" << endl;
    cout << left << setw(12) << "Supply ID" 
         << setw(25) << "Type" 
         << setw(12) << "Quantity" 
         << setw(20) << "Batch" 
         << "Date Added" << endl;
    cout << "------------------------------------------------------------------------------" << endl;
    
    SupplyNode* current = top;
    
    while (current != nullptr) {
        current->data.displaySupply();
        current = current->next;
    }
    
    cout << "------------------------------------------------------------------------------" << endl;
    cout << "Total Supplies: " << size << endl;
    cout << "+==============================================================================+" << endl;
}

int SupplyStack::getAllSupplies(Supply* suppliesArray, int maxSize) const {
    if (isEmpty() || suppliesArray == nullptr) {
        return 0;
    }

    int count = (size < maxSize) ? size : maxSize;
    Supply* tempArray = new Supply[count];
    
    SupplyNode* current = top;
    int index = 0;
    
    while (current != nullptr && index < count) {
        tempArray[index] = current->data;
        current = current->next;
        index++;
    }
    
    for (int i = 0; i < count; i++) {
        suppliesArray[i] = tempArray[count - 1 - i];
    }
    
    delete[] tempArray;
    
    return count;
}

void SupplyStack::clear() {
    while (!isEmpty()) {
        SupplyNode* temp = top;
        top = top->next;
        delete temp;
    }
    size = 0;
}
