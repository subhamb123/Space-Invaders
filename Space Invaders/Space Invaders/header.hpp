/************************************************************************
* Programmers: Subham, Ryan, Danielle, Manjesh                          *
* Class: CptS 122                                                       *
* Programming Assignment: PA 9 - Space Invaders                         *
* Date: 4/17/2021                                                       *
* Description: This program emulates space invaders.                    *
************************************************************************/

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

using std::cout;
using std::endl;
using std::to_string;
using std::vector;

void delay(int x);
//void ship_movement(User** ship, RenderWindow& window);
//void missile_movement(vector<Missile*> &missiles, vector<Missile*> &enemyM);