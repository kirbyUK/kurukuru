#include <iostream>
#include "helirin.h"

int main()
{
	if(! Helirin::init())
	{
		std::cerr << "Failed to load '" << KURU_IMG_PATH << "'!\n"; 
		return -1;
	}
	Helirin helirin;

	sf::Clock fps;
	float frameTime = 0.016;
	sf::RenderWindow window(sf::VideoMode(800, 600), "KuruKuru Kuruin");
	sf::Event event;

	//Main game loop:
	while(window.isOpen())
	{
		//Check events:
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			helirin.move(UP, frameTime);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			helirin.move(DOWN, frameTime);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			helirin.move(LEFT, frameTime);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			helirin.move(RIGHT, frameTime);

		helirin.handleEvents(frameTime);

		window.clear(sf::Color::White);
		window.draw(helirin.getSprite());
		window.display();

		frameTime = fps.restart().asSeconds();
	}
	return 0;
}
