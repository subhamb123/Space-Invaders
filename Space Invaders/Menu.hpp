/************************************************************************
* Programmers: Subham, Ryan, Danielle, Manjesh                          *
* Class: CptS 122                                                       *
* Programming Assignment: PA 9 - Space Invaders                         *
* Date: 4/17/2021                                                       *
* Description: This program emulates space invaders.                    *
************************************************************************/

#pragma once

#include "header.hpp"

class Menu {
public:
    Menu(int userChoice = 0);
    void displayMenu(RenderWindow* window, int& score, int& lives, bool& indicator, bool& no_test);
    int getUserChoice() const;
    void setUserChoice(int choice);

private:
    int userChoice;
};