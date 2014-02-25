#include <iostream>
#include "helirin.h"
#include "interface.h"

int main()
{
	//Loads the Helirin image:
	if(! Helirin::init())
	{
		std::cerr << "Failed to load '" << KURU_IMG_PATH << "'!\n"; 
		return -1;
	}
	//Loads the fonts:
	if(! Interface::init())
		return -1; 

	Helirin helirin;
	Interface interface;

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
		}

		//Movement:
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			helirin.move(UP, frameTime);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			helirin.move(DOWN, frameTime);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			helirin.move(LEFT, frameTime);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			helirin.move(RIGHT, frameTime);

		//Non-player based events:
		helirin.handleEvents(frameTime);

		//Clearing the window and redrawing everything:
		window.clear(sf::Color::White);
		for(int i = 0; i < NUMBER_OF_TEXT_ITEMS; i++)
			window.draw(interface.getText()[i]);
		window.draw(helirin.getSprite());
		window.display();

		//Get the time of that frame:
		frameTime = fps.restart().asSeconds();
	}
	return 0;
}
