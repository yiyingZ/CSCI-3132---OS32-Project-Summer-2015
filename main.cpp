#include <iostream>
#include "ui/Menu.h"

using namespace std;


int main() {
    Menu mainMenu
            {"main",
                {
                        {"User Commands", {}},
                        {"Utilties", {
                                {"Encryption", {}},
                                {"Calculator", {}},
                                {"Message of the Day", {}},
                                {"Converter", {}},
                                {"Date and Time", {}},
                                {"Palindrome Checker", {}},
                                {"Exit Checker", {}},
                        }},
                        {"Shutdown", {}}
                }
            };
    mainMenu.printOptions();
    return 0;
}