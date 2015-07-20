#include <iostream>
#include "ui/Menu.h"
#include "ui/parser.h"

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

  parser *syntax;
  syntax = new parser;

  string cmdLine;

  cout << "Enter a string: " << endl;

  getline(cin, cmdLine);

  syntax->parsing(cmdLine);
  syntax->displayToken();
    return EXIT_SUCCESS;
}