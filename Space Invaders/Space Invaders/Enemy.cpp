/************************************************************************
* Programmers: Subham, Ryan, Danielle, Manjesh                          *
* Class: CptS 122                                                       *
* Programming Assignment: PA 9 - Space Invaders                         *
* Date: 4/17/2021                                                       *
* Description: This program emulates space invaders.                    *
************************************************************************/

#include "Enemy.hpp"

/****************************************************************
* Class Function: isAlive()                                     *
* Date Created: 4/17/2021                                       *
* Date Last Modified: 4/17/2021                                 *
* Description: Returns if enemy is alive or not                 *
* Input parameters: None                                        *
* Returns: bool                                                 *
* Preconditions: None                                           *
* Postconditions: Life state of enemy has been returned         *
*****************************************************************/
bool Enemy::isAlive()
{
	return alive;
}

/****************************************************************
* Class Function: kill()                                        *
* Date Created: 4/17/2021                                       *
* Date Last Modified: 4/17/2021                                 *
* Description: Sets alive to false                              *
* Input parameters: None                                        *
* Returns: Nothing                                              *
* Preconditions: None                                           *
* Postconditions: An enemy has been killed                      *
*****************************************************************/
void Enemy::kill()
{
	alive = false;
}

/****************************************************************
* Class Function: reset()                                       *
* Date Created: 4/17/2021                                       *
* Date Last Modified: 4/17/2021                                 *
* Description: Sets alive to true                               *
* Input parameters: None                                        *
* Returns: Nothing                                              *
* Preconditions: None                                           *
* Postconditions: An enemy has been brought back to life        *
*****************************************************************/
void Enemy::reset()
{
	alive = true;
}