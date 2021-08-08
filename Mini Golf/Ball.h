#pragma once
#include <SFML/Graphics.hpp>
#include <set>

enum class eBallState
{
	e_stationary, e_moving
};

class Ball
{
public:
	Ball();
	Ball(const sf::Vector2f& position, sf::Color colour);

	void Update(float deltaTime);
	void Render(sf::RenderWindow& window);

	void Shoot(const sf::Vector2f& velocity);

	void Collide(Ball& other) const;

	int GetId() const;

	void SetState(eBallState state);
	eBallState GetState() const;

	sf::Vector2f GetPosition() const;
	sf::Vector2f GetCentrePosition() const;

	sf::Vector2f GetVelocity() const;

private:
	sf::CircleShape m_ball;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	eBallState m_ballState;

	int m_id;
};

