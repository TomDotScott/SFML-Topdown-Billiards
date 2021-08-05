#pragma once
#include <SFML/Graphics.hpp>

enum class eBallState
{
	e_stationary, e_moving
};

class Ball
{
public:
	explicit Ball(const sf::Vector2f& position);
	void Update(float deltaTime, int mouseX, int mouseY, bool mousePressed);
	void Render(sf::RenderWindow& window);

private:
	sf::CircleShape m_ball;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	eBallState m_ballState;
	bool m_selected;
};

