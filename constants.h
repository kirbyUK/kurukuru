/* 
* constants.h
*  Defines various constants 
*  used throughout the program.
*/

#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <SFML/Graphics.hpp>

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

//The colours used for the colour
//mask on images, for transparency:
const int RED = 0;
const int GREEN = 255;
const int BLUE = 0;
const sf::Color COLOUR_MASK = sf::Color(RED, GREEN, BLUE);

#endif
