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
    int removeFile = remove("merge.out");
    string list = "data.txt";
    int success = readLines(list);

    if (success == 1) {
        cout << "Merge sort complete." << endl;
    }
    else {
        cout << "Error: Failed to open file." << endl;
    }

    return 0;
}

int readLines(string dataFile) {
    string fileLine;
    ifstream inputFile(dataFile.c_str());
    int len;
    vector<int> valueVector;


    if (inputFile.is_open()) {
        while(getline(inputFile, fileLine)) {
            len = getVectorSize(fileLine);
            valueVector.resize(len);

            lineToArray(valueVector, fileLine, len);

            sortElements(valueVector, len);
            valueVector.clear();
        }

        inputFile.close();
        return 1;
    }

    else {
        return 0;
    }
    
}

int getVectorSize(string dataString) {
    int dataItr = 0;
    int dataValue = 0;
    string dataItem;

    while (dataItr <= dataString.length()) {
        if ((dataString[dataItr] == ' ') || (dataItr == dataString.length())) {
            dataValue = atoi(dataItem.c_str());
            return dataValue;
        }
        else {
            dataItem += dataString[dataItr];
        }

        dataItr++;
    }

    return 0;
}

void lineToArray(vector<int> &vect, string dataString, int length) {
    int dataItr = 0;
    int vectorItr = 0;
    int isLength = 1;
    int dataValue = 0;
    string dataItem;

    while ((dataItr <= dataString.length()) && (vectorItr < length)) {
        if ((dataString[dataItr] == ' ') || (dataItr == dataString.length())) {
            dataValue = atoi(dataItem.c_str());
            
            if (isLength != 1) {
                vect[vectorItr] = dataValue;
                vectorItr++;
            }
            else {
                isLength = 0;
            }
            
            dataValue = 0;
            dataItem = "";
        }
        else {
            dataItem += dataString[dataItr];
        }

        dataItr++;
    }

}

void sortElements(vector<int> &vect, int length) {
    mergeSort(vect, 0, (length - 1));

    writeToFile(vect, length);
}

void mergeSort(vector<int> &vect, int left, int right) {
    if (left < right) {
        int middle = (left + right)/2;
        // cout << "Left index: " << left << endl;
        // cout << "Middle index: " << middle << endl;
        // cout << "Right index: " << right << endl;

        // cout << "Sorting left-middle index: " << left << ", " << middle << endl;
        mergeSort(vect, left, middle);
        // cout << "Sorting middle+1-right index: " << (middle + 1) << ", " << right << endl;
        mergeSort(vect, (middle + 1), right);

        merge(vect, left, right, middle);

        // cout << "Merged vector: ";
        // for (int i = 0; i <= right; i++) {
        //     cout << vect[i] << " ";
        // }
        // cout << endl;
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

    // cout << "Left Vector: ";
    for (i = 0; i < vectorLeftSize; i++) {
        vectorLeft[i] = vect[left + i];
        // cout << vectorLeft[i] << " ";
    }
    // cout << endl << "Right Vector: ";
    for (i = 0; i < vectorRightSize; i++) {
        vectorRight[i] = vect[middle + i + 1];
        // cout << vectorRight[i] << " ";
    }
    // cout << endl;

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

    // cout << "Updated Vector: ";
    // for (i = 0; i < 4; i++) {
    //     cout << vect[i] << " ";
    // }
    // cout << endl;
}

void writeToFile(vector<int> &vect, int length) {
    ofstream outputFile("merge.out", ios_base::app);

    for (int i = 0; i < length; i++) {
        outputFile << vect[i] << " ";
    }

    outputFile << endl;
}