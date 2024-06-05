#include <iostream>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <math.h>

using namespace std;

// Function to compute a*b using Karatsuba algorithm
long long karatsuba(long long a, long long b)
{
    // Base case: return a*b if a or b is less than 10
    // This is the stopping condition for the recursive calls
    if (a < 10 || b < 10)
        return a*b;

    // Calculate the length of the two numbers
    int n = max(to_string(a).length(), to_string(b).length());

    // Divide n by 2
    int n2 = n / 2;

    // Split the numbers into high and low digits
    // x and z are the high digits, y and w are the low digits
    long long x = a / (long long)pow(10, n2);
    long long y = a % (long long)pow(10, n2);
    long long z = b / (long long)pow(10, n2);
    long long w = b % (long long)pow(10, n2);

    // Recursively compute p, q, and r
    // p = x*z
    // q = (x+y)*(z+w)
    // r = y*w
    long long p = karatsuba(x, z);
    long long q = karatsuba(x + y, z + w);
    long long r = karatsuba(y, w);

    // Return the final result using the Karatsuba formula
    // a*b = (10^(2*n2))*p + (10^n2)*(q-p-r) + r
    return (long long)pow(10, 2 * n2) * p + (long long)pow(10, n2) * (q - p - r) + r;
}

int main()
{
    // Read in the two numbers to be multiplied
    long long a, b;
    cin >> a >> b;

    // Call the karatsuba function and print the result
    cout << karatsuba(a, b) << endl;
    return 0;
}