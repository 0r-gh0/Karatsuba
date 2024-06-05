#include <iostream>      // Include the standard input-output stream library
#include <fstream>       // Include the file stream library for file handling
#include <string>        // Include the string library for string handling
#include <sstream>       // Include the string stream library for string stream operations
#include <algorithm>     // Include the algorithm library for utility functions like max()

using namespace std;     // Use the standard namespace

// Function to add two hexadecimal numbers represented as strings
string addHexStrings(const string& a, const string& b) {
    int len1 = a.size();     // Get the length of the first hex string
    int len2 = b.size();     // Get the length of the second hex string
    int carry = 0;           // Initialize carry to 0
    string result = "";      // Initialize result string to empty
    
    // Loop through each digit from the least significant to the most significant
    for (int i = 0; i < max(len1, len2); ++i) {
        // Convert each character to its integer value from hex, or 0 if out of bounds
        int digitA = (i < len1) ? stoi(a.substr(len1 - 1 - i, 1), nullptr, 16) : 0;
        int digitB = (i < len2) ? stoi(b.substr(len2 - 1 - i, 1), nullptr, 16) : 0;
        
        // Calculate sum of the two digits plus carry
        int sum = digitA + digitB + carry;
        carry = sum / 16;    // Calculate new carry
        sum = sum % 16;      // Calculate the current digit
        
        // Append the current digit to the result string
        result = (sum > 9 ? char('a' + (sum - 10)) : char('0' + sum)) + result;
    }
    
    // If there's any carry left, append it to the result
    if (carry) {
        result = (carry > 9 ? char('a' + (carry - 10)) : char('0' + carry)) + result;
    }
    
    return result;  // Return the final result
}

// Function to subtract two hexadecimal numbers represented as strings (a > b)
string subHexStrings(const string& a, const string& b) {
    int len1 = a.size();     // Get the length of the first hex string
    int len2 = b.size();     // Get the length of the second hex string
    int borrow = 0;          // Initialize borrow to 0
    string result = "";      // Initialize result string to empty
    
    // Loop through each digit from the least significant to the most significant
    for (int i = 0; i < len1; ++i) {
        // Convert each character to its integer value from hex
        int digitA = stoi(a.substr(len1 - 1 - i, 1), nullptr, 16);
        int digitB = (i < len2) ? stoi(b.substr(len2 - 1 - i, 1), nullptr, 16) : 0;
        
        // Calculate the difference of the two digits minus borrow
        int diff = digitA - digitB - borrow;
        if (diff < 0) {  // If diff is negative, adjust it and set borrow
            diff += 16;
            borrow = 1;
        } else {         // If diff is non-negative, reset borrow
            borrow = 0;
        }
        
        // Append the current digit to the result string
        result = (diff > 9 ? char('a' + (diff - 10)) : char('0' + diff)) + result;
    }
    
    // Remove leading zeros from the result
    while (result.size() > 1 && result[0] == '0') {
        result.erase(result.begin());
    }
    
    return result;  // Return the final result
}

// Function to multiply two hexadecimal numbers using Karatsuba algorithm
string karatsubaHex(const string& a, const string& b) {
    // Base case: multiply single-digit numbers directly
    if (a.size() == 1 && b.size() == 1) {
        int result = stoi(a, nullptr, 16) * stoi(b, nullptr, 16);  // Multiply single digits
        stringstream ss;  // Create a stringstream
        ss << hex << result;  // Convert the result to hex
        return ss.str();  // Return the hex result as string
    }
    
    // Make the lengths of the strings equal by padding with leading zeros
    int n = max(a.size(), b.size());
    string a_padded = string(n - a.size(), '0') + a;
    string b_padded = string(n - b.size(), '0') + b;
    
    // Divide n by 2
    int n2 = n / 2;
    
    // Split the numbers into high and low parts
    string x = a_padded.substr(0, n - n2);
    string y = a_padded.substr(n - n2);
    string z = b_padded.substr(0, n - n2);
    string w = b_padded.substr(n - n2);
    
    // Recursively compute p, q, and r
    string p = karatsubaHex(x, z);
    string q = karatsubaHex(addHexStrings(x, y), addHexStrings(z, w));
    string r = karatsubaHex(y, w);
    
    // Combine results using the Karatsuba formula
    string p_shifted = p + string(2 * n2, '0');  // p shifted by 2*n2 positions
    string q_minus_p_minus_r = subHexStrings(subHexStrings(q, p), r) + string(n2, '0');  // (q - p - r) shifted by n2 positions
    
    // Return the final combined result
    return addHexStrings(addHexStrings(p_shifted, q_minus_p_minus_r), r);
}

int main() {
    string inputFileName;  // Variable to hold the input file name
    string outputFileName; // Variable to hold the output file name

    // Prompt the user to enter the name of the input file
    cout << "Enter the name of the Input file : ";
    getline(cin, inputFileName);

    // Open the input file
    ifstream inputFile(inputFileName);
    if (!inputFile) {  // Check if the file was opened successfully
        cerr << "Error opening file" << endl;
        return 1;  // Return an error code if file cannot be opened
    }

    // Read the hexadecimal numbers and their lengths from the input file
    string hexA, hexB;
    int sizeA, sizeB;
    inputFile >> hexA >> sizeA;
    inputFile >> hexB >> sizeB;

    // Remove the '0x' prefix from the hexadecimal strings
    hexA = hexA.substr(2);
    hexB = hexB.substr(2);

    // Close the input file
    inputFile.close();

    // Call the Karatsuba multiplication function
    string result = karatsubaHex(hexA, hexB);

    // Ask the user for the output file name
    cout << "Enter the name of the output file: ";
    getline(cin, outputFileName);

    // Open the output file
    ofstream outputFile(outputFileName);
    if (!outputFile) {  // Check if the file was opened successfully
        cerr << "Error opening output file: " << outputFileName << std::endl;
        return 1;  // Return an error code if file cannot be opened
    }

    // Write the result to the output file with '0x' prefix
    outputFile << "0x" << result << endl;

    // Close the output file
    outputFile.close();
    return 0;  // Return success code
}
