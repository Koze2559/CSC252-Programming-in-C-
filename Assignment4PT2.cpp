#include <iostream>
#include <string>
using namespace std;

// Recursive function to convert decimal to binary
string decimalToBinary(int number)
{
    if (number == 0)
        return "";

    int digit;

    if (number % 2 == 0)
        digit = 0;   // even
    else
        digit = 1;   // odd

    // Recursive call first, then add digit when returning
    return decimalToBinary(number / 2) + char(digit + '0');
}

int main()
{
    int number;

    cout << "Enter a decimal integer: ";
    cin >> number;

    if (number == 0)
        cout << "Binary equivalent: 0" << endl;
    else
        cout << "Binary equivalent: " << decimalToBinary(number) << endl;

    return 0;
}