//
// Created by nathan on 17/07/15.
//

#include "UI.h"

/*
 * Prints a line to stdout with a new line after
 */
void UI::println(const std::string &msg) {
    std::cout << msg << std::endl;
}

/*
 * Prints a line to stdout without a new line after
 */
void UI::print(const std::string &msg) {
    std::cout << msg;
}
