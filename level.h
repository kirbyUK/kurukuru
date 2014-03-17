/*
* level.h
*  Contains the class defintion for a level,
*  the courses the player plays through.
*/

#ifndef LEVEL_H
#define LEVEL_H
#include <SFML/Graphics.hpp>
#include <string>

#ifdef _WIN32
	const std::string MEADOW_TEXTURE = "assets\\themes\\textures\\meadow.png";
	const std::string MEADOW_BACKGROUND = "assets\\themes\\backgrounds\\meadow.jpg";
#else
	const std::string MEADOW_TEXTURE = "assets/themes/textures/meadow.png";
	const std::string MEADOW_BACKGROUND = "assets/themes/backgrounds/meadow.jpg";
#endif

//The various themes:
enum
{
	MEADOW,
	TOTAL_NUMBER_OF_THEMES,
};

//The number of seconds added if the player crashes:
const float PENALTY = 3.0;

class Level
{
	private:
		static sf::Image _images[TOTAL_NUMBER_OF_THEMES];
		static sf::Image _backgrounds[TOTAL_NUMBER_OF_THEMES];
		sf::Texture _levelTexture;
		sf::Texture _backgroundTexture;
		sf::Sprite _background;

		//Meta-data:
		std::string _name;
		std::string _author;
		std::string _theme;

		//The level is effectively a big shape:
		sf::ConvexShape _shape;

		//Times how long they're in the level:
		sf::Clock _levelTimer;

		//Should the player die, this is where they spawn:
		sf::Vector2f _spawnPoint;

		//The number of penalties the player has recieved:
		short unsigned int _penalties;

	public:
		//Loads the texture image:
		static bool init();

		//Loads the level from the passed file:
		Level(std::string);

		//Starts the level:
		void begin();

		//Does stuff like animating the border:
		void handleEvents();

		//Resizes the background:
		void resizeBackground(sf::View);

		//Adds extra time to the clock if the player crashes:
		void penalise();

		//Getters:
		sf::ConvexShape& getShape();
		sf::Sprite& getBackground();
		sf::Time getElapsedTime();
};

#endif
