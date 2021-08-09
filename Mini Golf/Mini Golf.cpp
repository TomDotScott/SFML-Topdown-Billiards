#include <iostream>

#include "Ball.h"
#include "Constants.h"
#include "Game.h"
#include "SFML/Graphics.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(constants::k_screenWidth, constants::k_screenHeight), "Minigolf");

	Game game;

	sf::Clock clock;

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		float deltaTime = clock.getElapsedTime().asSeconds();
		clock.restart();

		const sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		
		window.clear(/*{0, 100, 0}*/);

		game.Update(deltaTime, mousePosition.x, mousePosition.y, sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
		game.Render(window);


		window.display();
	}

	return 0;
}