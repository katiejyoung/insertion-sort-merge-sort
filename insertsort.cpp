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

int main() {
    cout << "Hello, world." << endl;
    string list = "data.txt";
    int success = readLines(list);

    if (success == 1) {
        cout << "Insertion sort complete." << endl;
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
            // cout << "Length of vector: " << len << endl;
            // cout << "Size of vector: " << valueVector.size() << endl;

            lineToArray(valueVector, fileLine, len);
            cout << valueVector.at(len - 1) << endl;
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