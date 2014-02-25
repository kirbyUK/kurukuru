#include "kuru.h"
#include <iostream>

int main()
{
	if(! Kuru::init())
	{
		std::cerr << "Failed to load '" << KURU_IMG_PATH << "'!\n"; 
		return -1;
	}
	Kuru kuru;

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
		kuru.handleEvents(frameTime);

		window.clear(sf::Color::White);
		window.draw(kuru.getSprite());
		window.display();

		frameTime = fps.restart().asSeconds();
	}
	return 0;
}
