/************************************************************************
* Programmers: Subham, Ryan, Danielle, Manjesh                          *
* Class: CptS 122                                                       *
* Programming Assignment: PA 9 - Space Invaders                         *
* Date: 4/17/2021                                                       *
* Description: This program emulates space invaders.                    *
************************************************************************/

//What exactly are the test cases?

#include "header.hpp"
#include "Menu.hpp"
#include "User.hpp"
#include "Enemy.hpp"
#include "Missile.hpp"

int main() {
    srand((unsigned)time(nullptr));

    Menu m;

    bool next_level = true, indicator = true, dir = true, reset_check = false;
    int level = 1, lives = 5, score = 0, tChange1 = 1, tChange2 = 1, tChange3 = 1;

    Clock c, c2;

    RenderWindow window(VideoMode(950, 950), "Space Invaders"); //Size of window

    Texture t1, t2, t3, t4, t5, t6, t7, t8; //Allows different textures for items

    //In-game music
    Music music;
    music.openFromFile("music.ogg");
    music.setLoop(true);
    music.play();
    music.setVolume(10.f);

    //Loads action sounds
    SoundBuffer buffer;
    SoundBuffer buffer2;
    SoundBuffer buffer3;
    buffer.loadFromFile("shoot.wav");
    buffer2.loadFromFile("invaderkilled.wav");
    buffer3.loadFromFile("explosion.wav");

    Sound missile_sound;
    Sound invader_killed;
    Sound ship_hit;

    missile_sound.setBuffer(buffer);
    invader_killed.setBuffer(buffer2);
    ship_hit.setBuffer(buffer3);

    invader_killed.setVolume(5.f);
    missile_sound.setVolume(5.f);
    ship_hit.setVolume(5.f);

    //Sets up different text in the game
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
    livesT.setPosition(Vector2f(425.f, 0.f));
    levelT.setPosition(Vector2f(675.f, 0.f));
    scoreEnd.setPosition(Vector2f(125.f, 450.f));
    levelEnd.setPosition(Vector2f(500.f, 450.f));
    endMessage.setPosition(Vector2f(125.f, 500.f));

    endMessage.setString("Press enter to continue...");

    t1.loadFromFile("Ship.jpg"); //Loads image
    Character* ship = new User(Vector2f(425.f, 825.f), t1, Vector2f(0.1f, 0.1f)); //Polymorphism because uer is a character

    Character* enemies[10][5] = { nullptr }; //Allows for matrix of enemies
    t2.loadFromFile("Alien.jpg");

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 5; j++)
            enemies[i][j] = new Enemy(Vector2f(175.f + 60 * i, 100.f + 50 * j), t2, Vector2f(0.75f, 0.75f));

    t3.loadFromFile("Missile.jpg");
    vector<Missile*> missiles; //Keeps track of user missiles on the screen

    t4.loadFromFile("enemyMissile.jpg");
    vector<Missile*> enemyM; //Keeps track of enemy missiles on the screen

    //Helper variables for insertion into the vectors
    Missile* missile = nullptr;
    Missile* enemyMi = nullptr;

    //Each shield has its own vector to keep track of the texture cycle
    vector<Texture> shieldT1;
    vector<Texture> shieldT2;
    vector<Texture> shieldT3;

    t5.loadFromFile("Shield1.jpg");
    t6.loadFromFile("Shield2.jpg");
    t7.loadFromFile("Shield3.jpg");
    t8.loadFromFile("Shield4.jpg");

    //Inserts the cycle of textures
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

    //Declares shield sprites
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

        while (indicator) //Is there any better way to do this?
            m.displayMenu(&window, score, lives, indicator); //Display menu until user enters a valid input

        //Skips checking each enemy during rounds to let program run smoother
        if (reset_check)
            goto escape1;

        //If all ememies are dead, this sets that indicator
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (dynamic_cast <Enemy*> (enemies[i][j])->isAlive() == true)
                {
                    reset_check = false;
                    goto escape1;
                }
                else
                    reset_check = true;
            }
        }

    escape1:
        //When user dies or goes to next level
        if (reset_check)
        {
            //Resets position
            for (int i = 0; i < 10; i++)
                for (int j = 0; j < 5; j++)
                    enemies[i][j]->setPosition(Vector2f(175.f + 60 * i, 100.f + 50 * j));

            //Makes each enemy alive
            for (int i = 0; i < 10; i++)
                for (int j = 0; j < 5; j++)
                    dynamic_cast <Enemy*> (enemies[i][j])->reset();

            reset_check = false;
        }

        //Updates statistics real-time
        scoreT.setString("Score: " + to_string(score));
        livesT.setString("Lives: " + to_string(lives));
        levelT.setString("Level: " + to_string(level));

        //Moves ship if it is within bounds of screen

        if (ship->getPosition().x + 105 != window.getSize().x && (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)))
            ship->move(0.5, 0);

        if (ship->getPosition().x != 0 && (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)))
            ship->move(-0.5, 0);

        //Generates new missiles every 0.375 seconds or when user presses space, whichever is longest in time passed
        if (Keyboard::isKeyPressed(Keyboard::Space) && c.getElapsedTime().asSeconds() > 0.375) {
            missile = new Missile(Vector2f(ship->getPosition().x + 34, ship->getPosition().y - 40), t3, Vector2f(0.1f, 0.1f));
            missiles.push_back(missile);
            c.restart();
            missile_sound.play();
        }

        //Generates new enemy missiles, which get faster each level
        if (c2.getElapsedTime().asMilliseconds() > 1075 - level * 75) {
            int x_coor = rand() % 10, y_coor = rand() % 5; //Randomly picks an enemy to shoot
            while (!(dynamic_cast <Enemy*> (enemies[x_coor][y_coor]))->isAlive()) //Makes sure the enemy is alive
                x_coor = rand() % 10, y_coor = rand() % 5;
            enemyMi = new Missile(Vector2f(enemies[x_coor][y_coor]->getPosition().x + 7, enemies[x_coor][y_coor]->getPosition().y), t4, Vector2f(0.05f, 0.05f));
            enemyM.push_back(enemyMi);
            c2.restart();
        }

        //If there are missiles, they move

        if (!missiles.empty()) {
            for (int i = 0; i < missiles.size(); i++)
                missiles.at(i)->move(Vector2f(0.f, -0.5f));
        }

        if (!enemyM.empty()) {
            for (int i = 0; i < enemyM.size(); i++)
                enemyM.at(i)->move(Vector2f(0.f, 0.5f));
        }

        //When a live enemy hits a border, they change directions and go down
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 5; j++)
                if ((dynamic_cast <Enemy*> (enemies[i][j]))->isAlive() && (enemies[i][j]->getPosition().x > 915 || enemies[i][j]->getPosition().x < 0)) {
                    dir = !dir; //Changes direction
                    for (int i = 0; i < 10; i++)
                        for (int j = 0; j < 5; j++)
                            enemies[i][j]->move(Vector2f(0.f, (float)(9 + level))); //Moves enemies downward

                    goto escape2;
                }

    escape2:
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 5; j++) {
                if (dir) //Right direction and speed depends on level
                    enemies[i][j]->move(Vector2f((float)(0.1 + (level * 0.02)), 0.f));
                else //Left direction
                    enemies[i][j]->move(Vector2f((float)(-0.1 - (level * 0.02)), 0.f));
            }

        window.clear();

        //Draw statistics
        window.draw(scoreT);
        window.draw(livesT);
        window.draw(levelT);

        window.draw(shieldS1);
        window.draw(shieldS2);
        window.draw(shieldS3);

        //Draws missiles if there are any on the screen

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
                    window.draw(*enemies[i][j]); //Draw live enemies

        if (!missiles.empty()) {
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 5; j++) {
                    for (int k = 0; k < missiles.size(); k++) {
                        //If user missile hits a live enemy with lots of offset and hitboxing
                        if (!missiles.empty() && (dynamic_cast <Enemy*> (enemies[i][j]))->isAlive() && missiles.at(k)->getPosition().y == enemies[i][j]->getPosition().y && missiles.at(k)->getPosition().x >
                            enemies[i][j]->getPosition().x - 20 && missiles.at(k)->getPosition().x < enemies[i][j]->getPosition().x + 20) {
                            missiles.erase(missiles.begin() + k); //Deletes that particular missile
                            (dynamic_cast <Enemy*> (enemies[i][j]))->kill();
                            invader_killed.play();
                            score += level * 10;
                            goto escape3;
                        }
                    }
                }
            }
        escape3:
            if (!missiles.empty() && missiles.back()->getPosition().y < -100)
                missiles.pop_back(); //Deletes missiles that go off the screen
        }

        try {
            if (!enemyM.empty()) {
                for (int i = 0; i < enemyM.size(); i++) {

                    //If enemy missile hits ship
                    if (!enemyM.empty() && enemyM.at(i)->getPosition().y == ship->getPosition().y && enemyM.at(i)->getPosition().x > ship->getPosition().x - 20 && enemyM.at(i)->getPosition().x < ship->getPosition().x + 120) {
                        enemyM.erase(enemyM.begin() + i);
                        lives--;
                        ship_hit.play();
                    }

                    //If enemy missile hits one of the shields

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
        }

        catch (...) { //Catches out_of_range error that shouldn't happen in the first place, but it works

        }

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 5; j++) {
                //If enemies get to y = 900 pixels, the user automatically loses
                if ((dynamic_cast <Enemy*> (enemies[i][j]))->isAlive() && (dynamic_cast <Enemy*> (enemies[i][j]))->getPosition().y + 50 == 900)
                    lives = 0;

                //If enemy hits a shield, they die and the shield takes some damage

                if ((dynamic_cast <Enemy*> (enemies[i][j]))->isAlive() && (dynamic_cast <Enemy*> (enemies[i][j]))->getPosition().y == shieldS1.getPosition().y && (dynamic_cast <Enemy*> (enemies[i][j]))->getPosition().x >
                    shieldS1.getPosition().x - 20 && (dynamic_cast <Enemy*> (enemies[i][j]))->getPosition().x < shieldS1.getPosition().x + 120 && tChange1 <= 3) {
                    (dynamic_cast <Enemy*> (enemies[i][j]))->kill();
                    shieldS1.setTexture(shieldT1.at(tChange1));
                    tChange1++;
                }
                if ((dynamic_cast <Enemy*> (enemies[i][j]))->isAlive() && (dynamic_cast <Enemy*> (enemies[i][j]))->getPosition().y == shieldS2.getPosition().y && (dynamic_cast <Enemy*> (enemies[i][j]))->getPosition().x >
                    shieldS2.getPosition().x - 20 && (dynamic_cast <Enemy*> (enemies[i][j]))->getPosition().x < shieldS2.getPosition().x + 120 && tChange2 <= 3) {
                    (dynamic_cast <Enemy*> (enemies[i][j]))->kill();
                    shieldS2.setTexture(shieldT2.at(tChange2));
                    tChange2++;
                }
                if ((dynamic_cast <Enemy*> (enemies[i][j]))->isAlive() && (dynamic_cast <Enemy*> (enemies[i][j]))->getPosition().y == shieldS3.getPosition().y && (dynamic_cast <Enemy*> (enemies[i][j]))->getPosition().x >
                    shieldS3.getPosition().x - 20 && (dynamic_cast <Enemy*> (enemies[i][j]))->getPosition().x < shieldS3.getPosition().x + 120 && tChange3 <= 3) {
                    (dynamic_cast <Enemy*> (enemies[i][j]))->kill();
                    shieldS3.setTexture(shieldT3.at(tChange3));
                    tChange3++;
                }
            }
        }

        window.display();

        //If all enemies are dead, go to next level
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 5; j++) {
                if ((dynamic_cast <Enemy*> (enemies[i][j]))->isAlive()) {
                    next_level = false;
                    goto escape4;
                }
            }
        }

    escape4:
        if (next_level || lives == 0) {
            reset_check = true; //Resets enemies using algorithm on line 181
            scoreEnd.setString("Score: " + to_string(score));
            levelEnd.setString("Level: " + to_string(level));

            //Displays statistics until user presses enter
            while (true) {
                window.clear();
                window.draw(levelEnd);
                window.draw(scoreEnd);
                window.draw(endMessage);
                window.display();
                if (Keyboard::isKeyPressed(Keyboard::Enter))
                    goto escape5;
            }

        escape5:
            if (lives == 0) {
                indicator = true; //Displays menu again
                level = 1;
            }
            else
                level++;

            //Empties all missiles for next round

            while (!missiles.empty())
                missiles.pop_back();

            while (!enemyM.empty())
                enemyM.pop_back();

            //Resets shield cycle
            shieldS1.setTexture(shieldT1.at(0));
            shieldS2.setTexture(shieldT2.at(0));
            shieldS3.setTexture(shieldT3.at(0));
            tChange1 = 1;
            tChange2 = 1;
            tChange3 = 1;
        }

        next_level = true;
    }

    return 0;
}