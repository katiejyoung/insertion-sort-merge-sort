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
void sortElements(vector<int> &vect, int length);
void mergeSort(vector<int> &vect, int left, int right);
void merge(vector<int> &vect, int left, int right, int middle);
void writeToFile(vector<int> &vect, int length);

int main() {
    int removeFile = remove("merge.out"); // Delete output file in case program has already been run
    string list = "data.txt";
    int success = readLines(list); // Initiate program

    // Output message according to program success
    if (success == 1) {
        cout << "Merge sort complete." << endl;
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
            sortElements(valueVector, len);
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
            dataValue = atoi(dataItem.c_str());
            
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

// Initiates sort and outputs results when complete
void sortElements(vector<int> &vect, int length) {
    // Initiate sort
    mergeSort(vect, 0, (length - 1));

    // Output results to file
    writeToFile(vect, length);
}

void mergeSort(vector<int> &vect, int left, int right) {
    if (left < right) {
        int middle = (left + right)/2;

        mergeSort(vect, left, middle);
        mergeSort(vect, (middle + 1), right);

        merge(vect, left, right, middle);
    }
}

void merge(vector<int> &vect, int left, int right, int middle) {
    vector<int> vectorLeft;
    vector<int> vectorRight;
    int vectorLeftSize = middle - left + 1;
    int vectorRightSize = right - middle;
    int i;
    int j = 0;
    int k = left;

    vectorLeft.resize(vectorLeftSize);
    vectorRight.resize(vectorRightSize);

    for (i = 0; i < vectorLeftSize; i++) {
        vectorLeft[i] = vect[left + i];
    }
    for (i = 0; i < vectorRightSize; i++) {
        vectorRight[i] = vect[middle + i + 1];
    }

    i = 0;
    while ((i < vectorLeftSize) && (j < vectorRightSize)) {
        if (vectorLeft[i] <= vectorRight[j]) {
            vect[k] = vectorLeft[i];
            i++;
        }
        else {
            vect[k] = vectorRight[j];
            j++;
        }
        k++;
    }

    while (i < vectorLeftSize) {
        vect[k] = vectorLeft[i];
        i++;
        k++;
    }

    while (j < vectorRightSize) {
        vect[k] = vectorRight[j];
        j++;
        k++;
    }
}

// Writes passed vector elements to "merge.out"
void writeToFile(vector<int> &vect, int length) {
    ofstream outputFile("merge.out", ios_base::app); // Open ofstream and enable overwriting

    // Write elements to file
    for (int i = 0; i < length; i++) {
        outputFile << vect[i] << " ";
    }

    outputFile << endl;

    outputFile.close(); // Close ofstream
}