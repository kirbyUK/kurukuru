//interface.cpp
#include "interface.h"
#include <iostream>

//The font paths:
#ifdef _WIN32
	const std::string PC_SENIOR = "assets\\fonts\\PC-Senior\\pcsenior.ttf";
#else
	const std::string PC_SENIOR = "assets/fonts/PC-Senior/pcsenior.ttf";
#endif

sf::Font Interface::_pcSenior; 

bool Interface::init()
{
	if(! _pcSenior.loadFromFile(PC_SENIOR))
	{
		std::cerr << "Failed to load'" << PC_SENIOR << "'!\n";
		return false;
	}
	return true;
}

Interface::Interface()
{
	_text[CLOCK].setFont(_pcSenior);
	_text[CLOCK].setCharacterSize(16);
	_text[CLOCK].setColor(sf::Color::White);
	_text[CLOCK].setString("TIME: 00'00\"00");

	_text[CLOCK_BESTTIME].setFont(_pcSenior);
	_text[CLOCK_BESTTIME].setCharacterSize(16);
	_text[CLOCK_BESTTIME].setColor(sf::Color::White);
	_text[CLOCK_BESTTIME].setString("BEST: 00'00\"00");

	_text[FPS].setFont(_pcSenior);
	_text[FPS].setCharacterSize(16);
	_text[FPS].setColor(sf::Color::White);
	_text[FPS].setString("FPS: 000");
}

void Interface::update(sf::View v)
{
	//Positions the text relative to the view:
	_text[CLOCK].setPosition(
		((v.getCenter().x - (v.getSize().x / 2)) + 5),  //X
		((v.getCenter().y - (v.getSize().y / 2)) + 5)); //Y

	_text[CLOCK_BESTTIME].setPosition(
		(_text[CLOCK].getPosition().x), //X
		(_text[CLOCK].getPosition().y + (_text[CLOCK].getGlobalBounds().height + 2))); //Y	

	_text[FPS].setPosition(
		((v.getCenter().x + (v.getSize().x / 2)) - (_text[FPS].getGlobalBounds().width + 5)),   //X
		((v.getCenter().y + (v.getSize().y / 2)) - (_text[FPS].getGlobalBounds().height + 5))); //Y
}


sf::Text* Interface::getText()
{
	return _text;
}
