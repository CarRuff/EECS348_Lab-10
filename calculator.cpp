#include "calculator.hpp"

// Valid Function
// Checks if an input is a valid double
bool valid(const string& input) {
    
    // Variable setup
    int x = input.length();
    bool doubletest = true;
    bool dot = false;
    bool hasSign = false;
    bool digitSeenBeforeDot = false;
    bool digitSeenAfterDot = false;
    
    // for every digit in the string
    for (int i = 0; i < x; i++) {
        char y = input[i];

        // If it is a '+' or '-'
        if (y == '+' || y == '-') {
            // If hasSign is already true, then not a double
            if (i != 0 || hasSign) {
                doubletest = false;
            //If hasSign is false set to true
            } else {
                hasSign = true;
            }
        }
        // If it is a '.'
        else if (y == '.') {
            // if dot is true then, its not a double
            if (dot) {
                doubletest = false;
            // if dot is false set it to true
            } else {
                dot = true;
            }
        }
        // test for it to be a number
        else if (y >= '0' && y <= '9') {
            if (!dot)
                digitSeenBeforeDot = true;
            else
                digitSeenAfterDot = true;
        }
        // If its not a number than its not a double
        else {
            doubletest = false;
        }
    }
    
    // If make sure both sides of the dot have numbers
    if (!digitSeenBeforeDot && !digitSeenAfterDot)
        doubletest = false;
    if (dot && !digitSeenAfterDot)
        doubletest = false;

    // Return
    return doubletest;
}

// addStrings Function
// Adds two strings
string addStrings(string x, string y) {
    
    // Variable setup 
    string result = "";
    int carry = 0;
    
    // fill in spots with 0 so both are equal length
    while (x.length() < y.length()) x = "0" + x;
    while (y.length() < x.length()) y = "0" + y;
    
    // loop through each digit adding them
    for (int i = x.length() - 1; i >= 0; i--) {
        int sum = (x[i] - '0') + (y[i] - '0') + carry;
        carry = sum / 10;
        result = char((sum % 10) + '0') + result;
    }
    
    // add carry
    if (carry)
        result = '1' + result;

    return result;
}

// subtractStrings Variable
// subtracts two strings
string subtractStrings(string x, string y) {
    
    // variable setup
    string result = "";
    int borrow = 0;
    
    // fill in spots with 0 so both are equal length
    while (x.length() < y.length()) x = "0" + x;
    while (y.length() < x.length()) y = "0" + y;
    
    // loop through while subtracting each number
    for (int i = x.length() - 1; i >= 0; i--) {
        // Convert to ints
        int a = x[i] - '0';
        int b = y[i] - '0' + borrow;
        // barrowing
        if (a < b) {
            a += 10;
            borrow = 1;
        // No barrow needed
        } else {
            borrow = 0;
        }
        // calculate diffrence
        result = char((a - b) + '0') + result;
    }
    
    // remove 0s
    int pos = 0;
    while (pos < result.size() - 1 && result[pos] == '0') pos++;
    
    // return
    return result.substr(pos);
}

string mathStrings(string x, string y) {
    
    // variable setup
    bool negX = false;
    bool negY = false;
    
    // test for negative numbers
    if (x[0] == '-') {
        negX = true;
        x = x.substr(1);
    }
    if (y[0] == '-') {
        negY = true;
        y = y.substr(1);
    }
    
    // More Variables
    string intX = x;
    string intY = y;
    string decX = "";
    string decY = "";
    int dotPosX = x.find('.');
    int dotPosY = y.find('.');
    
    // Split each part at the "."
    if (dotPosX != string::npos) {
        intX = x.substr(0, dotPosX);
        decX = x.substr(dotPosX + 1);
    }
    if (dotPosY != string::npos) {
        intY = y.substr(0, dotPosY);
        decY = y.substr(dotPosY + 1);
    }

    // make sure they are the same length
    while (decX.length() < decY.length()) decX += "0";
    while (decY.length() < decX.length()) decY += "0";
    while (intX.length() < intY.length()) intX = "0" + intX;
    while (intY.length() < intX.length()) intY = "0" + intY;

    // merge both parts
    string numX = intX + decX;
    string numY = intY + decY;
    // setup result variable
    string result;
    
    // If they are both negative just do adding
    if (negX == negY) {
        result = addStrings(numX, numY);
        if (negX) result = "-" + result;
    // if one is negative and they other isn't do subtraction
    } else {
        // variable setup
        bool xGreater = false;
        // Find which one is greater
        if (numX.length() > numY.length()) xGreater = true;
        else if (numX.length() < numY.length()) xGreater = false;
        else xGreater = numX >= numY;
        
        // based on which one is larger preform subtraction
        if (xGreater) {
            result = subtractStrings(numX, numY);
            if (negX) result = "-" + result;
        } else {
            result = subtractStrings(numY, numX);
            if (negY) result = "-" + result;
        }
    }
        
    // add '.' back into the correct spot
    int decLen = max(decX.length(), decY.length());
    if (decLen > 0) {
        while (result.length() <= decLen) result = "0" + result;
        result.insert(result.length() - decLen, ".");
    }
    
    // result
    return result;
}
