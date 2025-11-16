#include "Supply.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

Supply::Supply() {
    supplyId = "";
    type = "";
    quantity = 0;
    batch = "";
    dateAdded = "";
}

Supply::Supply(string id, string t, int qty, string b, string date) {
    supplyId = id;
    type = t;
    quantity = qty;
    batch = b;
    dateAdded = date;
}

Supply::Supply(const Supply& other) {
    supplyId = other.supplyId;
    type = other.type;
    quantity = other.quantity;
    batch = other.batch;
    dateAdded = other.dateAdded;
}

Supply::~Supply() {
    //
}

string Supply::getSupplyId() const {
    return supplyId;
}

string Supply::getType() const {
    return type;
}

int Supply::getQuantity() const {
    return quantity;
}

string Supply::getBatch() const {
    return batch;
}

string Supply::getDateAdded() const {
    return dateAdded;
}

void Supply::setSupplyID(const string& id) {
    supplyId = id;
}

void Supply::setType(const string& t) {
    type = t;
}

void Supply::setQuantity(int qty) {
    if (qty >= 0) {
        quantity = qty;
    } else {
        cerr << "Error: Quantity cannot be negative!" << endl;
    }
}

void Supply::setBatch(const string& b) {
    batch = b;
}

void Supply::setDateAdded(const string& date) {
    dateAdded = date;
}

void Supply::displaySupply() const {
    cout << left << setw(12) << supplyId 
         << setw(25) << type 
         << setw(12) << quantity 
         << setw(20) << batch 
         << dateAdded << endl;
}

string Supply::toString() const {
    stringstream ss;
    ss << supplyId << "," 
       << type << "," 
       << quantity << "," 
       << batch << "," 
       << dateAdded;
    return ss.str();
}

Supply& Supply::operator=(const Supply& other) {
    if (this != &other) {
        supplyId = other.supplyId;
        type = other.type;
        quantity = other.quantity;
        batch = other.batch;
        dateAdded = other.dateAdded;
    }
    return *this;
}

SupplyNode::SupplyNode() {
    data = Supply();
    next = nullptr;
}

SupplyNode::SupplyNode(const Supply& supply) {
    data = supply;
    next = nullptr;
}

SupplyNode::~SupplyNode() {
    //
}