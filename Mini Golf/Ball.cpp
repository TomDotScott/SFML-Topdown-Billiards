#include "Ball.h"

#include "Constants.h"

Ball::Ball(const sf::Vector2f& position) :
	m_position(position),
	m_velocity(50.f, 50.f),
	m_ballState(eBallState::e_moving)
{
	m_ball.setRadius(constants::k_ballRadius);
	m_ball.setFillColor(sf::Color::Green);
}

void Ball::Update(const float deltaTime)
{
	switch (m_ballState) {
	case eBallState::e_stationary:
		// TODO: Take mouse input
		break;
	case eBallState::e_moving:

		m_position.x += m_velocity.x * deltaTime;
		m_position.y += m_velocity.y * deltaTime;

		// Check Boundaries
		if (m_position.x < 0 || m_position.x > constants::k_screenWidth - (constants::k_ballRadius * 2))
		{
			m_velocity.x *= -1;
		}

		if (m_position.y < 0 || m_position.y > constants::k_screenHeight - (constants::k_ballRadius * 2))
		{
			m_velocity.y *= -1;
		}

		break;
	default:
		break;
	}
}

void Ball::Render(sf::RenderWindow& window)
{
	m_ball.setPosition(m_position);

	window.draw(m_ball);
}
