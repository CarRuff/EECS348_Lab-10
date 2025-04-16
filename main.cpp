#include <iostream>

#include "calculator.hpp"

using namespace std;

int main(int argc, char *argv[]) {

  // variable setup
    string fileName;
    ifstream file;
    string line;
    
    // get file name from user
    cout << "Enter File Name: ";
    getline(cin, fileName);
    
    // add .txt to it
    file.open(fileName+".txt");
    
    
    // loop through each line
    while(getline(file, line)) {
        // if its a valid double
        if(valid(line)) {
            // add to -123.456
            cout << mathStrings(line, "-123.456") + "\n";
        // if its not a valid double
        } else {
            cout << "Not a double \n";
        }
    }
    
    return 0;

}
