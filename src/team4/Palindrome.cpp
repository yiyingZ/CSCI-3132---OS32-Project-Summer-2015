//
// Created by Aymen Ben Rkhis on 7/18/15.
//

#include "Palindrome.h"
#include "UI.h"
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
    UI::print("Input a string: ");
    input = UI::readLine();
    if (input == string(input.rbegin(), input.rend())) {
        UI::println(input+" is a palindrome");
    }
    else UI::println(input+"is not palindrome");
}
