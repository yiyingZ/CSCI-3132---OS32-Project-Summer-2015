//
// Created by nathan on 29/06/15.
//

#ifndef UI_MENU_H
#define UI_MENU_H

#include <map>
#include <vector>

class Menu {
    std::string title_;
    std::vector<Menu> items_;
public:
    Menu(const std::string &title, std::vector<Menu> items) : title_(title), items_(items) {}
    Menu(){}
    void printOptions();
};


#endif //UI_MENU_H
