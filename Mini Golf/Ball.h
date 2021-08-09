#pragma once
#include <SFML/Graphics.hpp>
#include <set>

enum class eBallState
{
	e_stationary, e_moving
};

enum class eBallType
{
	e_none, e_cueBall, e_redBall, e_yellowBall, e_blackBall
};

class Ball
{
public:
	Ball();
	Ball(const sf::Vector2f& position, eBallType type);

	void Update(float deltaTime);
	void Render(sf::RenderWindow& window) const;

	void Shoot(const sf::Vector2f& velocity);

	void Collide(Ball& other) const;

	int GetId() const;

	void SetState(eBallState state);
	eBallState GetState() const;

	eBallType GetType() const;

	sf::Vector2f GetPosition() const;
	sf::Vector2f GetCentrePosition() const;

	sf::Vector2f GetVelocity() const;

private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;

	eBallState m_ballState;
	eBallType m_type;

	int m_id;
};

