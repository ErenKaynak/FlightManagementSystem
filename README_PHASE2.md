# Flight Management System - Phase 2

## Phase 2 University Assignment - Advanced C++ Features

This project implements Phase 2 requirements for the Flight Management System, including advanced C++ features and algorithmic problem solving.

## 📋 Requirements Implemented

### PART 1: Technical Requirements ✓

1. **Static Variables**
   - Flight class: Tracks total flights created
   - Person class: Tracks total people in system
   - Access via `Flight::getTotalFlights()` and `Person::getTotalPeople()`

2. **Friend Functions**
   - `operator<<` for Flight class (stream output)
   - `compareFlights()` utility function for detailed flight comparison

3. **Operator Overloading**
   - `operator==` - Compare flights by ID
   - `operator<` - Compare flights by price (for sorting)
   - `operator=` - Assignment operator
   - `operator<<` - Stream output operator

### PART 2: Algorithmic Problem Solving ✓

**Problem A: Calculate Total Revenue**
- Function: `calculateTotalRevenue()`
- Algorithm: Simple iteration and accumulation
- Complexity: O(n) time, O(1) space

**Problem B: QuickSort Algorithm**
- Function: `sortFlightsByPrice()` and `sortFlightsByDuration()`
- Algorithm: Classic QuickSort (divide and conquer)
- Complexity: O(n log n) average case
- Detailed explanation included in code comments

**Problem B (Alternative): Binary Search**
- Function: `searchFlightById()`
- Algorithm: Binary Search on sorted flight IDs
- Complexity: O(log n) time, O(1) space
- Detailed explanation included in code comments

## 🏗️ Build Instructions

```bash
# Clean previous builds
make clean

# Build the project
make

# Run the application
./build/fms
```

## 🧪 Testing

### Automated Unit Tests

Run the unit tests to verify core functionality:

```bash
# Compile the test suite
g++ -std=c++11 -Wall -Iinclude test_phase2.cpp \
    src/Flight/flight.cpp src/Person/person.cpp \
    src/Pilot/pilot.cpp src/Worker/worker.cpp \
    src/Aircraft/aircraft.cpp -o test_phase2

# Run tests
./test_phase2
```

Expected output: All tests should pass with ✓ marks.

### Manual Testing

1. **Start the application:**
   ```bash
   ./build/fms
   ```

2. **Access Phase 2 Features:**
   - Select option `4` from the main menu
   - This opens the "Phase 2 Features & Algorithms" menu

3. **Test Each Feature:**

   **a) Display Statistics (Static Variables):**
   - Select option `1`
   - Verify total flights and people counts

   **b) Calculate Total Revenue:**
   - Select option `2`
   - Should show sum of all flight prices

   **c) Sort by Price (QuickSort):**
   - Select option `3`
   - View before/after sorting
   - Verify flights sorted from cheapest to most expensive

   **d) Sort by Duration (QuickSort):**
   - Select option `4`
   - View before/after sorting
   - Verify flights sorted by duration (shortest to longest)

   **e) Binary Search:**
   - Select option `5`
   - Enter a flight ID (e.g., "FL-1")
   - System will search and display if found

   **f) Demonstrate All Features:**
   - Select option `6`
   - Shows usage of operators and friend functions

## 📊 Sample Data

The system comes with sample data in `data/` directory:

- **5 flights** with varying prices ($125 - $520.75) and durations (90-360 minutes)
- **4 aircraft types** (Boeing 737, Airbus A320, Boeing 777, Airbus A380)
- **Pilots and workers** for assignment testing

## 📝 Code Organization

```
FlightManagementSystem/
├── include/
│   ├── Flight.h          # Flight class with static vars & operators
│   ├── Person.h          # Person class with static counter
│   ├── Admin.h           # Admin class with algorithm methods
│   └── Menu.h            # Menu system
├── src/
│   ├── Flight/
│   │   └── flight.cpp    # Flight implementation & friend functions
│   ├── Person/
│   │   └── person.cpp    # Person implementation
│   ├── algorithms.cpp    # Phase 2 algorithms (NEW)
│   ├── menu.cpp          # Menu implementation
│   └── admin.cpp         # Admin implementation
├── test_phase2.cpp       # Automated unit tests (NEW)
├── PHASE2_SUMMARY.md     # Comprehensive documentation (NEW)
└── README.md             # This file (NEW)
```

## 🎯 Key Features

### Static Variables
- **Flight::totalFlights** - Incremented in constructor, decremented in destructor
- **Person::totalPeople** - Tracks all people objects (Pilots, Workers, etc.)
- Used for system monitoring and statistics

### Operator Overloading Examples

```cpp
// Equality comparison
if (flight1 == flight2) {
    cout << "Same flight!" << endl;
}

// Price comparison for sorting
if (flight1 < flight2) {
    cout << "Flight1 is cheaper" << endl;
}

// Stream output
cout << flight1 << endl;  // Prints formatted flight details
```

### Friend Functions

```cpp
// Stream output (friend)
cout << flight << endl;

// Compare two flights (friend)
compareFlights(flight1, flight2);
```

## 📖 Algorithm Explanations

### QuickSort
- **Pivot Selection:** Last element
- **Partitioning:** Elements smaller than pivot go left, larger go right
- **Recursion:** Sort left and right sub-arrays independently
- **Why QuickSort?** O(n log n) average case, in-place sorting, industry standard

### Binary Search
- **Prerequisite:** Sorted array
- **Method:** Divide search space in half each iteration
- **Comparison:** target vs middle element
- **Why Binary Search?** O(log n) time - extremely fast for large datasets

## 🔍 Edge Cases Handled

- Empty flight lists
- Flights with zero price
- Duplicate flight IDs
- Self-assignment in operator=
- Backward compatibility with old data format
- Invalid search queries

## 📚 Documentation

See `PHASE2_SUMMARY.md` for:
- Detailed implementation explanations
- Algorithm complexity analysis
- Code examples and usage
- Educational value and learning outcomes
- Testing recommendations
- Complete feature walkthrough

## ✅ Phase 2 Checklist

- [x] Static variables implemented (Flight, Person)
- [x] Friend functions implemented (operator<<, compareFlights)
- [x] Operator overloading (==, <, =, <<)
- [x] Problem A: Calculate total revenue
- [x] Problem B: QuickSort implementation
- [x] Problem B: Binary Search implementation
- [x] Comprehensive code comments
- [x] Algorithm explanations
- [x] Menu system for Phase 2 features
- [x] Unit tests created and passing
- [x] Documentation completed
- [x] Code compiles without errors
- [x] Edge cases handled

## 🎓 Learning Outcomes

This implementation demonstrates:

1. **C++ Advanced Features:**
   - Static member variables and methods
   - Friend functions and operator overloading
   - Object-oriented design principles

2. **Algorithm Design:**
   - Divide and conquer (QuickSort)
   - Binary Search optimization
   - Time/space complexity analysis

3. **Software Engineering:**
   - Clean, well-documented code
   - Modular design
   - Backward compatibility
   - Unit testing

## 👨‍💻 Developer Notes

- All Phase 2 features are marked with `// REQUIREMENT:` comments
- Algorithms include detailed explanations in comments
- Code follows C++11 standard
- No external dependencies required
- Designed for educational purposes

## 📄 License

Academic project - Flight Management System Phase 2

---

**Status:** ✅ COMPLETE - Ready for submission
**Author:** Implemented for university assignment Phase 2
**Date:** December 2024
