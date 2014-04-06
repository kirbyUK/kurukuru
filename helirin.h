/* 
* helirin.h
*  Contains the class defintion for the
*  main character thing the player plays as.
*/

#ifndef KURU_H
#define KURU_H
#include <SFML/Graphics.hpp>
#include "constants.h"

//The number of degrees the Helirin rotates per second:
const float ROTATION_SPEED = 90.0;

//The number of pixels moved in a single second
//of constant movement in any given direction:
const float VELOCITY = 100.0;

//The time in seconds it takes for the Helirin to
//'cooldown' after colliding with a wall. During the
//'cooldown' period, it spins the other way:
const float COOLDOWN = 0.4;

#ifdef _WIN32
	const std::string HELIRIN_IMG_PATH = "assets\\helirin\\helirin.png";
#else
	const std::string HELIRIN_IMG_PATH = "assets/helirin/helirin.png";
#endif

class Helirin
{
	private:
		static sf::Image _image;
		sf::Sprite _sprite;
		sf::Texture _texture;

		sf::Clock _hitTimer;

		//The direction we moved this frame,
		//just in case we need to go back:
		Direction _directionMoved;

		unsigned short int _lives;

	public:
		//Loads the image:
		static bool init();

		Helirin();

		//Moves the Helirin in the given direction:
		void move(Direction, float);

		//Handles non-keyboard events, like roation:
		void handleEvents(float);

		//Checks for any collisions with the level walls:
		bool checkCollision(sf::ConvexShape&);

		//Subtract a life, spin the other way, and move back
		//a bit. Happens when the player collides with something:
		void ouch(float);

		//Getters:
		sf::Sprite& getSprite();
		unsigned short int getLives();
};

#endif
