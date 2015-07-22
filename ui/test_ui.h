//
// Created by nathan on 18/07/15.
//

#ifndef UI_TEST_UI_H
#define UI_TEST_UI_H

#include "UI.h"
#include "Menu.h"

/*
 * Test static input / output functions
 */
void test_static_io() {
    UI::println("Testing println");
    UI::print("Testing print");

    UI::println("<< no new line.");

    // enter a string
    UI::println("Enter a string:");
    std::string s = UI::read<std::string>();
    UI::println(s);

    // enter an int
    UI::println("Enter an int:");
    int x = UI::read<int>();
    UI::println(std::to_string(x));
}

void test_user_interface() {
    UI ui;
    ui.startUI();
}

void test_menu() {
    Menu mainMenu
            {"main",
             {
                     {"User Commands", {
                             {"helpme", {}},
                             {"fcreate", {}},
                             {"fread", {}},
                             {"fwrite", {}},
                             {"dcreate", {}},
                             {"currdir", {}},
                             {"listitems", {}},
                             {"chper", {}},
                             {"Back", {}},
                     }},
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
    int option = 0;
    while(option = UI::read<int>()) {
        mainMenu.selectOption(option);
        mainMenu.printOptions();
    }
}

#endif //UI_TEST_UI_H
