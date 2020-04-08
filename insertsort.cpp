// Katie Young
// CS 325, Homework Assignment #1

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std;

int readLines(string dataFile);
int getVectorSize(string dataString);
void lineToArray(vector<int> &vect, string dataString, int length);
void insertSort(vector<int> &vect, int length);
void saveValueToIndex(vector<int> &vect, int length, int value, int newIndex, int oldIndex);
void writeToFile(vector<int> &vect, int length);

int main() {
    int removeFile = remove("insert.out"); // Delete output file in case program has already been run
    string list = "data.txt";
    int success = readLines(list); // Initiate program

    // Output message according to program success
    if (success == 1) {
        cout << "Insertion sort complete." << endl;
    }
    else {
        cout << "Error: Failed to open file." << endl;
    }

    return 0;
}

// Reads file line by line and initiates sorting
// Returns 1 if sorting successful
// Returns 0 if file error
int readLines(string dataFile) {
    string fileLine;
    int len;
    vector<int> valueVector;

    ifstream inputFile(dataFile.c_str()); // Open passed file

    // If open successful, read lines
    if (inputFile.is_open()) {
        while(getline(inputFile, fileLine)) { // Iterate through file lines
            // Obtain new vector size and update vector length accordingly
            len = getVectorSize(fileLine);
            valueVector.resize(len);

            // Convert line to vector
            lineToArray(valueVector, fileLine, len);

            // Sort vector
            insertSort(valueVector, len);
            valueVector.clear(); // Clear vector elements
        }

        inputFile.close(); // Close ifstream
        return 1; // Return 1 if successful
    }
    else {
        return 0; // Return 0 if unsuccessful
    }  
}

// Identifies first integer in a given string
// Returns integer as vector size
int getVectorSize(string dataString) {
    int dataItr = 0;
    int dataValue = 0;
    string dataItem;

    // Iterate through string
    while (dataItr <= dataString.length()) {
        // When separator identified, convert to integer and return
        if ((dataString[dataItr] == ' ') || (dataItr == dataString.length())) {
            dataValue = atoi(dataItem.c_str());
            return dataValue;
        }
        else {
            dataItem += dataString[dataItr]; // Append character to string until separator reached
        }

        dataItr++;
    }

    return 0;
}

// Converts a passd string to a vector by separating integers from spaces
void lineToArray(vector<int> &vect, string dataString, int length) {
    int dataItr = 0;
    int vectorItr = 0;
    int isLength = 1;
    int dataValue = 0;
    string dataItem;

    // Iterate through string
    while ((dataItr <= dataString.length()) && (vectorItr < length)) {
        // When separator identified, convert value to integer and append to vector
        if ((dataString[dataItr] == ' ') || (dataItr == dataString.length())) { 
            dataValue = atoi(dataItem.c_str()); // Convert value to integer
            
            // Append value to vector
            if (isLength != 1) {
                vect[vectorItr] = dataValue;
                vectorItr++;
            }
            else {
                isLength = 0; // Ignore length marker
            }
            
            dataValue = 0;
            dataItem = "";
        }
        else {
            dataItem += dataString[dataItr]; // Append character to string until separator reached
        }

        dataItr++;
    }
}

// Iterates through array and identifies values to be shifted
// Passes to saveValueToIndex to change element index
void insertSort(vector<int> &vect, int length) {
    int largeValIdx = 0;
    int largeVal = vect[largeValIdx];
    int newIndex;
    int i, k;
    
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