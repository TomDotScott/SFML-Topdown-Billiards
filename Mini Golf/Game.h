#pragma once
#include <SFML/Graphics.hpp>

#include "Ball.h"

class Game
{
public:
	Game();
	void Update(float deltaTime, int mouseX, int mouseY, bool mousePressed);
	void Render(sf::RenderWindow& window);

private:
	Ball m_ball;
	sf::Vector2f m_ballShootVelocity;
	bool m_isBallSelected;

	sf::RectangleShape m_powerBar;

	void UpdateInput(int mouseX, int mouseY, bool mousePressed);
};

