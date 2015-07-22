//
// Created by nathan on 17/07/15.
//

#include <iterator>
#include <sstream>
#include <algorithm>
#include "Login.cpp"
#include "UI.h"

void UI::println(const std::string &msg) {
    std::cout << msg << std::endl;
}

void UI::print(const std::string &msg) {
    std::cout << msg;
}

void UI::startUI() {
    // Authenticate User:
    Login l;
    std::string username = l.login();

    // Start prompt
    std::string prompt = username + "@OS32-Menu> ";

    UI::println("Your main menu options");
    UI::print(prompt);

    int option = 0;
    while( option = UI::read<int>()) {
        if(option == 1) { // Parse user command
            std::string line = UI::readLine();
            auto cmd = parseCommand(line);
            if(commandValidate(cmd)) {
                // scheduler->invokeCommand(cmd)
            }
        }
        else if(option == 2) { // Start utilties
            new Utilities();
        }
        else if(option == 3) { // Shutdown
            break;
        }
        else {
            UI::println("Invalid option.");
        }

        UI::println("Your main menu options");
        UI::print(prompt);
    }
}

std::vector<std::string> UI::parseCommand(const std::string &line) {
    std::istringstream iss;
    std::vector<std::string> command_tokens;
    std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(command_tokens));

    return command_tokens;
}

bool UI::commandValidate(std::vector<std::string> &cmd) {
    return false;
}
