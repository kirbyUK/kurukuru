#include "level.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>

//The number of seconds added if the player crashes:
float PENALTY = 3.0;

//Seperates the co-ordinates in the level's file:
std::string DELIMITER = "->";

Level::Level(std::string path)
{
	std::ifstream in(path.c_str());
	if(! in)
		throw "oh noes!";

	std::string theme = "";
	std::string line = "";
	while(line != ";;")
	{
		getline(in, line);

		//Skip comments and whitespace:
		if((line[0] == '#') || (line[0] == '\0'))
			continue;

		//Read appropriate meta-data and save it:
		if(line.find("name=") != std::string::npos)
			_name = line.substr(5, (line.size() - 5));
		else if(line.find("author=") != std::string::npos)
			_author = line.substr(7, (line.size() - 7));
		else if(line.find("theme=") != std::string::npos)
			theme = line.substr(6, (line.size() - 6));
	}
	//The rest of the file should be the points (if not someone
	//has done their job wrong), so just read until the end:
	std::string co_ords = "";
	while(in.good())
	{
		getline(in, line);

		//Skip comments and whitespace:
		if((line[0] == '#') || (line[0] == '\0'))
			continue;

		co_ords += line;
	}
	std::vector <sf::Vector2f> points;
	unsigned int i = 0;
	while(co_ords.find(DELIMITER, i) != std::string::npos)
	{
		//Perl has ruined me, this whole process could be SO much easier...
		std::string co_ord = co_ords.substr(i, (co_ords.find(DELIMITER, i) - i));
		i = (co_ords.find(DELIMITER, i) + DELIMITER.size());

		//error checking lol

		//We should now have (X,Y), extract the values:
		int x = atoi(co_ord.substr(1, (co_ord.find(",") - 1)).c_str());
		int y = (atoi(co_ord.substr(co_ord.find(",") + 1, std::string::npos - 1).c_str()));

		//Create a sf::Vector2f with our values, put them to the correct scale
		//and add them to the vector of vectors (haha) that will become the shape:
		sf::Vector2f v((x * 50), (y * 50));
		points.push_back(v);
	}
	//There should be one more point (because the last point doesn't have
	//a delimiter after it), so grab that:
	if(i < co_ords.size())
	{
		std::string co_ord = co_ords.substr(i, (co_ords.size() - i));

		int x = atoi(co_ord.substr(1, (co_ord.find(",") - 1)).c_str());
		int y = (atoi(co_ord.substr(co_ord.find(",") + 1, std::string::npos - 1).c_str()));

		sf::Vector2f v((x * 50), (y * 50));
		points.push_back(v);
	}

	//All the points are read, make the shape:
	_shape.setPointCount(points.size());
	for(unsigned int i = 0; i < points.size(); i++)
		_shape.setPoint(i, points[i]);

	//Work out which textures to use:
	if(theme == "meadow")
		_theme = new Theme(MEADOW);

	_shape.setTexture(&_theme->getTexture());
	_shape.setTextureRect(sf::IntRect(0, 0, 400, 400));

	//Make the outline:
	_shape.setOutlineThickness(7);
	_shape.setOutlineColor(sf::Color::Red);

	//Reset the clock (THIS SHOULD BE MOVED TO level::begin())
	_levelTimer.restart();
	_penalties = 0;
}

Level::~Level()
{
	delete _theme;
}

void Level::begin()
{
	//stuff
}

void Level::handleEvents()
{
	//stuff
}

void Level::resizeBackground(sf::View v)
{
	sf::Sprite* b = &_theme->getBackground();
	b->setPosition((v.getCenter().x - 1000), (v.getCenter().y - 1000));
	b->setTextureRect(sf::IntRect(0, 0, v.getSize().x * 4, v.getSize().y * 4));
}

void Level::penalise()
{
	_penalties++;
}

sf::ConvexShape& Level::getShape()
{
	return _shape;
}

sf::Sprite& Level::getBackground()
{
	return _theme->getBackground();
}

std::string Level::getElapsedTime()
{
	sf::Time t = (_levelTimer.getElapsedTime() + (sf::seconds(PENALTY * _penalties)));
	float total = t.asSeconds();
	int minutes = total / 60;
	int seconds = int(total) % 60;
	int milliseconds = t.asMilliseconds() % 100;

	std::stringstream ss;
	ss << "TIME: ";

	//Append a zero to the minutes if nessecary:
	if(minutes < 10)
		ss << "0" << minutes << "'";
	else
		ss << minutes << "'";

	//Append a zero to the seconds if nessecary:
	if(seconds < 10)
		ss << "0" << seconds << "\"";
	else
		ss << seconds << "\"";

	ss << milliseconds;
	return ss.str();
}
