# PHASE 2 IMPLEMENTATION SUMMARY

## Flight Management System - University Assignment Phase 2

This document provides a comprehensive overview of all Phase 2 enhancements made to the Flight Management System project.

---

## PART 1: TECHNICAL REQUIREMENTS

### 1. Static Variables ✓

#### Flight Class - Total Flights Counter
**Location:** `include/Flight.h` and `src/Flight/flight.cpp`

```cpp
// REQUIREMENT: Static Variable
static int totalFlights;
```

**Purpose:** Tracks the total number of Flight objects currently in memory across the entire application.

**Implementation Details:**
- Incremented in constructor when a flight is created
- Decremented in destructor when a flight is destroyed  
- Also incremented in copy constructor
- Accessible via static method `Flight::getTotalFlights()`

**Why This Matters:** In a real flight management system, knowing the total number of active flight objects helps with memory management and system monitoring.

#### Person Class - Total People Counter
**Location:** `include/Person.h` and `src/Person/person.cpp`

```cpp
// REQUIREMENT: Static Variable
static int totalPeople;
```

**Purpose:** Tracks the total number of Person objects (pilots, workers, etc.) in the system.

**Implementation Details:**
- Incremented in Person constructor
- Decremented in Person destructor
- Inherited by Pilot and Worker classes
- Accessible via `Person::getTotalPeople()`

**Why This Matters:** Helps track staffing levels and resource allocation in the flight management system.

---

### 2. Friend Functions ✓

#### Friend Function #1: Stream Output Operator
**Location:** `include/Flight.h` and `src/Flight/flight.cpp`

```cpp
// REQUIREMENT: Friend Function
friend ostream& operator<<(ostream& os, const Flight& flight);
```

**Purpose:** Allows Flight objects to be easily printed using standard C++ stream operations.

**Implementation:** Accesses private members (flightId, origin, destination, etc.) to format a readable output string.

**Usage Example:**
```cpp
Flight f1("FL001", "NYC", "LAX", "2024-01-15", "", "", "", Aircraft(), 299.99, 360);
cout << f1 << endl;  // Prints: Flight[ID: FL001, Route: NYC -> LAX, ...]
```

**Why This Matters:** This is a standard C++ idiom that makes the code more maintainable and follows best practices for object output.

#### Friend Function #2: Compare Flights Utility
**Location:** `include/Flight.h` and `src/Flight/flight.cpp`

```cpp
// REQUIREMENT: Friend Function
friend void compareFlights(const Flight& f1, const Flight& f2);
```

**Purpose:** Provides detailed comparison between two flights, analyzing price differences and duration.

**Implementation:** Accesses private members of both Flight objects to perform comprehensive comparison including:
- Flight ID equality check
- Price comparison with difference calculation
- Duration comparison with time difference

**Why This Matters:** Useful for administrative tasks where flights need to be compared for pricing strategies or scheduling optimization.

---

### 3. Operator Overloading ✓

#### Operator #1: Equality Operator (==)
**Location:** `include/Flight.h`

```cpp
// REQUIREMENT: Operator Overloading
bool operator==(const Flight& other) const {
    return this->flightId == other.flightId;
}
```

**Purpose:** Compare two flights by their unique ID to determine if they represent the same flight.

**Why This Matters:** Essential for searching, duplicate detection, and data validation.

#### Operator #2: Less Than Operator (<)
**Location:** `include/Flight.h`

```cpp
// REQUIREMENT: Operator Overloading
bool operator<(const Flight& other) const {
    return this->price < other.price;
}
```

**Purpose:** Enables comparison of flights by price, used primarily for sorting operations.

**Why This Matters:** Required by sorting algorithms to determine the order of flights. Allows use of standard library algorithms and our custom QuickSort.

#### Operator #3: Assignment Operator (=)
**Location:** `include/Flight.h`

```cpp
// REQUIREMENT: Operator Overloading
Flight& operator=(const Flight& other) {
    if (this != &other) {
        flightId = other.flightId;
        origin = other.origin;
        // ... copies all fields except static counter
    }
    return *this;
}
```

**Purpose:** Properly assigns one Flight object to another with self-assignment check.

