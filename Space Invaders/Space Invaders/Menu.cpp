#include "Menu.hpp"

Menu::Menu(int userChoice) {
	this->userChoice = userChoice;
}

Menu::~Menu() {

}

void Menu::displayMenu(RenderWindow* window, int& score, int& lives, bool& b)
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
	options.setString("Welcome to Space Invaders!\n\nBasic gameplay: \nThe player controls the cannon at the bottom of \nthe screen, which can move only horizontally. \nThe aliens moves both horizontally and \nvertically (approaching the cannon). The cannon \ncan be controlled to shoot laser to destroy the \naliens, while the aliens will randomly shoot \ntowards the cannon. If an alien is shot by the \ncannon, it is destroyed; if the cannon is shot, \none life is lost. However, the position of the \naliens will not be reset if the cannon is lost. \nThe initial number of lives is three.\n\nEnter the option you would like to proceed with:\n1. Play Game\n2. Exit Game");

	window->draw(options);
	window->display();
	if (Keyboard::isKeyPressed(Keyboard::Num1)) {
		userChoice = 1;
		b = false;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Num2)) {
		userChoice = 2;
	}

	if (userChoice == 1) {
		score = 0;
		lives = 5;
	}

	else if (userChoice == 2)
	{
		window->close();
		b = false;
	}
}