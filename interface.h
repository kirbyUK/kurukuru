/*
* interface.h
*  Handles all things with the interface,
*  mostly the text and moving everything
*  about when the window gets resized.
*/

#ifndef INTERFACE_H
#define INTERFACE_H
#include <SFML/Graphics.hpp>
#include <string>

//The tags for the text items:
enum
{
	CLOCK,
	CLOCK_BESTTIME,
	FPS,
	NUMBER_OF_TEXT_ITEMS,
};

class Interface
{
	private:
		//The fonts:
		static sf::Font _pcSenior;

		//The text items:
		sf::Text _text[NUMBER_OF_TEXT_ITEMS];

	public:
		//Initialises all the fonts:
		static bool init();

		Interface();

		//Updates the positions of all the text items:
		void update(sf::View);

		//Gets the text items array:
		sf::Text* getText();
};

#endif
