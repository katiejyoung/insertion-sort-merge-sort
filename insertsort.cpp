#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int readLines(string dataFile);
void lineToArray();

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

    if (inputFile.is_open()) {
        while(getline(inputFile, fileLine)) {
            cout << fileLine << endl;
        }

        inputFile.close();
        return 1;
    }

    else {
        return 0;
    }
    
}

void lineToArray() {

}