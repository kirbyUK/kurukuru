/* 
* helirin.h
*  Contains the class defintion for the
*  main character thing the player plays as.
*/

#ifndef KURU_H
#define KURU_H
#include <SFML/Graphics.hpp>

//The number of degrees Kuru rotates per second:
const float ROTATION_SPEED = 90.0;

#ifdef _WIN32
	const std::string KURU_IMG_PATH = "assets\\kuru\\kuru.png";
#else
	const std::string KURU_IMG_PATH = "assets/kuru/kuru.png";
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

		//Handles non-keyboard events, like roation:
		void handleEvents(float);

		//Getters:
		sf::Sprite& getSprite();
		unsigned short int getLives();
};

#endif
