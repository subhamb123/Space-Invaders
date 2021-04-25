//
//////////////////////////////////////////////////////////////
//// Headers
//////////////////////////////////////////////////////////////
//#include "header.hpp"
//#include "Scoring.hpp"
//#include "Menu.hpp"
//#include "User.hpp"
//#include "Enemy.hpp"
//#include "Missile.hpp"
//
//
//////////////////////////////////////////////////////////////
///// Entry point of application
/////
///// \return Application exit code
/////
//////////////////////////////////////////////////////////////
//int main()
//{
//    srand((unsigned)time(nullptr));
//
//    Menu m;
//
//    bool x = false, y = false, z = false, a = true, dir = true;
//    int level = 1, lives = 5, score = 0;
//
//    Clock c, c2;
//
//    RenderWindow window(VideoMode(950, 950), "Space Invaders");
//
//    Texture t1, t2, t3, t4;
//
//    SoundBuffer buffer;
//    SoundBuffer buffer2;
//    buffer.loadFromFile("shoot.wav");
//    buffer2.loadFromFile("invaderkilled.wav");
//
//    Sound missile_sound;
//    Sound invader_killed;
//
//    missile_sound.setBuffer(buffer);
//    invader_killed.setBuffer(buffer2);
//
//    invader_killed.setVolume(5.f);
//    missile_sound.setVolume(5.f);
//
//    Text scoreT, livesT;
//    Font font;
//    font.loadFromFile("font.ttf");
//
//    scoreT.setFont(font);
//    livesT.setFont(font);
//    scoreT.setCharacterSize(25);
//    livesT.setCharacterSize(25);
//    scoreT.setFillColor(Color::White);
//    livesT.setFillColor(Color::White);
//
//    scoreT.setPosition(Vector2f(200.f, 0.f));
//    livesT.setPosition(Vector2f(500.f, 0.f));
//
//    t1.loadFromFile("Ship.jpg");
//    Character* ship = new User(Vector2f(425.f, 825.f), t1, Vector2f(0.1f, 0.1f));
//
//    Enemy* enemies[10][5] = { nullptr };
//    t2.loadFromFile("Alien.jpg");
//
//    for (int i = 0; i < 10; i++)
//        for (int j = 0; j < 5; j++)
//            enemies[i][j] = new Enemy(Vector2f(175.f + 60 * i, 100.f + 50 * j), t2, Vector2f(0.75f, 0.75f));
//
//    t3.loadFromFile("Missile.jpg");
//    vector<Missile*> missiles;
//
//    t4.loadFromFile("enemyMissile.jpg");
//    vector<Missile*> enemyM;
//
//    Missile* missile = nullptr;
//    Missile* enemyMi = nullptr;
//    bool isPlaying = false;
//    while (window.isOpen())
//    {
//        // Handle events
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            // Window closed or escape key pressed: exit
//            if ((event.type == sf::Event::Closed) ||
//                ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
//            {
//                window.close();
//                break;
//            }
//
//            // Space key pressed: play
//            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter))
//            {
//                if (!isPlaying)
//                {
//                    // (re)start the game
//                    isPlaying = true;
//
//                }
//            }
//        }
//
//        if (isPlaying)
//        {
//            scoreT.setString("Score: " + to_string(score));
//            livesT.setString("Lives: " + to_string(lives));
//
//            if (ship->getPosition().x + 105 != window.getSize().x && (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)))
//                ship->move(0.5, 0);
//
//            if (ship->getPosition().x != 0 && (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)))
//                ship->move(-0.5, 0);
//
//            if (Keyboard::isKeyPressed(Keyboard::Space) && c.getElapsedTime().asSeconds() > 0.25) {
//                missile = new Missile(Vector2f(ship->getPosition().x + 34, ship->getPosition().y - 40), t3, Vector2f(0.1f, 0.1f));
//                missiles.push_back(missile);
//                c.restart();
//                missile_sound.play();
//            }
//
//            if (c2.getElapsedTime().asMilliseconds() > 1000 - level * 75) {
//                int x_coor = rand() % 10, y_coor = rand() % 5;
//                while (!enemies[x_coor][y_coor]->isAlive())
//                    x_coor = rand() % 10, y_coor = rand() % 5;
//                enemyMi = new Missile(Vector2f(enemies[x_coor][y_coor]->getPosition().x + 7, enemies[x_coor][y_coor]->getPosition().y), t4, Vector2f(0.05f, 0.05f));
//                enemyM.push_back(enemyMi);
//                c2.restart();
//            }
//
//            if (!missiles.empty()) {
//                for (int i = 0; i < missiles.size(); i++)
//                    missiles.at(i)->move(Vector2f(0.f, -0.5f));
//            }
//
//            if (!enemyM.empty()) {
//                for (int i = 0; i < enemyM.size(); i++)
//                    enemyM.at(i)->move(Vector2f(0.f, 0.5f));
//            }
//
//            for (int i = 0; i < 10; i++)
//                for (int j = 0; j < 5; j++)
//                    if (enemies[i][j]->isAlive() && (enemies[i][j]->getPosition().x > 915 || enemies[i][j]->getPosition().x < 0)) {
//                        dir = !dir;
//                        for (int i = 0; i < 10; i++)
//                            for (int j = 0; j < 5; j++)
//                                enemies[i][j]->move(Vector2f(0.f, 10.f));
//                    }
//
//            for (int i = 0; i < 10; i++)
//                for (int j = 0; j < 5; j++) {
//                    if (dir)
//                        enemies[i][j]->move(Vector2f(0.1f, 0.f));
//                    else
//                        enemies[i][j]->move(Vector2f(-0.1f, 0.f));
//                }
//
//            if (!missiles.empty()) {
//                for (int i = 0; i < 10; i++) {
//                    for (int j = 0; j < 5; j++) {
//                        for (int k = 0; k < missiles.size(); k++) {
//                            if (!missiles.empty() && enemies[i][j]->isAlive() && missiles.at(k)->getPosition().y < enemies[i][j]->getPosition().y && missiles.at(k)->getPosition().x > enemies[i][j]->getPosition().x - 20 &&
//                                missiles.at(k)->getPosition().x < enemies[i][j]->getPosition().x + 20) {
//                                missiles.erase(missiles.begin() + k);
//                                enemies[i][j]->kill(level);
//                                invader_killed.play();
//                                score += level * 10;
//                                x = true;
//                                break;
//                            }
//                        }
//                        if (x) {
//                            x = false;
//                            y = true;
//                            break;
//                        }
//                    }
//                    if (y) {
//                        y = false;
//                        break;
//                    }
//                }
//
//                if (!missiles.empty() && missiles.back()->getPosition().y < -100)
//                    missiles.pop_back();
//            }
//
//            if (!enemyM.empty()) {
//                for (int i = 0; i < enemyM.size(); i++)
//                    if (!enemyM.empty() && enemyM.at(i)->getPosition().y > ship->getPosition().y && enemyM.at(i)->getPosition().x > ship->getPosition().x - 20 &&
//                        enemyM.at(i)->getPosition().x < ship->getPosition().x + 120) {
//                        enemyM.erase(enemyM.begin() + i);
//                        lives--;
//                    }
//
//                if (!enemyM.empty() && enemyM.back()->getPosition().y > 1050)
//                    enemyM.pop_back();
//            }
//
//            // Clear the window
//            window.clear(sf::Color(50, 200, 50));
//
//            if (isPlaying)
//            {
//                // Draw the paddles and the ball
//                window.draw(scoreT);
//                window.draw(livesT);
//
//                if (!missiles.empty()) {
//                    for (int i = 0; i < missiles.size(); i++)
//                        window.draw(*missiles.at(i));
//                }
//
//                if (!enemyM.empty()) {
//                    for (int i = 0; i < enemyM.size(); i++)
//                        window.draw(*enemyM.at(i));
//                }
//
//                window.draw(*ship);
//                for (int i = 0; i < 10; i++)
//                    for (int j = 0; j < 5; j++)
//                        if (enemies[i][j]->isAlive())
//                            window.draw(*enemies[i][j]);
//            }
//            else
//            {
//                // Draw the pause message
//
//
//                for (int i = 0; i < 10; i++) {
//                    for (int j = 0; j < 5; j++) {
//                        if (enemies[i][j]->isAlive()) {
//                            z = true;
//                            a = false;
//                            break;
//                        }
//                    }
//                    if (z) {
//                        z = false;
//                        break;
//                    }
//                }
//
//                if (a || lives == 0) {
//                    //window.draw(pauseMessage);
//                }
//
//                a = true;
//            }
//
//            // Display things on screen
//            window.display();
//        }
//
//        return EXIT_SUCCESS;
//    }
//}