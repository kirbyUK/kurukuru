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
	unsigned int nvert = s.getPointCount();

	sf::FloatRect r = _sprite.getGlobalBounds();
	sf::Vector2f p[4];
	p[0] = sf::Vector2f(r.top, r.left);
	p[1] = sf::Vector2f(r.top, (r.left + r.width));
	p[2] = sf::Vector2f((r.top + r.height), r.left);
	p[3] = sf::Vector2f((r.top + r.height), (r.left + r.width));

	//Uses the ray casting algorithm on the 4 points of the Helirin, as found
	//on www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html:
	for(unsigned int i = 0; i < 4; i++)
	{
		for(unsigned int j = 0, k = (nvert - 1); j < nvert; k = j++)
		{
			if(((s.getPoint(j).y > p[i].y) != (s.getPoint(k).y > p[i].y)) &&
				(p[i].x < (s.getPoint(k).x - s.getPoint(j).x) *
				(p[j].y - s.getPoint(j).y) / 
				(s.getPoint(k).y - s.getPoint(j).y) + s.getPoint(j).x))
			return true;	
		}
	}
	return false;
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
