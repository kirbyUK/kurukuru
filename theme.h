/* theme.h
*	Contains the class definition for a theme, which defines how a level
*	looks by giving it a texture and a background.
*/
#ifndef THEME_H
#define THEME_H
#include <SFML/Graphics.hpp>

//The various themes:
enum
{
	MEADOW,
	TOTAL_NUMBER_OF_THEMES,
};

class Theme
{
	private:
		static sf::Image _textures[TOTAL_NUMBER_OF_THEMES];
		static sf::Image _backgrounds[TOTAL_NUMBER_OF_THEMES];
		sf::Texture _texture;
		sf::Texture _backgroundTexture;
		sf::Sprite _background;

	public:
		static bool init();

		Theme(int);

		sf::Texture& getTexture();
		sf::Sprite& getBackground();
};

#endif
