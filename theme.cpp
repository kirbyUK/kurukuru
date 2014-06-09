#include "theme.h"
#include <SFML/Graphics.hpp>
#include <iostream>

#ifdef _WIN32
	std::string MEADOW_TEXTURE = "assets\\themes\\textures\\meadow.png";
	std::string MEADOW_BACKGROUND = "assets\\themes\\backgrounds\\meadow.jpg";
#else
	std::string MEADOW_TEXTURE = "assets/themes/textures/meadow.png";
	std::string MEADOW_BACKGROUND = "assets/themes/backgrounds/meadow.jpg";
#endif

sf::Image Theme::_textures[TOTAL_NUMBER_OF_THEMES];
sf::Image Theme::_backgrounds[TOTAL_NUMBER_OF_THEMES];

bool Theme::init()
{
	if(! _textures[MEADOW].loadFromFile(MEADOW_TEXTURE))
	{
		std::cerr << "Failed to load '" << MEADOW_TEXTURE << "'!\n";
		return false;
	} 
	if(! _backgrounds[MEADOW].loadFromFile(MEADOW_BACKGROUND))
	{
		std::cerr << "Failed to load '" << MEADOW_BACKGROUND << "'!\n";
		return false;
	} 
	return true;
}

//Creates a theme based on the given integer, which will more than likely
//be one of the aliases in the 'theme.h' enum:
Theme::Theme(int t)
{
	switch(t)
	{
		case MEADOW:
			_texture.loadFromImage(_textures[MEADOW]);
			_backgroundTexture.loadFromImage(_backgrounds[MEADOW]);
	}
	_texture.setRepeated(true);
	_backgroundTexture.setRepeated(true);
	_background.setTexture(_backgroundTexture);
}

sf::Texture& Theme::getTexture()
{
	return _texture;
}

sf::Sprite& Theme::getBackground()
{
	return _background;
}
