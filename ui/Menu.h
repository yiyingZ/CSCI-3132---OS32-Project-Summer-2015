//
// Created by nathan on 29/06/15.
//

#ifndef UI_MENU_H
#define UI_MENU_H

#include <iostream>
#include <map>
#include <vector>

enum class MenuItemType {
    SUB_MENU, COMMAND, BACK
};

class Menu {
private:
    class Builder;
    std::string title_;
    std::vector<Menu> items_;
    MenuItemType type_;

public:
    Menu *parent_ = nullptr;
    Menu *current_menu_ = nullptr;


public:
    Menu(const std::string &title, std::vector<Menu> items) : title_(title), items_(items), current_menu_(this) {
        for(Menu m : items) {
            m.parent_ = this;
        }
        if(items.size() == 0) {
            type_ = MenuItemType::COMMAND;
        }
        else {
            items.back().type_ = MenuItemType::BACK;
        }
    }
    Menu(){}

    /*
     * Prints options of the current menu.
     */
    void printOptions();
    void selectOption(int choice);
};

class Menu::Builder {

};

#endif //UI_MENU_H
