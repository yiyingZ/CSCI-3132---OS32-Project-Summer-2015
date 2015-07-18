//
// Created by nathan on 17/07/15.
//

#ifndef UI_UI_H
#define UI_UI_H

#include <iostream>

class UI {
public:
    static void println(const std::string &);
    static void print(const std::string &);

    template <typename T>
    static T read() {
        T ret;
        std::cin >> ret;
        return ret;
    }
};


#endif //UI_UI_H
