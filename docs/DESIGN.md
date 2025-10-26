# Emergency Department System - Design Documentation

## System Architecture

### Overview

This module implements the **Emergency Department Officer** role using a **Priority Queue** data structure based on a Min-Heap algorithm. The system manages emergency cases by priority level, ensuring critical cases are processed first.

## Data Structure: Priority Queue (Min-Heap)

### Why Priority Queue?

- **Automatic Sorting**: Cases are automatically ordered by priority
- **Efficient Operations**: O(log n) insertion and extraction
- **Critical-First Processing**: Ensures highest priority cases are always accessible
- **Real-world Alignment**: Matches hospital triage systems

### Heap Properties

- **Min-Heap Implementation**: Smallest priority number (most critical) at root
- **Complete Binary Tree**: Maintains balanced structure
- **Array-Based**: Efficient memory usage without pointers

### Time Complexity

| Operation   | Complexity |
| ----------- | ---------- |
| Insert      | O(log n)   |
| Extract Min | O(log n)   |
| Peek        | O(1)       |
| Display All | O(n)       |

## Class Structure

### 1. EmergencyCase

**Purpose**: Data container for individual emergency cases

**Attributes**:

- `caseID`: Unique identifier (EC####)
- `patientName`: Patient's full name
- `emergencyType`: Type of emergency
- `priorityLevel`: 1-5 (1 = critical, 5 = non-urgent)
- `timestamp`: When case was logged

**Methods**:

- Getters/Setters for all attributes
- Comparison operators for priority ordering
- `display()`: Console output
- `toString()`: CSV formatting for file storage

### 2. PriorityQueue

**Purpose**: Min-heap implementation for case management

**Private Attributes**:

- `heap[]`: Dynamic array storing cases
- `capacity`: Maximum array size
- `size`: Current number of cases

**Core Methods**:

- `insert()`: Add case and maintain heap property
- `extractMin()`: Remove and return highest priority case
- `peek()`: View highest priority without removal
- `heapifyUp()`: Restore heap after insertion
- `heapifyDown()`: Restore heap after extraction

### 3. EmergencyDepartment

**Purpose**: Main controller and user interface

**Responsibilities**:

- File I/O operations
- User interaction
- Case ID generation
- Data persistence

**Key Methods**:

- `logEmergencyCase()`: Add new emergency
- `processMostCriticalCase()`: Handle highest priority
- `viewPendingEmergencyCases()`: Display all cases
- `loadFromFile()` / `saveToFile()`: Data persistence

## Data Flow

```
User Input → EmergencyDepartment → PriorityQueue → EmergencyCase
                     ↓
                File Storage
```

### 1. Logging New Case

```
1. User enters patient details
2. System generates unique Case ID
3. System captures timestamp
4. EmergencyCase object created
5. Inserted into PriorityQueue (heapifyUp)
6. Saved to file
```

### 2. Processing Critical Case

```
1. System retrieves root of heap (minimum priority)
2. Root is returned as most critical case
3. Last element moved to root
4. heapifyDown restores heap property
5. File updated
```

### 3. Viewing Cases

```
1. Display all cases in heap array
2. Cases shown in priority order
3. Heap structure maintained (read-only)
```

## File Structure

### emergency_cases.txt Format

```csv
CaseID,PatientName,EmergencyType,PriorityLevel,Timestamp
EC0001,John Doe,Cardiac Arrest,1,2024-03-15 14:30:00
```

**Fields**:

- **CaseID**: EC#### (auto-generated)
- **PatientName**: String (no commas)
- **EmergencyType**: String describing emergency
- **PriorityLevel**: Integer 1-5
- **Timestamp**: YYYY-MM-DD HH:MM:SS

## Priority Level Guidelines

| Level | Category    | Examples                              | Response Time |
| ----- | ----------- | ------------------------------------- | ------------- |
| 1     | Critical    | Cardiac arrest, severe trauma, stroke | Immediate     |
| 2     | Emergency   | Severe bleeding, major fractures      | < 10 minutes  |
| 3     | Urgent      | Moderate injuries, high fever         | < 30 minutes  |
| 4     | Semi-urgent | Minor fractures, mild symptoms        | < 1 hour      |
| 5     | Non-urgent  | Follow-ups, minor ailments            | < 2 hours     |

## Integration Points

### With Patient Admission Clerk

- Emergency cases can generate patient admission
- Case ID can link to Patient ID
- Transfer data after emergency stabilization

### With Medical Supply Manager

- Request supplies based on emergency type
- Critical cases trigger automatic supply allocation
- Track supply usage per emergency

### With Ambulance Dispatcher

- Coordinate ambulance arrivals with case logging
- Priority level affects ambulance deployment
- Real-time updates on incoming emergencies

## Memory Management

### Dynamic Array Resizing

```cpp
if (size >= capacity) {
    capacity *= 2;  // Double the capacity
    // Allocate new array and copy data
}
```

### Heap Invariant Maintenance

- **After Insert**: HeapifyUp from last position
- **After Extract**: HeapifyDown from root
- Ensures O(log n) complexity maintained

## Error Handling

### Common Scenarios

1. **Empty Queue**: Check before extraction
2. **File Not Found**: Create new file with header
3. **Invalid Priority**: Default to level 3 (Urgent)
4. **Corrupted Data**: Skip malformed lines

### Exception Safety

- Try-catch blocks for file operations
- Validation on user inputs
- Graceful degradation on errors

## Testing Strategy

### Unit Tests

- Test heap operations independently
- Verify priority ordering
- Check boundary conditions

### Integration Tests

- File load/save operations
- Full workflow (log → process → view)
- Data persistence across sessions

### Test Cases

1. Log cases with different priorities
2. Process cases in correct order
3. Handle empty queue gracefully
4. Load existing data correctly
5. Save data persistently

## Future Enhancements

### Possible Improvements

1. **Search Functionality**: Find cases by ID or name
2. **Case History**: Track processed cases
3. **Statistics Dashboard**: Case counts by priority
4. **Notification System**: Alert staff for critical cases
5. **Multi-priority Processing**: Handle multiple cases simultaneously

## Coding Standards

### Naming Conventions

- Classes: PascalCase (EmergencyCase)
- Methods: camelCase (extractMin)
- Variables: camelCase (priorityLevel)
- Constants: UPPER_SNAKE_CASE

### File Organization

- Each class in separate .hpp/.cpp files
- Clear separation of interface and implementation
- Minimal dependencies between modules

### Comments

- Header comments for each class/method
- Inline comments for complex algorithms
- Documentation for integration points

## Performance Considerations

### Optimization Strategies

1. **Heap over Linear Search**: O(log n) vs O(n)
2. **Array-based Storage**: Cache-friendly, no pointer overhead
3. **Batch File Writes**: Save on program exit, not per operation
4. **Minimal String Copying**: Pass by reference where possible

### Scalability

- System handles 100+ cases efficiently
- Dynamic resizing prevents overflow
- File-based persistence allows unlimited historical data

---

**Author**: [Your Name]  
**Role**: Emergency Department Officer  
**Date**: March 2024  
**Version**: 1.0
