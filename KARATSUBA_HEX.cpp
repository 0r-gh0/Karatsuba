#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// Function to add two hexadecimal numbers represented as strings
string addHexStrings(const string& a, const string& b) {
    int len1 = a.size();
    int len2 = b.size();
    int carry = 0;
    string result = "";
    
    for (int i = 0; i < max(len1, len2); ++i) {
        int digitA = (i < len1) ? stoi(a.substr(len1 - 1 - i, 1), nullptr, 16) : 0;
        int digitB = (i < len2) ? stoi(b.substr(len2 - 1 - i, 1), nullptr, 16) : 0;
        
        int sum = digitA + digitB + carry;
        carry = sum / 16;
        sum = sum % 16;
        
        result = (sum > 9 ? char('a' + (sum - 10)) : char('0' + sum)) + result;
    }
    
    if (carry) {
        result = (carry > 9 ? char('a' + (carry - 10)) : char('0' + carry)) + result;
    }
    
    return result;
}

// Function to subtract two hexadecimal numbers represented as strings (a > b)
string subHexStrings(const string& a, const string& b) {
    int len1 = a.size();
    int len2 = b.size();
    int borrow = 0;
    string result = "";
    
    for (int i = 0; i < len1; ++i) {
        int digitA = stoi(a.substr(len1 - 1 - i, 1), nullptr, 16);
        int digitB = (i < len2) ? stoi(b.substr(len2 - 1 - i, 1), nullptr, 16) : 0;
        
        int diff = digitA - digitB - borrow;
        if (diff < 0) {
            diff += 16;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result = (diff > 9 ? char('a' + (diff - 10)) : char('0' + diff)) + result;
    }
    
    // Remove leading zeros
    while (result.size() > 1 && result[0] == '0') {
        result.erase(result.begin());
    }
    
    return result;
}

// Function to multiply two hexadecimal numbers using Karatsuba algorithm
string karatsubaHex(const string& a, const string& b) {
    // Base case: multiply single-digit numbers directly
    if (a.size() == 1 && b.size() == 1) {
        int result = stoi(a, nullptr, 16) * stoi(b, nullptr, 16);
        stringstream ss;
        ss << hex << result;
        return ss.str();
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
    string p_shifted = p + string(2 * n2, '0');
    string q_minus_p_minus_r = subHexStrings(subHexStrings(q, p), r) + string(n2, '0');
    
    return addHexStrings(addHexStrings(p_shifted, q_minus_p_minus_r), r);
}

int main() {
    // Open the input file
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    // Read the hexadecimal numbers and their lengths
    string hexA, hexB;
    int sizeA, sizeB;
    inputFile >> hexA >> sizeA;
    inputFile >> hexB >> sizeB;

    // Remove the '0x' prefix from the hexadecimal strings
    hexA = hexA.substr(2);
    hexB = hexB.substr(2);

    // Close the input file
    inputFile.close();

    // Call the karatsuba function
    string result = karatsubaHex(hexA, hexB);

    // Print the result in hexadecimal format
    cout << "0x" << result << endl;

    return 0;
}