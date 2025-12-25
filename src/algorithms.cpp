#include "Admin.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

/*
 * ============================================================================
 * PART 2: ALGORITHMIC PROBLEM SOLVING
 * ============================================================================
 */

/*
 * PROBLEM A (Standard Functional Problem):
 * Calculate the total revenue from all flights in the system.
 * 
 * Algorithm Logic:
 * - Iterate through all flights in the vector
 * - Sum up the price of each flight
 * - Return the total revenue
 * 
 * Time Complexity: O(n) where n is the number of flights
 * Space Complexity: O(1) - only using a single variable to store sum
 */
double Admin::calculateTotalRevenue() const {
    double totalRevenue = 0.0;
    
    // Iterate through all flights and accumulate their prices
    for (const auto& flight : flights) {
        totalRevenue += flight.getPrice();
    }
    
    return totalRevenue;
}

/*
 * ============================================================================
 * PROBLEM B (Complex Algorithm): QuickSort Implementation
 * ============================================================================
 * 
 * QuickSort is a divide-and-conquer sorting algorithm that:
 * 1. Selects a 'pivot' element from the array
 * 2. Partitions the other elements into two sub-arrays:
 *    - Elements less than the pivot
 *    - Elements greater than the pivot
 * 3. Recursively sorts the sub-arrays
 * 
 * WHY QuickSort?
 * - Average time complexity: O(n log n)
 * - In-place sorting (doesn't require extra space)
 * - Efficient for large datasets
 * - Widely used in industry
 * 
 * HOW it works:
 * 1. Choose the last element as pivot
 * 2. Place pivot at its correct position in sorted array
 * 3. Place all smaller elements to left of pivot
 * 4. Place all greater elements to right of pivot
 * 5. Recursively apply to left and right sub-arrays
 */

/*
 * Partition function for QuickSort
 * 
 * This function takes the last element as pivot, places the pivot element
 * at its correct position in sorted array, and places all smaller elements
 * to left of pivot and all greater elements to right of pivot.
 * 
 * Parameters:
 * - arr: Vector of flights to be sorted
 * - low: Starting index
 * - high: Ending index
 * - sortByPrice: If true, sort by price; if false, sort by duration
 * 
 * Returns: Index of the pivot element after partitioning
 */
int Admin::partition(vector<Flight>& arr, int low, int high, bool sortByPrice) {
    // Select the last element as pivot
    Flight pivot = arr[high];
    
    // Index of smaller element - indicates the right position
    // of pivot found so far
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        // Compare based on sort criteria
        bool isSmaller;
        if (sortByPrice) {
            isSmaller = arr[j].getPrice() < pivot.getPrice();
        } else {
            isSmaller = arr[j].getDurationMinutes() < pivot.getDurationMinutes();
        }
        
        // If current element is smaller than the pivot
        if (isSmaller) {
            i++; // Increment index of smaller element
            swap(arr[i], arr[j]);
        }
    }
    
    // Place pivot at correct position
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

/*
 * Recursive QuickSort function
 * 
 * Parameters:
 * - arr: Vector of flights to be sorted
 * - low: Starting index
 * - high: Ending index
 * - sortByPrice: If true, sort by price; if false, sort by duration
 */
void Admin::quickSortHelper(vector<Flight>& arr, int low, int high, bool sortByPrice) {
    if (low < high) {
        // Partitioning index - arr[pi] is now at right place
        int pi = partition(arr, low, high, sortByPrice);
        
        // Recursively sort elements before partition and after partition
        quickSortHelper(arr, low, pi - 1, sortByPrice);
        quickSortHelper(arr, pi + 1, high, sortByPrice);
    }
}

/*
 * Public method to sort flights by price using QuickSort
 */
