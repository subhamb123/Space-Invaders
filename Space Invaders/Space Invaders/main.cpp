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
#include "Missile.hpp"

int main() {
    Scoring s;
    Menu m;

    bool x = false, y = false;

    Clock c;

    RenderWindow window(VideoMode(550, 950), "Space Invaders");

    Texture t1, t2, t3;

    t1.loadFromFile("Ship.jpg");
    Character* ship = new User(Vector2f(225.f, 825.f), t1, Vector2f(0.1f, 0.1f));

    Enemy* enemies[10][5] = { nullptr };
    t2.loadFromFile("Alien.jpg");

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 5; j++)
            enemies[i][j] = new Enemy(Vector2f(25.f + 50 * i, 25.f + 50 * j), t2, Vector2f(0.75f, 0.75f));

    t3.loadFromFile("Missile.jpg");

    vector<Missile*> missiles;
    Missile* missile = new Missile(Vector2f(ship->getPosition().x + 34, ship->getPosition().y - 40), t3, Vector2f(0.1f, 0.1f));

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

        if (Keyboard::isKeyPressed(Keyboard::Space) && c.getElapsedTime().asSeconds() > 0.25) {
            missile = new Missile(Vector2f(ship->getPosition().x + 34, ship->getPosition().y - 40), t3, Vector2f(0.1f, 0.1f));
            missiles.push_back(missile);
            c.restart();
        }

        if (!missiles.empty()) {
            for(int i = 0; i < missiles.size(); i++)
                missiles.at(i)->move(Vector2f(0.f, -0.5f));
        }

        window.clear();
        
        if (!missiles.empty()) {
            for (int i = 0; i < missiles.size(); i++)
                window.draw(*missiles.at(i));
        }

        window.draw(*ship);
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 5; j++)
                if(enemies[i][j]->isAlive())
                    window.draw(*enemies[i][j]);

        window.display();

        if (!missiles.empty()) {
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 5; j++) {
                    for (int k = 0; k < missiles.size(); k++) {
                        if (!missiles.empty() && enemies[i][j]->isAlive() && missiles.at(k)->getPosition().y < enemies[i][j]->getPosition().y && missiles.at(k)->getPosition().x > enemies[i][j]->getPosition().x-20 &&
                            missiles.at(k)->getPosition().x < enemies[i][j]->getPosition().x + 20) {
                            missiles.erase(missiles.begin() + k);
                            enemies[i][j]->kill();
                            x = true;
                            break;
                        }
                    }
                    if (x) {
                        x = false;
                        y = true;
                        break;
                    }
                }
                if (y) {
                    y = false;
                    break;
                }
            }

            if (!missiles.empty() && missiles.back()->getPosition().y < -100)
                missiles.pop_back();
        }
    }

    return 0;
}