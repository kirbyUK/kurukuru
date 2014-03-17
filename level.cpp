#include "level.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>

//Seperates the co-ordinates in the level's file:
const std::string DELIMITER = "->";

sf::Image Level::_images[TOTAL_NUMBER_OF_THEMES];
sf::Image Level::_backgrounds[TOTAL_NUMBER_OF_THEMES];

bool Level::init()
{
	if(! _images[MEADOW].loadFromFile(MEADOW_TEXTURE))
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

Level::Level(std::string path)
{
	std::ifstream in(path.c_str());
	if(! in)
		throw "oh noes!";

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
			_theme = line.substr(6, (line.size() - 6));
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
	if(_theme == "meadow")
	{
		_levelTexture.loadFromImage(_images[MEADOW]);
		_backgroundTexture.loadFromImage(_backgrounds[MEADOW]);
	}
	_levelTexture.setRepeated(true);
	_backgroundTexture.setRepeated(true);
	_shape.setTexture(&_levelTexture);
	_background.setTexture(_backgroundTexture);
	_shape.setTextureRect(sf::IntRect(0, 0, 400, 400));

	//Make the outline:
	_shape.setOutlineThickness(7);
	_shape.setOutlineColor(sf::Color::Red);
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
	_background.setPosition((v.getCenter().x - 1000), (v.getCenter().y - 1000));
	_background.setTextureRect(sf::IntRect(0, 0, v.getSize().x * 4, v.getSize().y * 4));
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
	return _background;
}

sf::Time Level::getElapsedTime()
{
	return (_levelTimer.getElapsedTime() + (sf::seconds(PENALTY * _penalties)));
}
