#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

enum class eBallState
{
	e_stationary, e_moving
};

class Ball
{
public:
	explicit Ball(const sf::Vector2f& position);
	void Update(float deltaTime);
	void Render(sf::RenderWindow& window);

private:
	sf::CircleShape m_ball;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	eBallState m_ballState;

};

