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
void sortElements(vector<int> &vect, int length);
void mergeSort(vector<int> &vect, int left, int right);
void merge(vector<int> &vect, int left, int right, int middle);
void writeToFile(vector<int> &vect, int length);

int main() {
    int removeFile = remove("merge.out"); // Delete output file in case program has already been run
    string list = "data.txt";
    int success = generateList(); // Initiate program

    // Output message according to program success
    if (success == 1) {
        cout << "Merge sort complete." << endl;
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
        sortElements(valueVector, len);
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

// Initiates sort and outputs results when complete
void sortElements(vector<int> &vect, int length) {
    double duration;
    time_t start, end;
    time(&start); // Set start time

    // Initiate sort
    mergeSort(vect, 0, (length - 1));

    time(&end); // Set end time
    duration = double(end - start); // Calculate time duration
    cout.precision(2);
    cout << fixed << duration << " seconds have passed" << endl;

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