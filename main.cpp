#include <iostream>
#include <sstream>

#include "helirin.h"
#include "interface.h"
#include "level.h"

float getAverageFPS(float);

int main()
{
	//Loads the Helirin image:
	if(! Helirin::init())
		return -1;
	//Loads the fonts:
	if(! Interface::init())
		return -1; 
	//Loads the level textures:
	if(! Theme::init())
		return -1;

	Helirin helirin;
	Interface interface;
	Level level("assets/levels/level2.lvl");

	sf::RenderWindow window(sf::VideoMode(800, 600), "KuruKuru Kuruin");
	sf::View view = window.getDefaultView();
	interface.update(view);

	sf::Event event;
	sf::Clock fps;
	float frameTime = 0.016;

	//Main game loop:
	while(window.isOpen())
	{
		//Check events:
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();

			//If the window is resized, resize the view
			//and reposition the text items:
			if(event.type == sf::Event::Resized)
			{
				view.setSize(event.size.width, event.size.height);
				window.setView(view);
				interface.update(view);
				level.resizeBackground(view);
			}
		}

		//Movement:
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			helirin.move(UP);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			helirin.move(DOWN);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			helirin.move(LEFT);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			helirin.move(RIGHT);

		//Non-player based events:
		helirin.handleEvents(frameTime);
		if(helirin.checkCollision(level.getShape()))
		{
			level.penalise();
			helirin.ouch(frameTime);
		}

		//Set the centre of the view to the Helirin:
		view.setCenter(helirin.getSprite().getPosition());
		window.setView(view);
		interface.update(view);

		//Create strings for the text:
		float averageFPS = getAverageFPS(1 / frameTime);
		if(averageFPS != -1)
		{
			std::stringstream ss;
			ss.precision(0);
			ss.setf(std::ios::fixed);
			ss << "FPS: " << averageFPS;
			interface.getText()[FPS].setString(ss.str());
		}
		interface.getText()[CLOCK].setString(level.getElapsedTime());

		//Clearing the window and redrawing everything:
		window.clear();
		window.draw(level.getBackground());
		window.draw(level.getShape());
		window.draw(helirin.getSprite());
		for(int i = 0; i < NUMBER_OF_TEXT_ITEMS; i++)
			window.draw(interface.getText()[i]);
		window.display();

		//Get the time of that frame:
		frameTime = fps.restart().asSeconds();
	}
	return 0;
}

float getAverageFPS(float time)
{
	static float times[150];
	static int i = 0;

	if(i < 150)
	{
		times[i++] = time;
		return -1;
	}
	else
	{
		float total = 0;
		for(int j = 0; j < 150; j++)
			total += times[j];
		i = 0;
		return total / 150;
	}
}
