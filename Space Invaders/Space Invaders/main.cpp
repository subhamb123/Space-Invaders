/************************************************************************
* Programmers: Subham, Ryan, Danielle, Manjesh                          *
* Class: CptS 122                                                       *
* Programming Assignment: PA 9 - Space Invaders                         *
* Date: 4/17/2021                                                       *
* Description: This program emulates space invaders.                    *
************************************************************************/

#include "header.hpp"
#include "Scoring.hpp"
#include "Menu.hpp"
#include "User.hpp"
#include "Enemy.hpp"

int main() {
	Scoring s;
	Menu m;

	RenderWindow window(VideoMode(550, 950), "Space Invaders");

	Texture t1, t2;

	t1.loadFromFile("Ship.jpg");
	Character* ship = new User(Vector2f(225.f, 825.f), t1, Vector2f(0.1f, 0.1f));

	Character* enemies[10] = { nullptr };
	t2.loadFromFile("Alien.jpg");
	for (int i = 0; i < 10; i++)
		enemies[i] = new Enemy(Vector2f(25.f + 50 * i, 25.f), t2, Vector2f(1.f, 1.f));

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		if (ship->getPosition().x + 105 != window.getSize().x && (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)))
				ship->move(0.5, 0);

		if (ship->getPosition().x != 0 && (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)))
				ship->move(-0.5, 0);
		
		window.clear();

		window.draw(*ship);
		for (int i = 0; i < 10; i++)
			window.draw(*enemies[i]);

		window.display();
	}

	return 0;
}