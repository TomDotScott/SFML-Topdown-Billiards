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
	void Update(float deltaTime);
	void Render(sf::RenderWindow& window);

	void Shoot(const sf::Vector2f& velocity);

	void SetState(eBallState state);
	eBallState GetState() const;

	sf::Vector2f GetPosition() const;

private:
	sf::CircleShape m_ball;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	eBallState m_ballState;
};

