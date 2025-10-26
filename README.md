# Hospital Emergency Department Management System

## Project Overview

This system manages emergency cases in a hospital using a **Priority Queue** data structure. Emergency cases are prioritized based on severity levels (1-5), with critical cases processed first.

## Team Member: Emergency Department Officer

**Data Structure Used:** Priority Queue (Min-Heap Implementation)

## Features

1. **Log Emergency Case** - Add new emergency cases with priority levels
2. **Process Most Critical Case** - Attend to the highest-priority emergency
3. **View Pending Emergency Cases** - Display all cases sorted by priority

## Priority Levels

- **Level 1 (Critical):** Life-threatening - Cardiac arrest, severe trauma, stroke
- **Level 2 (Emergency):** Severe bleeding, major fractures, severe burns
- **Level 3 (Urgent):** Moderate injuries, high fever, infections
- **Level 4 (Semi-urgent):** Minor fractures, mild symptoms
- **Level 5 (Non-urgent):** Minor ailments, follow-ups

## Project Structure

```
hospital-emergency-system/
├── src/               # Source code files
├── data/              # Data storage (txt files)
├── docs/              # Documentation
└── build/             # Compiled executables
```

## Compilation Instructions

### Windows (MinGW/MSVC)

```bash
g++ -std=c++11 src/*.cpp -o build/hospital_system.exe
```

### Linux/Mac

```bash
g++ -std=c++11 src/*.cpp -o build/hospital_system
```

## Running the Program

```bash
# Windows
.\build\hospital_system.exe

# Linux/Mac
./build/hospital_system
```

## Data File Format

### emergency_cases.txt

```
CaseID,PatientName,EmergencyType,PriorityLevel,Timestamp
EC001,John Doe,Cardiac Arrest,1,2024-03-15 14:30:00
EC002,Jane Smith,Severe Bleeding,2,2024-03-15 14:35:00
```

## Integration with Other Modules

- **Patient Admission Clerk:** Receives patient ID for admitted emergency cases
- **Medical Supply Manager:** Requests supplies for emergency treatment
- **Ambulance Dispatcher:** Coordinates ambulance arrivals with emergency cases

## Development Guidelines

1. No STL containers (vector, list, queue) allowed
2. Manual implementation of Priority Queue using arrays
3. File-based persistence for data storage
4. Modular code design for easy integration

## Author

[Your Name] - Emergency Department Officer Module

## Version

1.0.0 - Initial Release
