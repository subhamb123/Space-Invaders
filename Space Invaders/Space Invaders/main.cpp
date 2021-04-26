/************************************************************************
* Programmers: Subham, Ryan, Danielle, Manjesh                          *
* Class: CptS 122                                                       *
* Programming Assignment: PA 9 - Space Invaders                         *
* Date: 4/17/2021                                                       *
* Description: This program emulates space invaders.                    *
************************************************************************/

#include "header.hpp"
#include "Menu.hpp"
#include "User.hpp"
#include "Enemy.hpp"
#include "Missile.hpp"

int main() {
    srand((unsigned)time(nullptr));

    Menu m;

    bool x = false, y = false, z = false, a = true, b = true, d = true, dir = true; //These help with breaking loops, so names aren't descriptive.
    int level = 1, lives = 5, score = 0, tChange1 = 1, tChange2 = 1, tChange3 = 1;

    Clock c, c2;

    RenderWindow window(VideoMode(950, 950), "Space Invaders");

    Texture t1, t2, t3, t4, t5, t6, t7, t8;

    SoundBuffer buffer;
    SoundBuffer buffer2;
    buffer.loadFromFile("shoot.wav");
    buffer2.loadFromFile("invaderkilled.wav");

    Sound missile_sound;
    Sound invader_killed;

    missile_sound.setBuffer(buffer);
    invader_killed.setBuffer(buffer2);

    invader_killed.setVolume(5.f);
    missile_sound.setVolume(5.f);

    Text scoreT, livesT, levelT, scoreEnd, levelEnd, endMessage;
    Font font;
    font.loadFromFile("font.ttf");

    scoreT.setFont(font);
    livesT.setFont(font);
    levelT.setFont(font);
    scoreEnd.setFont(font);
    levelEnd.setFont(font);
    endMessage.setFont(font);

    scoreT.setCharacterSize(25);
    livesT.setCharacterSize(25);
    levelT.setCharacterSize(25);
    scoreEnd.setCharacterSize(25);
    levelEnd.setCharacterSize(25);
    endMessage.setCharacterSize(25);

    scoreT.setFillColor(Color::White);
    livesT.setFillColor(Color::White);
    levelT.setFillColor(Color::White);
    scoreEnd.setFillColor(Color::White);
    levelEnd.setFillColor(Color::White);
    endMessage.setFillColor(Color::White);

    scoreT.setPosition(Vector2f(75.f, 0.f));
    livesT.setPosition(Vector2f(375.f, 0.f));
    levelT.setPosition(Vector2f(675.f, 0.f));
    scoreEnd.setPosition(Vector2f(175.f, 450.f));
    levelEnd.setPosition(Vector2f(475.f, 450.f));
    endMessage.setPosition(Vector2f(175.f, 500.f));

    endMessage.setString("Press enter to continue...");

    t1.loadFromFile("Ship.jpg");
    Character* ship = new User(Vector2f(425.f, 825.f), t1, Vector2f(0.1f, 0.1f));

    Character* enemies[10][5] = { nullptr };
    t2.loadFromFile("Alien.jpg");

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 5; j++)
            enemies[i][j] = new Enemy(Vector2f(175.f + 60 * i, 100.f + 50 * j), t2, Vector2f(0.75f, 0.75f));

    t3.loadFromFile("Missile.jpg");
    vector<Missile*> missiles;

    t4.loadFromFile("enemyMissile.jpg");
    vector<Missile*> enemyM;

    Missile* missile = nullptr;
    Missile* enemyMi = nullptr;

    vector<Texture> shieldT1;
    vector<Texture> shieldT2;
    vector<Texture> shieldT3;

    t5.loadFromFile("Shield1.jpg");
    t6.loadFromFile("Shield2.jpg");
    t7.loadFromFile("Shield3.jpg");
    t8.loadFromFile("Shield4.jpg");

    shieldT1.push_back(t5);
    shieldT1.push_back(t6);
    shieldT1.push_back(t7);
    shieldT1.push_back(t8);
    shieldT2.push_back(t5);
    shieldT2.push_back(t6);
    shieldT2.push_back(t7);
    shieldT2.push_back(t8);
    shieldT3.push_back(t5);
    shieldT3.push_back(t6);
    shieldT3.push_back(t7);
    shieldT3.push_back(t8);

    Sprite shieldS1(shieldT1.at(0));
    Sprite shieldS2(shieldT2.at(0));
    Sprite shieldS3(shieldT3.at(0));

    shieldS1.setPosition(Vector2f(125.f, 650.f));
    shieldS2.setPosition(Vector2f(425.f, 650.f));
    shieldS3.setPosition(Vector2f(725.f, 650.f));

    shieldS1.setScale(Vector2f(0.5f, 0.5f));
    shieldS2.setScale(Vector2f(0.5f, 0.5f));
    shieldS3.setScale(Vector2f(0.5f, 0.5f));

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        while (b)
            m.displayMenu(&window, score, lives, b);

        scoreT.setString("Score: " + to_string(score));
        livesT.setString("Lives: " + to_string(lives));
        levelT.setString("Level: " + to_string(level));

        if (ship->getPosition().x + 105 != window.getSize().x && (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)))
            ship->move(0.5, 0);

        if (ship->getPosition().x != 0 && (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)))
            ship->move(-0.5, 0);

        if (Keyboard::isKeyPressed(Keyboard::Space) && c.getElapsedTime().asSeconds() > 0.25) {
            missile = new Missile(Vector2f(ship->getPosition().x + 34, ship->getPosition().y - 40), t3, Vector2f(0.1f, 0.1f));
            missiles.push_back(missile);
            c.restart();
            missile_sound.play();
        }

        if (c2.getElapsedTime().asMilliseconds() > 1075 - level * 75) {
            int x_coor = rand() % 10, y_coor = rand() % 5;
            while (!(dynamic_cast <Enemy*> (enemies[x_coor][y_coor]))->isAlive())
                x_coor = rand() % 10, y_coor = rand() % 5;
            enemyMi = new Missile(Vector2f(enemies[x_coor][y_coor]->getPosition().x + 7, enemies[x_coor][y_coor]->getPosition().y), t4, Vector2f(0.05f, 0.05f));
            enemyM.push_back(enemyMi);
            c2.restart();
        }

        if (!missiles.empty()) {
            for (int i = 0; i < missiles.size(); i++)
                missiles.at(i)->move(Vector2f(0.f, -0.5f));
        }

        if (!enemyM.empty()) {
            for (int i = 0; i < enemyM.size(); i++)
                enemyM.at(i)->move(Vector2f(0.f, 0.5f));
        }

        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 5; j++)
                if ((dynamic_cast <Enemy*> (enemies[i][j]))->isAlive() && (enemies[i][j]->getPosition().x > 915 || enemies[i][j]->getPosition().x < 0)) {
                    dir = !dir;
                    for (int i = 0; i < 10; i++)
                        for (int j = 0; j < 5; j++)
                            enemies[i][j]->move(Vector2f(0.f, (float)(9 + level)));
                }

        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 5; j++) {
                if (dir)
                    enemies[i][j]->move(Vector2f((float)(level * 0.1), 0.f));
                else
                    enemies[i][j]->move(Vector2f((float)(level * (-0.1)), 0.f));
            }

        window.clear();

        window.draw(scoreT);
        window.draw(livesT);
        window.draw(levelT);

        window.draw(shieldS1);
        window.draw(shieldS2);
        window.draw(shieldS3);

        if (!missiles.empty()) {
            for (int i = 0; i < missiles.size(); i++)
                window.draw(*missiles.at(i));
        }

        if (!enemyM.empty()) {
            for (int i = 0; i < enemyM.size(); i++)
                window.draw(*enemyM.at(i));
        }

        window.draw(*ship);
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 5; j++)
                if ((dynamic_cast <Enemy*> (enemies[i][j]))->isAlive())
                    window.draw(*enemies[i][j]);

        if (!missiles.empty()) {
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 5; j++) {
                    for (int k = 0; k < missiles.size(); k++) {
                        if (!missiles.empty() && (dynamic_cast <Enemy*> (enemies[i][j]))->isAlive() && missiles.at(k)->getPosition().y < enemies[i][j]->getPosition().y && missiles.at(k)->getPosition().x >
                            enemies[i][j]->getPosition().x - 20 && missiles.at(k)->getPosition().x < enemies[i][j]->getPosition().x + 20) {
                            missiles.erase(missiles.begin() + k);
                            (dynamic_cast <Enemy*> (enemies[i][j]))->kill();
                            invader_killed.play();
                            score += level * 10;
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

        //New code

        if (!enemyM.empty()) {
            for (int i = 0; i < enemyM.size(); i++) {
                if (!enemyM.empty() && enemyM.at(i)->getPosition().y > ship->getPosition().y && enemyM.at(i)->getPosition().x > ship->getPosition().x - 20 && enemyM.at(i)->getPosition().x < ship->getPosition().x + 120) {
                    enemyM.erase(enemyM.begin() + i);
                    lives--;
                }

                if (!enemyM.empty() && enemyM.at(i)->getPosition().y > shieldS1.getPosition().y && enemyM.at(i)->getPosition().x > shieldS1.getPosition().x - 20 && enemyM.at(i)->getPosition().x < shieldS1.getPosition().x + 120 &&
                    tChange1 <= 3) {
                    enemyM.erase(enemyM.begin() + i);
                    shieldS1.setTexture(shieldT1.at(tChange1));
                    tChange1++;
                }
                if (!enemyM.empty() && enemyM.at(i)->getPosition().y > shieldS2.getPosition().y && enemyM.at(i)->getPosition().x > shieldS2.getPosition().x - 20 && enemyM.at(i)->getPosition().x < shieldS2.getPosition().x + 120 &&
                    tChange2 <= 3) {
                    enemyM.erase(enemyM.begin() + i);
                    shieldS2.setTexture(shieldT2.at(tChange2));
                    tChange2++;
                }
                if (!enemyM.empty() && enemyM.at(i)->getPosition().y > shieldS3.getPosition().y && enemyM.at(i)->getPosition().x > shieldS3.getPosition().x - 20 && enemyM.at(i)->getPosition().x < shieldS3.getPosition().x + 120 &&
                    tChange3 <= 3) {
                    enemyM.erase(enemyM.begin() + i);
                    shieldS3.setTexture(shieldT3.at(tChange3));
                    tChange3++;
                }
            }

            if (!enemyM.empty() && enemyM.back()->getPosition().y > 1050)
                enemyM.pop_back();
        }


        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 5; j++) {
                if ((dynamic_cast <Enemy*> (enemies[i][j]))->isAlive() && (dynamic_cast <Enemy*> (enemies[i][j]))->getPosition().y + 50 == ship->getPosition().y) {
                    lives--;
                    (dynamic_cast <Enemy*> (enemies[i][j]))->kill();
                }

                if ((dynamic_cast <Enemy*> (enemies[i][j]))->isAlive() && (dynamic_cast <Enemy*> (enemies[i][j]))->getPosition().y + 50 == shieldS1.getPosition().y && tChange1 <= 3) {
                    (dynamic_cast <Enemy*> (enemies[i][j]))->kill();
                    shieldS1.setTexture(shieldT1.at(tChange1));
                    tChange1++;
                }
                if ((dynamic_cast <Enemy*> (enemies[i][j]))->isAlive() && (dynamic_cast <Enemy*> (enemies[i][j]))->getPosition().y + 50 == shieldS2.getPosition().y && tChange2 <= 3) {
                    (dynamic_cast <Enemy*> (enemies[i][j]))->kill();
                    shieldS2.setTexture(shieldT2.at(tChange2));
                    tChange2++;
                }
                if ((dynamic_cast <Enemy*> (enemies[i][j]))->isAlive() && (dynamic_cast <Enemy*> (enemies[i][j]))->getPosition().y + 50 == shieldS3.getPosition().y && tChange3 <= 3) {
                    (dynamic_cast <Enemy*> (enemies[i][j]))->kill();
                    shieldS3.setTexture(shieldT3.at(tChange3));
                    tChange3++;
                }
            }
        }

        //
    
        window.display();

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 5; j++) {
                if ((dynamic_cast <Enemy*> (enemies[i][j]))->isAlive()) {
                    z = true;
                    a = false;
                    break;
                }
            }
            if (z) {
                z = false;
                break;
            }
        }

        if (a) {
            scoreEnd.setString("Score: " + to_string(score));
            levelEnd.setString("Level: " + to_string(level));

            while (d) {
                window.clear();
                window.draw(levelEnd);
                window.draw(scoreEnd);
                window.draw(endMessage);
                window.display();
                if (Keyboard::isKeyPressed(Keyboard::Enter))
                    d = false;
            }

            level++;
        }

        if (lives == 0) {
            scoreEnd.setString("Score: " + to_string(score));
            levelEnd.setString("Level: " + to_string(level));

            while (d) {
                window.clear();
                window.draw(levelEnd);
                window.draw(scoreEnd);
                window.draw(endMessage);
                window.display();
                if (Keyboard::isKeyPressed(Keyboard::Enter))
                    d = false;
            }
            
            b = true;
            while (b)
                m.displayMenu(&window, score, lives, b);
            level = 1;
        }

        a = true;
    }

    return 0;
}