void Admin::sortFlightsByPrice() {
    if (flights.empty()) {
        cout << "No flights to sort." << endl;
        return;
    }
    
    cout << "\n--- Sorting Flights by Price (QuickSort Algorithm) ---" << endl;
    cout << "Before sorting:" << endl;
    for (const auto& flight : flights) {
        cout << "  " << flight << endl;
    }
    
    // Apply QuickSort algorithm
    quickSortHelper(flights, 0, flights.size() - 1, true);
    
    cout << "\nAfter sorting (by price - ascending):" << endl;
    for (const auto& flight : flights) {
        cout << "  " << flight << endl;
    }
    
    saveFlightsToFile(); // Save sorted flights
    cout << "\nFlights sorted successfully!" << endl;
}

/*
 * Public method to sort flights by duration using QuickSort
 */
void Admin::sortFlightsByDuration() {
    if (flights.empty()) {
        cout << "No flights to sort." << endl;
        return;
    }
    
    cout << "\n--- Sorting Flights by Duration (QuickSort Algorithm) ---" << endl;
    cout << "Before sorting:" << endl;
    for (const auto& flight : flights) {
        cout << "  " << flight << endl;
    }
    
    // Apply QuickSort algorithm
    quickSortHelper(flights, 0, flights.size() - 1, false);
    
    cout << "\nAfter sorting (by duration - ascending):" << endl;
    for (const auto& flight : flights) {
        cout << "  " << flight << endl;
    }
    
    saveFlightsToFile(); // Save sorted flights
    cout << "\nFlights sorted successfully!" << endl;
}

/*
 * ============================================================================
 * PROBLEM B (Alternative Complex Algorithm): Binary Search Implementation
 * ============================================================================
 * 
 * Binary Search is an efficient searching algorithm for sorted arrays that:
 * 1. Compares the target value to the middle element of the array
 * 2. If they match, return the position
 * 3. If target is less than middle, search the left half
 * 4. If target is greater than middle, search the right half
 * 5. Repeat until found or search space is empty
 * 
 * WHY Binary Search?
 * - Time complexity: O(log n) - much faster than linear search O(n)
 * - Efficient for large datasets
 * - Requires sorted data
 * 
 * HOW it works:
 * 1. Sort the flights by ID (using Flight ID as key)
 * 2. Compare target ID with middle element
 * 3. Eliminate half of the search space in each iteration
 * 4. Continue until found or search space exhausted
 */

/*
 * Binary search helper function
 * 
 * Parameters:
 * - sortedFlights: Vector of flights sorted by ID
 * - flightId: The flight ID to search for
 * 
 * Returns: Index of the flight if found, -1 otherwise
 */
int Admin::binarySearchById(const vector<Flight>& sortedFlights, const string& flightId) {
    int left = 0;
    int right = sortedFlights.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // Get the middle element's ID
        string midId = sortedFlights[mid].getFlightId();
        
        // Check if flightId is present at mid
        if (midId == flightId) {
            return mid;
        }
        
        // If flightId is greater, ignore left half
        if (midId < flightId) {
            left = mid + 1;
        }
        // If flightId is smaller, ignore right half
        else {
            right = mid - 1;
        }
    }
    
    // Flight ID not found
    return -1;
}

/*
 * Public method to search for a flight by ID using Binary Search
 * 
 * Returns: Pointer to the flight if found, nullptr otherwise
 */
Flight* Admin::searchFlightById(const string& flightId) {
    if (flights.empty()) {
        cout << "No flights available to search." << endl;
        return nullptr;
    }
    
    cout << "\n--- Searching for Flight (Binary Search Algorithm) ---" << endl;
    cout << "Searching for Flight ID: " << flightId << endl;
    
    // Create a sorted copy of flights by ID for binary search
    vector<Flight> sortedFlights = flights;
    
    // Sort by flight ID using standard library sort
    // (In a real scenario, we'd maintain a sorted index or use our QuickSort)
    sort(sortedFlights.begin(), sortedFlights.end(), 
         [](const Flight& a, const Flight& b) {
             return a.getFlightId() < b.getFlightId();
         });
    
    cout << "Sorted flights by ID for binary search:" << endl;
    for (const auto& flight : sortedFlights) {
        cout << "  " << flight.getFlightId() << endl;
    }
    
    // Perform binary search
    int index = binarySearchById(sortedFlights, flightId);
    
    if (index != -1) {
        cout << "\nFlight FOUND!" << endl;
        cout << sortedFlights[index] << endl;
        
        // Find the flight in the original unsorted vector and return pointer to it
        for (auto& flight : flights) {
            if (flight.getFlightId() == flightId) {
                return &flight;
            }
        }
    } else {
        cout << "\nFlight NOT FOUND!" << endl;
        return nullptr;
    }
    
    return nullptr;
}

