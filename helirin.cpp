//helirin.cpp
#include "helirin.h"

//The number of degrees the Helirin rotates per second:
const float ROTATION_SPEED = 90.0;

//The number of pixels moved in a single second
//of constant movement in any given direction:
const float VELOCITY = 100.0;

//The time in seconds it takes for the Helirin to
//'cooldown' after colliding with a wall. During the
//'cooldown' period, it spins the other way:
const float COOLDOWN = 0.15;

#ifdef _WIN32
	const std::string HELIRIN_IMG_PATH = "assets\\helirin\\helirin.png";
#else
	const std::string HELIRIN_IMG_PATH = "assets/helirin/helirin.png";
#endif

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
	_sprite.setOrigin((_sprite.getLocalBounds().width / 2),   //x 
					  (_sprite.getLocalBounds().height / 2)); //y

	//Initalise the directional vectors:
	_previousDirection.x = 0;
	_previousDirection.y = 0;
	_currentDirection.x = 0;
	_currentDirection.y = 0;

	_sprite.setPosition(300, 300);

	_lives = 3;
}

void Helirin::move(Direction d)
{
	switch(d)
	{
		case UP:    if(_currentDirection.y > -1) _currentDirection.y--; break;
		case DOWN:  if(_currentDirection.y <  1) _currentDirection.y++; break;
		case LEFT:  if(_currentDirection.x > -1) _currentDirection.x--; break;
		case RIGHT: if(_currentDirection.x <  1) _currentDirection.x++; break;
	}
}

//Handles non-keyboard events, like rotation:
void Helirin::handleEvents(float frameTime)
{
	//Checks if we recently collided, and if so, spin the other way 
	//around, and move in the opposite direction to the collision:
	if(_hitTimer.getElapsedTime().asSeconds() <= COOLDOWN)
	{
		//Move the Helirin away at a slightly faster rate:
		_sprite.move(
					(_previousDirection.x * ((-VELOCITY * 2) * frameTime)), 
					(_previousDirection.y * ((-VELOCITY * 2) * frameTime)));

		//Rotate the Helirin:
		_sprite.rotate(-ROTATION_SPEED * frameTime);
	}
	else
	{

		//Move the Helirin:
		_sprite.move(
					(_currentDirection.x * (VELOCITY * frameTime)),
					(_currentDirection.y * (VELOCITY * frameTime)));

		//Save the direction moved in, but only if it's not empty:
		if((_currentDirection.x != 0) || (_currentDirection.y != 0))
			_previousDirection = _currentDirection;

		//Reset the current movement vector:
		_currentDirection.x = 0;
		_currentDirection.y = 0;

		//Rotate the Helirin:
		_sprite.rotate(ROTATION_SPEED * frameTime);
	}
}

bool Helirin::checkCollision(sf::ConvexShape& s)
{
	sf::FloatRect r = _sprite.getGlobalBounds();
	sf::Vector2f p[4];
	p[0] = sf::Vector2f(r.left, r.top);
	p[1] = sf::Vector2f((r.left + r.width), r.top);
	p[2] = sf::Vector2f(r.left, (r.top + r.height));
	p[3] = sf::Vector2f((r.left + r.width), (r.top + r.height));

	unsigned int nvert = s.getPointCount();

	//Uses the ray casting algorithm on the 4 corners of the Helirin, as found
	//on www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html:
	for(unsigned int i = 0; i < 4; i++)
	{
		bool collide = true;
		for(unsigned int j = 0, k = (nvert - 1); j < nvert; k = j++)
		{
			if(((s.getPoint(j).y > p[i].y) != (s.getPoint(k).y > p[i].y)) &&
				(p[i].x < (s.getPoint(k).x - s.getPoint(j).x) *
				(p[i].y - s.getPoint(j).y) / 
				(s.getPoint(k).y - s.getPoint(j).y) + s.getPoint(j).x))
					collide = !collide;
		}
		if(collide)
			return true;
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