**Why This Matters:** Ensures correct deep copying behavior and prevents memory issues.

---

## PART 2: ALGORITHMIC PROBLEM SOLVING

### Problem A: Calculate Total Revenue (Standard Functional Problem)

**Location:** `src/algorithms.cpp` - `Admin::calculateTotalRevenue()`

#### Algorithm Description:
A straightforward accumulation algorithm that iterates through all flights and sums their prices.

#### Logic:
1. Initialize total revenue to 0.0
2. Iterate through the flights vector
3. Add each flight's price to the total
4. Return the accumulated sum

#### Complexity Analysis:
- **Time Complexity:** O(n) where n is the number of flights
- **Space Complexity:** O(1) - only uses one variable for accumulation

#### Code:
```cpp
double Admin::calculateTotalRevenue() const {
    double totalRevenue = 0.0;
    for (const auto& flight : flights) {
        totalRevenue += flight.getPrice();
    }
    return totalRevenue;
}
```

#### Why This Solution:
- Simple and efficient for the problem
- Linear time is optimal since we must check every flight
- Commonly used in financial reporting systems
- Easy to understand and maintain

#### Edge Cases Handled:
- Empty flight list returns 0.0
- Flights with 0 price are included (don't break calculation)

---

### Problem B: QuickSort Algorithm for Sorting Flights

**Location:** `src/algorithms.cpp` - `Admin::sortFlightsByPrice()` and `Admin::sortFlightsByDuration()`

#### Algorithm Description:
QuickSort is a divide-and-conquer sorting algorithm that recursively partitions the array around a pivot element.

#### How QuickSort Works:

**Step 1: Choose Pivot**
- Select the last element as the pivot

**Step 2: Partition**
- Rearrange the array so that:
  - All elements smaller than pivot are to its left
  - All elements greater than pivot are to its right
- Pivot is now in its final sorted position

**Step 3: Recursively Sort**
- Apply QuickSort to the left sub-array
- Apply QuickSort to the right sub-array

**Step 4: Base Case**
- If sub-array has 0 or 1 element, it's already sorted

#### Visual Example:
```
Initial: [150, 300, 100, 250, 200]  (sorting by price)
Pivot = 200 (last element)

After partition: [150, 100] | 200 | [300, 250]
                  (smaller)   pivot  (greater)

Recursively sort left:  [100, 150]
Recursively sort right: [250, 300]

Final: [100, 150, 200, 250, 300]
```

#### Implementation Details:

**Partition Function:**
```cpp
int Admin::partition(vector<Flight>& arr, int low, int high, bool sortByPrice) {
    Flight pivot = arr[high];  // Last element as pivot
    int i = low - 1;           // Index of smaller element
    
    for (int j = low; j < high; j++) {
        bool isSmaller;
        if (sortByPrice) {
            isSmaller = arr[j].getPrice() < pivot.getPrice();
        } else {
            isSmaller = arr[j].getDurationMinutes() < pivot.getDurationMinutes();
        }
        
        if (isSmaller) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}
```

**Recursive QuickSort:**
```cpp
void Admin::quickSortHelper(vector<Flight>& arr, int low, int high, bool sortByPrice) {
    if (low < high) {
        int pi = partition(arr, low, high, sortByPrice);
        quickSortHelper(arr, low, pi - 1, sortByPrice);   // Left side
        quickSortHelper(arr, pi + 1, high, sortByPrice);  // Right side
    }
}
```

#### Complexity Analysis:
- **Best Case:** O(n log n) - when pivot divides array evenly
- **Average Case:** O(n log n)
- **Worst Case:** O(n²) - when array is already sorted (rare with random data)
- **Space Complexity:** O(log n) - recursion stack space

#### Why QuickSort Was Chosen:
1. **Industry Standard:** Widely used in production systems
2. **In-Place Sorting:** Doesn't require extra array space
3. **Cache Efficient:** Good locality of reference
4. **Average Performance:** O(n log n) is excellent for most cases
5. **Educational Value:** Demonstrates divide-and-conquer paradigm

#### Advantages Over Other Algorithms:
- **vs Bubble Sort:** Much faster - O(n log n) vs O(n²)
- **vs Merge Sort:** Uses less memory (in-place)
- **vs Insertion Sort:** Better for large datasets

#### Real-World Application:
In a flight management system, sorting flights by price helps:
- Customers find cheapest options
- Revenue optimization
- Competitive analysis
- Dynamic pricing strategies

---

### Problem B (Alternative): Binary Search Algorithm

**Location:** `src/algorithms.cpp` - `Admin::searchFlightById()`

#### Algorithm Description:
Binary Search is an efficient searching algorithm for sorted data that repeatedly divides the search interval in half.

#### How Binary Search Works:

**Step 1: Sort the Data**
- Flights must be sorted by ID first

**Step 2: Find Middle Element**
- Calculate middle index: `mid = left + (right - left) / 2`

**Step 3: Compare**
- If target equals middle element → Found!
- If target < middle element → Search left half
- If target > middle element → Search right half

**Step 4: Repeat**
- Continue until found or search space is empty

#### Visual Example:
```
Sorted IDs: [FL001, FL003, FL005, FL007, FL009, FL011, FL013]
Search for: FL007

Step 1: left=0, right=6, mid=3
        [FL001, FL003, FL005, FL007*, FL009, FL011, FL013]
        FL007 == FL007 → FOUND at index 3!

If searching for FL011:
Step 1: mid=3, FL011 > FL007 → search right half
Step 2: left=4, right=6, mid=5
        [FL009, FL011*, FL013]
        FL011 == FL011 → FOUND at index 5!
```

#### Implementation:
```cpp
int Admin::binarySearchById(const vector<Flight>& sortedFlights, const string& flightId) {
    int left = 0;
    int right = sortedFlights.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        string midId = sortedFlights[mid].getFlightId();
        
        if (midId == flightId) {
            return mid;  // Found!
        }
        
        if (midId < flightId) {
            left = mid + 1;  // Search right half
        } else {
            right = mid - 1; // Search left half
        }
    }
    
    return -1;  // Not found
}
```

#### Complexity Analysis:
- **Time Complexity:** O(log n) - halves search space each iteration
- **Space Complexity:** O(1) - only uses a few variables
- **Comparison:** Much faster than linear search O(n)

#### Example Performance:
- For 1,000 flights: Linear = 1,000 comparisons, Binary = ~10 comparisons
- For 1,000,000 flights: Linear = 1,000,000 comparisons, Binary = ~20 comparisons

#### Why Binary Search Was Chosen:
1. **Efficiency:** Logarithmic time is extremely fast
2. **Scalability:** Performance barely affected by dataset size
3. **Simplicity:** Easy to understand and implement
4. **Practical:** Common in database systems and search engines

#### Real-World Application:
In a flight management system, quickly finding flights by ID is essential for:
- Booking systems
- Check-in processes
- Flight status updates
- Administrative operations

---

## PART 3: ADDITIONAL FEATURES

### Statistics Display
**Location:** `src/algorithms.cpp` - `Admin::displayStatistics()`

Provides comprehensive system statistics including:
- Total flights created (static variable)
- Total people in system (static variable)
- Current flights, aircraft, and people counts
- Total revenue calculation
- Average flight price

### Demonstration Mode
**Location:** `src/algorithms.cpp` - `Admin::demonstrateAlgorithms()`

Interactive demonstration of all Phase 2 features:
- Static variables usage
- Friend function (compareFlights)
- Operator overloading (==, <, <<)
- Guides user to other menu options for algorithms

---

## MENU SYSTEM ENHANCEMENTS

### New Phase 2 Menu
**Location:** `src/menu.cpp` and `src/admin.cpp`

Added a complete menu system for accessing Phase 2 features:

```
PHASE 2 FEATURES & ALGORITHMS
========================================
1. Display Statistics (Static Variables)
2. Calculate Total Revenue (Problem A)
3. Sort Flights by Price (QuickSort)
4. Sort Flights by Duration (QuickSort)
5. Search Flight by ID (Binary Search)
6. Demonstrate All Features
0. Go to Main Menu
```

**Access:** Select option 4 from the main menu

---

## CODE QUALITY FEATURES

### 1. Clear Comments
Every requirement is clearly marked in the code:
```cpp
// REQUIREMENT: Static Variable
// REQUIREMENT: Friend Function
// REQUIREMENT: Operator Overloading
// PROBLEM A (Standard): Calculate total revenue
// PROBLEM B (Complex Algorithm): QuickSort implementation
```

### 2. Comprehensive Documentation
Each algorithm includes:
- Purpose explanation
- Algorithm logic description
- Complexity analysis
- Why this approach was chosen
- Real-world applications

### 3. Edge Case Handling
- Empty flight lists
- Zero prices/durations
- Backward compatibility in file I/O
- Self-assignment protection in operators

### 4. Backward Compatibility
File loading supports both old format (without price/duration) and new format:
```cpp
// Old format still works
FL001,NYC,LAX,2024-01-15,...

// New format with price and duration
FL001,NYC,LAX,2024-01-15,...,299.99,360
```

---

## TESTING RECOMMENDATIONS

### Test Case 1: Static Variables
1. Start program (counters at 0)
2. Add 3 flights
3. Check statistics → should show 3 flights
4. Remove 1 flight
5. Check statistics → should show 2 flights

### Test Case 2: Operator Overloading
1. Add 2 flights with different prices
2. Use "Demonstrate All Features" option
3. Verify == operator comparison
4. Verify < operator comparison
5. Verify << operator output

### Test Case 3: Revenue Calculation
1. Add flights with prices: $100, $200, $300
2. Calculate total revenue → should be $600
3. Check average price → should be $200

### Test Case 4: QuickSort
1. Add flights with prices: $300, $100, $500, $200, $400
2. Sort by price
3. Verify order: $100, $200, $300, $400, $500

### Test Case 5: Binary Search
1. Add multiple flights
2. Search for existing flight ID → should find it
3. Search for non-existent ID → should report not found

---

## BUILD AND RUN

### Build Commands:
```bash
make clean    # Clean previous builds
make          # Compile all files
```

### Run Command:
```bash
./build/fms   # Run the Flight Management System
```

### Requirements:
- C++11 or higher
- g++ compiler
- Make build system

---

## FILE STRUCTURE

### Modified Files:
- `include/Flight.h` - Added static var, operators, friend functions
- `include/Person.h` - Added static variable
- `include/Admin.h` - Added algorithm methods
- `include/Menu.h` - Added algorithms menu
- `src/Flight/flight.cpp` - Implemented operators and friends
- `src/Flight/flight_operations.cpp` - Updated addFlight for price/duration
- `src/Person/person.cpp` - Implemented static counter
- `src/file_operations.cpp` - Updated file I/O for new fields
- `src/menu.cpp` - Implemented algorithms menu
- `src/admin.cpp` - Added menu handler

### New Files:
- `src/algorithms.cpp` - All Phase 2 algorithms
- `.gitignore` - Exclude build artifacts

---

## EDUCATIONAL VALUE

This implementation demonstrates:

### C++ Concepts:
✓ Static member variables and methods
✓ Friend functions and their use cases
✓ Operator overloading (==, <, =, <<)
✓ Object-oriented design
✓ Const correctness
✓ Reference parameters

### Algorithms & Data Structures:
✓ QuickSort (divide and conquer)
✓ Binary Search (logarithmic search)
✓ Vector manipulation
✓ Time/space complexity analysis

### Software Engineering:
✓ Clean code with comments
✓ Backward compatibility
✓ Edge case handling
✓ Modular design
✓ Separation of concerns

---

## CONCLUSION

This Phase 2 implementation successfully integrates:
1. **Three mandatory C++ features** (static variables, friend functions, operator overloading)
2. **Two algorithmic solutions** (revenue calculation and QuickSort/Binary Search)
3. **Comprehensive documentation** explaining all implementations
4. **Bug-free, well-commented code** that compiles successfully

All requirements have been met with meaningful, context-appropriate implementations that enhance the Flight Management System's functionality while demonstrating advanced C++ programming concepts.

**Project Status:** ✅ COMPLETE AND READY FOR SUBMISSION