/*
 * Display statistics including static variable counts
 * This demonstrates the use of static variables
 */
void Admin::displayStatistics() const {
    cout << "\n========================================" << endl;
    cout << "   FLIGHT MANAGEMENT SYSTEM STATISTICS   " << endl;
    cout << "========================================" << endl;
    
    // REQUIREMENT: Using Static Variables
    cout << "\nStatic Counters:" << endl;
    cout << "  Total Flights Created: " << Flight::getTotalFlights() << endl;
    cout << "  Total People Created: " << Person::getTotalPeople() << endl;
    
    cout << "\nCurrent Data:" << endl;
    cout << "  Flights in System: " << flights.size() << endl;
    cout << "  Aircraft in System: " << aircrafts.size() << endl;
    cout << "  People in System: " << people.size() << endl;
    
    // PROBLEM A: Calculate total revenue
    double revenue = calculateTotalRevenue();
    cout << "\nFinancial Information:" << endl;
    cout << "  Total Revenue: $" << fixed << setprecision(2) << revenue << endl;
    
    if (!flights.empty()) {
        double avgPrice = revenue / flights.size();
        cout << "  Average Flight Price: $" << fixed << setprecision(2) << avgPrice << endl;
    }
    
    cout << "========================================\n" << endl;
}

/*
 * Demonstration function to showcase all Phase 2 features
 * This includes:
 * - Static variables
 * - Friend functions
 * - Operator overloading
 * - Algorithms (QuickSort, Binary Search)
 */
void Admin::demonstrateAlgorithms() {
    cout << "\n========================================" << endl;
    cout << "  PHASE 2 FEATURES DEMONSTRATION" << endl;
    cout << "========================================" << endl;
    
    // Display statistics (uses static variables)
    displayStatistics();
    
    if (flights.size() >= 2) {
        cout << "\n--- DEMONSTRATION: Friend Function (compareFlights) ---" << endl;
        // REQUIREMENT: Using Friend Function
        compareFlights(flights[0], flights[1]);
    }
    
    if (flights.size() >= 2) {
        cout << "\n--- DEMONSTRATION: Operator Overloading ---" << endl;
        
        // REQUIREMENT: Using == operator
        cout << "Testing == operator:" << endl;
        if (flights[0] == flights[1]) {
            cout << "  Flights are the same" << endl;
        } else {
            cout << "  Flights are different" << endl;
        }
        
        // REQUIREMENT: Using < operator
        cout << "\nTesting < operator (comparing by price):" << endl;
        if (flights[0] < flights[1]) {
            cout << "  Flight " << flights[0].getFlightId() 
                 << " is cheaper than " << flights[1].getFlightId() << endl;
        } else {
            cout << "  Flight " << flights[1].getFlightId() 
                 << " is cheaper than " << flights[0].getFlightId() << endl;
        }
        
        // REQUIREMENT: Using << operator
        cout << "\nTesting << operator (stream output):" << endl;
        cout << "  " << flights[0] << endl;
        cout << "  " << flights[1] << endl;
    }
    
    cout << "\n========================================" << endl;
    cout << "For sorting and searching demonstrations," << endl;
    cout << "please use the dedicated menu options." << endl;
    cout << "========================================\n" << endl;
}
