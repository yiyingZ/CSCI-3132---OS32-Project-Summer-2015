//
// Created by Aymen Ben Rkhis on 7/18/15.
//

#include "Palindrome.h"
#include <string>
#include <sstream>

using namespace std;
using namespace Utilities;


void Palindrome::execute() {
    palindrome();
}

/*
 * Input a string and check if it is palindrome
 * Output the result
 */
void Palindrome::palindrome() {
    string input;
    cout << "Input a string: ";
    cin >> input;
    if (input == string(input.rbegin(), input.rend())) {
        cout << input << " is a palindrome" << endl;
    }
    else cout << input << "is not palindrome" << endl;
}
