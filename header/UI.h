//
// Created by nathan on 17/07/15.
//

#ifndef UI_UI_H
#define UI_UI_H

#include <vector>
#include <iostream>

class UI {
private:
    /*
     * Validates that this command is a valid system command.
     */
    bool commandValidate(std::vector<std::string> &cmd);

    /*
     * Splits the command entered by the user into a vector of strings
     */
    std::vector<std::string> parseCommand(const std::string &line);
public:

    /*
     * Starts the shell / command parsing loop.
     */
    void startUI();

    /*
     * Prints a line to stdout with a new line after
     */
    static void println(const std::string &);

    /*
     * Prints a line to stdout without a new line after
     */
    static void print(const std::string &);

    /*
     * Reads the parametrised type from stdin and returns it.
     */
    template <typename T>
    static T read() {
        T ret;
        std::cin >> ret;
        return ret;
    }

    /*
     * Reads the parametrised type from stdin and returns it.
     */
    static std::string readLine() {
        std::string line;
        std::getline(std::cin, line);
        return line;
    }
};


#endif //UI_UI_H
