/************************************************************************
* Programmers: Subham, Ryan, Danielle, Manjesh                          *
* Class: CptS 122                                                       *
* Programming Assignment: PA 9 - Space Invaders                         *
* Date: 4/17/2021                                                       *
* Description: This program emulates space invaders.                    *
************************************************************************/

#include "Menu.hpp"

/****************************************************************
* Class Function: Menu()                                        *
* Date Created: 4/17/2021                                       *
* Date Last Modified: 4/17/2021                                 *
* Description: Constructor                                      *
* Input parameters: int                                         *
* Returns: Nothing                                              *
* Preconditions: int                                            *
* Postconditions: An object has been created                    *
*****************************************************************/
Menu::Menu(int userChoice) {
	this->userChoice = userChoice;
}

/****************************************************************
* Class Function: displayMenu()                                 *
* Date Created: 4/17/2021                                       *
* Date Last Modified: 4/17/2021                                 *
* Description: Displays the menu waiting for user input         *
* Input parameters: RenderWindow*, int&, int&, bool&            *
* Returns: Nothing                                              *
* Preconditions: RenderWindow*, int&, int&, bool&               *
* Postconditions: The menu has been displayed                   *
*****************************************************************/
void Menu::displayMenu(RenderWindow* window, int& score, int& lives, bool& indicator, bool& no_test)
{
	window->clear();
	bool x = true;

	Font font;
	font.loadFromFile("font.ttf");

	Text options, instructions;
	options.setFont(font);
	options.setCharacterSize(20);
	options.setPosition(0.f, 0.f);
	options.setFillColor(Color::White);
	options.setString("Welcome to Space Invaders!\n\nBasic gameplay: \nThe player controls the cannon at the bottom of \nthe screen, which can move only horizontally. \nThe aliens moves both horizontally and \nvertically (approaching the cannon). The cannon \ncan be controlled to shoot laser to destroy the \naliens, while the aliens will randomly shoot \ntowards the cannon. If an alien is shot by the \ncannon, it is destroyed; if the cannon is shot, \none life is lost. However, the position of the \naliens will not be reset if the cannon is lost. \nThe initial number of lives is five.\n\nEnter the option on your keyboard you would \nlike to proceed with:\n1. Play Game\n2. Run Test Cases\n3. Exit Game");

	window->draw(options);
	window->display();
	if (Keyboard::isKeyPressed(Keyboard::Num1)) {
		userChoice = 1;
		indicator = false;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Num2)) {
		userChoice = 2;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Num3)) {
		indicator = false;
		userChoice = 3;
	}

	if (userChoice == 1) {
		score = 0;
		lives = 5;
	}

	else if (userChoice == 2)
		no_test = false;

	else if (userChoice == 3)
		window->close();
}

/****************************************************************
* Class Function: getUserChoice()                               *
* Date Created: 4/17/2021                                       *
* Date Last Modified: 4/17/2021                                 *
* Description: Returns user choice                              *
* Input parameters: Nothing                                     *
* Returns: int                                                  *
* Preconditions: Nothing                                        *
* Postconditions: User choice has been returned                 *
*****************************************************************/
int Menu::getUserChoice() const {
	return userChoice;
}

/****************************************************************
* Class Function: setUserChoice()                               *
* Date Created: 4/17/2021                                       *
* Date Last Modified: 4/17/2021                                 *
* Description: Sets user choice                                 *
* Input parameters: int                                         *
* Returns: Nothing                                              *
* Preconditions: int                                            *
* Postconditions: Choice has been changed                       *
*****************************************************************/
void Menu::setUserChoice(int choice) {
	userChoice = choice;
}