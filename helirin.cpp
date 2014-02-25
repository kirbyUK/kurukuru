//kuru.cpp
#include "helirin.h"

sf::Image Helirin::_image;

bool Helirin::init()
{
	return _image.loadFromFile(KURU_IMG_PATH);
}

Helirin::Helirin()
{
	//Make the green background transparent:
	_image.createMaskFromColor(COLOUR_MASK);
	_texture.loadFromImage(_image);
	_sprite.setTexture(_texture);

	//Sets the centre of the sprite to the exact centre of 
	//Helirin, so it rotatates and moves properly:
	_sprite.setOrigin((_sprite.getLocalBounds().width / 2), //x 
					(_sprite.getLocalBounds().height / 2)); //y

	_sprite.setPosition(300, 300);

	_lives = 3;
}

void Helirin::move(Direction d, float frameTime)
{
	switch(d)
	{
		case UP: 	_sprite.move(0, -(VELOCITY * frameTime)); break;
		case DOWN:	_sprite.move(0, (VELOCITY * frameTime));  break;
		case LEFT:	_sprite.move(-(VELOCITY * frameTime), 0); break;
		case RIGHT:	_sprite.move((VELOCITY * frameTime), 0);  break;
	}
}

//Handles non-keyboard events, like rotation:
void Helirin::handleEvents(float frameTime)
{
	//Rotate Helirin:
	_sprite.rotate(ROTATION_SPEED * frameTime);

	//Check if we've collided with anything:
	//[COLLISION CHECK CODE]
}

unsigned short int Helirin::getLives()
{
	return _lives;
}

sf::Sprite& Helirin::getSprite()
{
	return _sprite;
}
