# Space Invaders [![license](https://img.shields.io/github/license/DAVFoundation/captain-n3m0.svg?style=flat-square)](https://github.com/subhamb123/Chess/blob/main/LICENSE)

Getting Started:
1) Download the zip and unzip it.
2) Go into the space invaders folder which is in the same folder as the license and readme.
3) Open the sln file.
4) Make sure project is in release and x86 mode.
5) Start without debugging and enjoy the game!

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Group Members: Subham Behera, Ryan McCarragher, Danielle Craig, Manjesh Reddy Puram


Team Name: Code Poltergeists

Space Invaders

User Manual:

This program was built for the purpose of WSU CPTS 122 Programming Assignment 9. Our task was to design a game within Visual Studio using graphics based on our choosing. We went with the approach of using SFML for our graphics engine and we decided to make Space Invaders as our game. The original game released in 1978 and our game is a derivative. Our game takes advantages of the libraries that are provided by implementing SFML to our code.

Operation Manual:

The main aspect of this game is played using the keyboard functions. For our game, we primarily use the “A” and “D” or “Left Arrow” and “Right Arrow” commands for movements of left and right respectively and “Space” for the shooting aspect of the game. The purpose is to last as long as you can within the 5 lives that you are given and rack up as many points as possible. You are to kill the enemy characters to stay alive and by doing so gives you points to get a high score. The speed of the enemies and their fire rate progressively gets faster as the player advances in levels.

Design Document:

The flow of our document starts at our main screen. You can choose to either run through the test cases, play the game, or exit the game. If you press 1 for the play game, it will proceed to the game and run until you die. If you press 2 for the test cases, it will run through the 5 test cases. If you press 3 for the exit, you will exit the game. Make sure to use the top row numbers.

Requirements Documentation:

The ideal machine to run this program would be on a Windows machine. The code was written on Visual Studio using the SFML libraries so to run the program ideally, the libraries must be imported. In the case of our program, the libraries will be provided and optimized to run. You must also have a keyboard to use the functionality of the game. Provided that all these criteria are met, you will be able to run and play the game as intended.

Technical Documentation:

Our program is written in the C++ language and uses examples of pointers and classes to help optimize flow and simplicity of the code. One notable characteristic of our program is inheritance. A few of our classes can inherit another class to use the functions and data members from that class. In our program, we have three different classes that inherit the character class. 

Example of Inheritance:

/* 
Missile(const Vector2f& pos, const Texture& texture, const Vector2f& scale) : Character(pos, texture, scale) {}
*/

This implies inheritence as we pass in pos, texture, and scale to the base class.

Example of Polymorphism:

/*
Character* ship = new User(Vector2f(425.f, 825.f), t1, Vector2f(0.1f, 0.1f)); // Polymorphism because user is a character
*/

This shows that we are using polymorphism because we are initializing the ship as a character class, but we are instantiating it to the user class.

Testing Document:

Test 1: Missile Deletion

Test 2: Ship loses life

Test 3: Shield loses health

Test 4: Enemy Movement

Test 5: Enemies randomly fire missiles

List of Encountered Bugs:
1.	At a point of time, we had a bug in which if there was an odd number of enemies at the end of the row and collided with the edge of the screen then the program would crash but that bug has been since fixed.
2.	We used to have an issue in which implementing the menu was a big challenge because we would face the issue where it would flash the screen to update the screen, but it wouldn’t consistently remain on the menu screen till we told it to proceed.
3.	Whenever our game started, the game would crash because we would use the numpad numbers instead of the top row of numbers.
