/* 
* helirin.h
*  Contains the class defintion for the
*  main character thing the player plays as.
*/

#ifndef KURU_H
#define KURU_H
#include <SFML/Graphics.hpp>
#include "constants.h"

class Helirin
{
	private:
		static sf::Image _image;
		sf::Sprite _sprite;
		sf::Texture _texture;

		sf::Clock _hitTimer;

		DirectionVector _previousDirection;
		DirectionVector _currentDirection;

		unsigned short int _lives;

	public:
		//Loads the image:
		static bool init();

		Helirin();

		//Updates the direction vector:
		void move(Direction);

		//Handles non-keyboard events, like roation, and actually moves the
		//Helirin based on the direction vector:
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
