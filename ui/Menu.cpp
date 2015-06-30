//
// Created by nathan on 29/06/15.
//

#include "Menu.h"
#include <iostream>

void Menu::printOptions() {
    std::cout << "Your " << title_ << " menu options (enter the number to choose an option):" << std::endl;
    for(int i = 0; i < items_.size(); i++) {
        std::cout << "(" << i + 1 << ") " << items_[i].title_<< "\t\t";
    }
    std::cout << std::endl;
}
