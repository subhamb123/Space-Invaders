/************************************************************************
* Programmers: Subham, Ryan, Danielle, Manjesh                          *
* Class: CptS 122                                                       *
* Programming Assignment: PA 9 - Space Invaders                         *
* Date: 4/17/2021                                                       *
* Description: This program emulates space invaders.                    *
************************************************************************/

#include "header.hpp"
//#include "Menu.hpp"
//#include "User.hpp"
//#include "Enemy.hpp"
//#include "Missile.hpp"

/****************************************************************
* Function: delay()                                             *
* Date Created: 4/17/2021                                       *
* Date Last Modified: 4/17/2021                                 *
* Description: pauses the program for some miliseconds.         *
* Input parameters: miliseconds as int                          *
* Returns: Nothing                                              *
* Preconditions: miliseconds as int                             *
* Postconditions: the program has been delayed for some time    *
*****************************************************************/
void delay(int x) {
	clock_t time = clock();
	while (clock() < time + x)
		;
}

//void ship_movement(User** ship, RenderWindow& window) {
//    if (ship->getPosition().x + 105 != window.getSize().x && (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)))
//        ship->move(0.5, 0);
//
//    if (ship->getPosition().x != 0 && (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)))
//        ship->move(-0.5, 0);
//}

//void missile_movement(vector<Missile*> &missiles, vector<Missile*> &enemyM)
//{
//	if (!missiles.empty()) {
//        for (int i = 0; i < missiles.size(); i++)
//            missiles.at(i)->move(Vector2f(0.f, -0.5f));
//    }
//
//    if (!enemyM.empty()) {
//        for (int i = 0; i < enemyM.size(); i++)
//            enemyM.at(i)->move(Vector2f(0.f, 0.5f));
//    }
//}
