//kuru.cpp
#include "kuru.h"
#include "constants.h"

sf::Image Kuru::_image;

bool Kuru::init()
{
	return _image.loadFromFile(KURU_IMG_PATH);
}

Kuru::Kuru()
{
	//Make the green background transparent:
	_image.createMaskFromColor(COLOUR_MASK);
	_texture.loadFromImage(_image);
	_sprite.setTexture(_texture);

	//Sets the centre of the sprite to the exact centre of 
	//Kuru, so it rotatates and moves properly:
	_sprite.setOrigin((_sprite.getLocalBounds().width / 2), //x 
					(_sprite.getLocalBounds().height / 2)); //y

	_sprite.setPosition(300, 300);

	_lives = 3;
}

//Handles non-keyboard events, like rotation:
void Kuru::handleEvents(float frameTime)
{
	//Rotate Kuru:
	_sprite.rotate(ROTATION_SPEED * frameTime);

	//Check if we've collided with anything:
	//[COLLISION CHECK CODE]
}

unsigned short int Kuru::getLives()
{
	return _lives;
}

sf::Sprite& Kuru::getSprite()
{
	return _sprite;
}
