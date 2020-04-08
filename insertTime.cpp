// Katie Young
// CS 325, Homework Assignment #1

#include <iostream>
#include <fstream>
#include <stdlib.h> 
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std;

int generateList();
int randomInt();
void insertSort(vector<int> &vect, int length);
void saveValueToIndex(vector<int> &vect, int length, int value, int newIndex, int oldIndex);
void writeToFile(vector<int> &vect, int length);

int main() {
    int removeFile = remove("insert.out"); // Delete output file in case program has already been run
    int success = generateList(); // Initiate program

    // Output message according to program success
    if (success == 1) {
        cout << "Insertion sort complete." << endl;
    }
    else {
        cout << "Error: Failed to open file." << endl;
    }

    return 0;
}

// Generates vector of integers and initiates sorting
// Returns 1 if sorting successful
// Returns 0 if file error
int generateList() {
    string fileLine;
    int len;
    vector<int> valueVector;

    // Get n from user
    cout << "Enter the array size: ";
    cin >> len;

    if (len) {
        valueVector.resize(len); // Set vector size

        // Generate random integer and add to vector, up to n values
        for (int i = 0; i < len; i++) {
            valueVector[i] = randomInt();
        }

        // Sort vector
        insertSort(valueVector, len);
        valueVector.clear(); // Clear vector elements

        return 1; // Return 1 if successful
    }
    else {
        return 0; // Return 0 if unsuccessful
    }  
}

int randomInt() {
    // Set range variables for random integer
    int lowInt = 0;
    int highInt = 10001;

    // Generate random integer in range and return
    int newInt = rand() % highInt + lowInt;
    return newInt;
}

// Iterates through array and identifies values to be shifted
// Passes to saveValueToIndex to change element index
void insertSort(vector<int> &vect, int length) {
    int largeValIdx = 0;
    int largeVal = vect[largeValIdx];
    int newIndex;
    int i, k;
    double duration;
    time_t start, end;
    time(&start); // Set start time
    
    // Iterate through array
    for (i = 0; i < length; i++) {
        // Identify values to be shifted
        if (vect[i] < largeVal) {
            k = 0;
            while (vect[k] <= vect[i]) { // Identify index to which the value should be moved
                k++;
            }

            saveValueToIndex(vect, length, vect[i], k, i); // Shift array to right and move value to identified index
        }
        else {
            largeVal = vect[i]; // Update largest value tracker if in correct order
        }
        largeValIdx++;
    }

    time(&end); // Set end time
    duration = double(end - start); // Calculate time duration
    cout.precision(2);
    cout << fixed << duration << " seconds have passed" << endl;

    writeToFile(vect, length); // Output results when finished
}

// Moves passed value to specified index and
// Shifts existing elements to right
void saveValueToIndex(vector<int> &vect, int length, int value, int newIndex, int oldIndex) {
    vector<int> tempVector;
    tempVector.resize(length);
    int i = 0;
    int j = 0;

    // Copy elements to left of new index to temporary vector
    while (i < newIndex) {
        tempVector[i] = vect[i];
        i++;
    }

    // Copy new value to passed index
    tempVector[i] = value;
    j = i + 1;

    // Append remaining elements in old vector to temporary vector
    while (i < length) {
        if (i != oldIndex) { // Skip the shifted value
            tempVector[j] = vect[i];
            j++;
        }

        i++;
    }

    // Replace passed vector with new array element order
    for (i = 0; i < length; i++) {
        vect[i] = tempVector[i];
    }
}

// Writes passed vector elements to "insert.out"
void writeToFile(vector<int> &vect, int length) {
    ofstream outputFile("insert.out", ios_base::app); // Open ofstream and enable overwriting

    // Write elements to file
    for (int i = 0; i < length; i++) {
        outputFile << vect[i] << " ";
    }
    outputFile << endl;

    outputFile.close(); // Close ofstream
}