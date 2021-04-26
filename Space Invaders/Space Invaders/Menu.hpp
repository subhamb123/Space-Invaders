#pragma once

#include "header.hpp"

class Menu {
public:
    Menu(int userChoice = 0);
    ~Menu();
    void displayMenu(RenderWindow* window, int& score, int& lives, bool& b);

    int userChoice;
};