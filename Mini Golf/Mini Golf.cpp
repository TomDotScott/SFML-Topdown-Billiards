#include <iostream>

#include "Ball.h"
#include "Constants.h"
#include "SFML/Graphics.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(constants::k_screenWidth, constants::k_screenHeight), "Minigolf");

	Ball ball({
		static_cast<float>(constants::k_screenWidth) / 2.f,
		static_cast<float>(constants::k_screenHeight) / 2.f
		}
	);

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

		ball.Update(deltaTime);
		
		window.clear();


		ball.Render(window);


		window.display();
	}

	return 0;
}