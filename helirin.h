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

		unsigned short int _lives;

	public:
		//Loads the image:
		static bool init();

		Helirin();

		//Moves the Helirin in the given direction:
		void move(Direction, float);

		//Handles non-keyboard events, like roation:
		void handleEvents(float);

		//Getters:
		sf::Sprite& getSprite();
		unsigned short int getLives();
};

#endif
