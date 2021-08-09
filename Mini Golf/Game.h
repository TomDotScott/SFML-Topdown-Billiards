#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "Ball.h"

class Game
{
public:
	Game();
	void Update(float deltaTime, int mouseX, int mouseY, bool mousePressed);
	void Render(sf::RenderWindow& window);


private:
	std::array<Ball, 16> m_balls;
	sf::Vector2f m_cueBallShootVelocity;
	bool m_isCueBallSelected;

	sf::RectangleShape m_powerBar;
	sf::Sprite m_backgroundSprite;

	void UpdateInput(int mouseX, int mouseY, bool mousePressed);
	void CheckCollisions();
};

