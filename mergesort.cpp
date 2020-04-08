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
void MergeSort(vector<int> &vect, int length);
void writeToFile(vector<int> &vect, int length);

int main() {
    int removeFile = remove("insert.out");
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

            MergeSort(valueVector, len);
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

void MergeSort(vector<int> &vect, int length) {
    

    writeToFile(vect, length);
}

void writeToFile(vector<int> &vect, int length) {
    ofstream outputFile("insert.out", ios_base::app);

    for (int i = 0; i < length; i++) {
        outputFile << vect[i] << " ";
    }

    outputFile << endl;
}