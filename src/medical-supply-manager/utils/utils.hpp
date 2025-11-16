#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
using namespace std;

namespace Utils {
    string getCurrentDateTime();
    int getIntInput(const string& prompt);
    int getIntInputInRange(const string& prompt, int min, int max);
    string getStringInput(const string& prompt);
    string getNonEmptyStringInput(const string& prompt);

    bool isValidQuantity(int quantity);
    string trim(const string& str);
    string toUpperCase(const string& str);
    string toLowerCase(const string& str);

    void clearScreen();
    void pauseScreen();

    void displaySeparator(char symbol = '-', int length = 80);
    void displayHeader(const string& title);
    void displaySuccess(const string& message);
    void displayError(const string& message);
    void displayWarning(const string& message);

    bool getConfirmation(const string& prompt);
}

#endif
