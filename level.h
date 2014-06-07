/*
* level.h
*  Contains the class defintion for a level,
*  the courses the player plays through.
*/

#ifndef LEVEL_H
#define LEVEL_H
#include <SFML/Graphics.hpp>
#include <string>
#include "theme.h"

class Level
{
	private:
		//Meta-data:
		std::string _name;
		std::string _author;
		Theme* _theme;

		//The level is effectively a big shape:
		sf::ConvexShape _shape;

		//Times how long they're in the level:
		sf::Clock _levelTimer;

		//Should the player die, this is where they spawn:
		sf::Vector2f _spawnPoint;

		//The number of penalties the player has recieved:
		short unsigned int _penalties;

	public:
		//Loads the level from the passed file:
		Level(std::string);
		~Level();

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
		std::string getElapsedTime();
};

#endif
