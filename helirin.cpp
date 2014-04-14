//helirin.cpp
#include "helirin.h"

sf::Image Helirin::_image;

bool Helirin::init()
{
	return _image.loadFromFile(HELIRIN_IMG_PATH);
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
	//Disable movement if we've collided:
	if(_hitTimer.getElapsedTime().asSeconds() > COOLDOWN)
	{
		switch(d)
		{
			case UP: 	_sprite.move(0, -(VELOCITY * frameTime)); break;
			case DOWN:	_sprite.move(0, (VELOCITY * frameTime));  break;
			case LEFT:	_sprite.move(-(VELOCITY * frameTime), 0); break;
			case RIGHT:	_sprite.move((VELOCITY * frameTime), 0);  break;
		}
		_directionMoved = d;
	}
}

//Handles non-keyboard events, like rotation:
void Helirin::handleEvents(float frameTime)
{
	//Checks if we recently collided, and if so,
	//spin the other way around, and move in the
	//opposite direction to the collision:
	if(_hitTimer.getElapsedTime().asSeconds() <= COOLDOWN)
	{
		_sprite.rotate(-ROTATION_SPEED * frameTime);	
		switch(_directionMoved)
		{
			case UP: 	_sprite.move(0, ((VELOCITY * 1.2) * frameTime)); break;
			case DOWN:	_sprite.move(0, -((VELOCITY * 1.2) * frameTime));  break;
			case LEFT:	_sprite.move(((VELOCITY * 1.2) * frameTime), 0); break;
			case RIGHT:	_sprite.move(-((VELOCITY * 1.2) * frameTime), 0);  break;
		}
	}
	else
		_sprite.rotate(ROTATION_SPEED * frameTime);
}

bool Helirin::checkCollision(sf::ConvexShape& s)
{
	bool collide = false;

	//The only points that matter are the 4 corners of the
	//Helirin, as if we've 'collided', it'll be one of these
	//corners that hits the wall:
	float left = _sprite.getGlobalBounds().left;
	float top = _sprite.getGlobalBounds().top;
	float width = _sprite.getGlobalBounds().width;
	float height = _sprite.getGlobalBounds().height;
	if(! s.getGlobalBounds().contains(left, top))
		collide = true;
	if(! s.getGlobalBounds().contains(left, (top + height)))
		collide = true;
	if(! s.getGlobalBounds().contains((left + width), top))
		collide = true;
	if(! s.getGlobalBounds().contains((left + width), (top + height)))
		collide = true;

	return collide;
}

void Helirin::ouch(float f)
{
	_hitTimer.restart();
	_lives--;
}

unsigned short int Helirin::getLives()
{
	return _lives;
}

sf::Sprite& Helirin::getSprite()
{
	return _sprite;
}
