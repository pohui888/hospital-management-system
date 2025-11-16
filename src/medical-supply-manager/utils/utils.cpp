#include "utils.hpp"
#include <iostream>
#include <limits>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

namespace Utils {
    string getCurrentDateTime() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        
        stringstream ss;
        ss << setfill('0')
           << (1900 + ltm->tm_year) << "-"
           << setw(2) << (1 + ltm->tm_mon) << "-"
           << setw(2) << ltm->tm_mday << " "
           << setw(2) << ltm->tm_hour << ":"
           << setw(2) << ltm->tm_min << ":"
           << setw(2) << ltm->tm_sec;
        
        return ss.str();
    }

    int getIntInput(const string& prompt) {
        int value;
        while (true) {
            cout << prompt;
            cin >> value;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                displayError("Invalid input! Please enter a valid integer.");
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }
        }
    }

    int getIntInputInRange(const string& prompt, int min, int max) {
        int value;
        while (true) {
            value = getIntInput(prompt);
            
            if (value >= min && value <= max) {
                return value;
            } else {
                displayError("Input out of range! Please enter a value between " 
                           + to_string(min) + " and " + to_string(max) + ".");
            }
        }
    }

    string getStringInput(const string& prompt) {
        string value;
        cout << prompt;
        getline(cin, value);
        return trim(value);
    }

    string getNonEmptyStringInput(const string& prompt) {
        string value;
        while (true) {
            value = getStringInput(prompt);
            
            if (!value.empty()) {
                return value;
            } else {
                displayError("Input cannot be empty! Please try again.");
            }
        }
    }

    bool isValidQuantity(int quantity) {
        return quantity > 0;
    }
    
    string trim(const string& str) {
        size_t first = str.find_first_not_of(" \t\n\r");
        if (first == string::npos) {
            return "";
        }
        size_t last = str.find_last_not_of(" \t\n\r");
        return str.substr(first, (last - first + 1));
    }

    string toUpperCase(const string& str) {
        string result = str;
        transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }
    
    string toLowerCase(const string& str) {
        string result = str;
        transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }

    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    void pauseScreen() {
        cout << "\nPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void displaySeparator(char symbol, int length) {
        cout << string(length, symbol) << endl;
    }

    void displayHeader(const string& title) {
        int titleLength = title.length();
        int totalWidth = (titleLength > 60) ? titleLength + 4 : 64;
        int padding = (totalWidth - titleLength - 2) / 2;
        
        displaySeparator('=', totalWidth);
        cout << "|" << string(padding, ' ') << title 
             << string(totalWidth - padding - titleLength - 2, ' ') << "|" << endl;
        displaySeparator('=', totalWidth);
    }

    void displaySuccess(const string& message) {
        cout << "[SUCCESS] " << message << endl;

    }

    void displayError(const string& message) {
        cout << "[ERROR] " << message << endl;
    }

    void displayWarning(const string& message) {
        cout << "[WARNING] " << message << endl;
    }

    bool getConfirmation(const string& prompt) {
        string response;
        while (true) {
            cout << prompt << " (Y/N): ";
            getline(cin, response);
            response = trim(response);
            response = toUpperCase(response);
            
            if (response == "Y" || response == "YES") {
                return true;
            } else if (response == "N" || response == "NO") {
                return false;
            } else {
                displayError("Invalid input! Please enter Y or N.");
            }
        }
    }
}
