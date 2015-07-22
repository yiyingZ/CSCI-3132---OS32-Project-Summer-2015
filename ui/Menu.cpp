//
// Created by nathan on 29/06/15.
//

#include "Menu.h"
#include "UI.h"
#include <iostream>

void Menu::printOptions() {
    std::cout << "Your " << current_menu_->title_ << " menu options (enter the number to choose an option):" << std::endl;
    for(int i = 0; i < current_menu_->items_.size(); i++) {
        std::cout << "(" << i + 1 << ") " << current_menu_->items_[i].title_<< "\t\t";
    }
    std::cout << std::endl;
}

void Menu::selectOption(int option) {
    option --;
    if(option < 0 || option >= items_.size()) {
        UI::println("Invalid option");
    }
    else {
        current_menu_ = &current_menu_->items_[option];
        if(current_menu_->type_ == MenuItemType::COMMAND) {
            UI::print("Starting command: ");
            UI::println(current_menu_->title_);
        }
        else if(current_menu_->type_ == MenuItemType::BACK) {
            current_menu_ = current_menu_->parent_->parent_;
        }
    }
}
