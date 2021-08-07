#include "Ball.h"
#include "Constants.h"
#include "HelperFunctions.h"

Ball::Ball(const sf::Vector2f& position) :
	m_position(position),
	m_velocity(0.f, 0.f),
	m_ballState(eBallState::e_stationary)
{
	m_ball.setRadius(constants::k_ballRadius);
	m_ball.setFillColor(sf::Color::White);
}

void Ball::Update(const float deltaTime)
{
	if (m_ballState == eBallState::e_moving) {
		m_velocity.x < 0 ? m_velocity.x += constants::k_friction * deltaTime : m_velocity.x -= constants::k_friction * deltaTime;
		m_velocity.y < 0 ? m_velocity.y += constants::k_friction * deltaTime : m_velocity.y -= constants::k_friction * deltaTime;

		m_position = m_position + (m_velocity * deltaTime);

		// Check Boundaries
		if (m_position.x < 0.f && m_velocity.x < 0.f || m_position.x > constants::k_screenWidth - constants::k_ballRadius * 2 && m_velocity.x > 0.f)
		{
			m_velocity.x *= -constants::k_bounceDampen;
		}

		if (m_position.y < 0.f && m_velocity.y < 0.f || m_position.y > constants::k_screenHeight - constants::k_ballRadius * 2 && m_velocity.y > 0.f)
		{
			m_velocity.y *= -constants::k_bounceDampen;
		}

		if ((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y) < 0.001f)
		{
			m_velocity = { 0.f, 0.f };
			m_ballState = eBallState::e_stationary;
		}


		// printf("Velocity: (%f, %f)\n", m_velocity.x, m_velocity.y);
	}
}

void Ball::Render(sf::RenderWindow& window)
{
	m_ball.setPosition(m_position);

	window.draw(m_ball);
}

void Ball::Shoot(const sf::Vector2f& velocity)
{
	m_velocity = velocity;
	m_ballState = eBallState::e_moving;
}

void Ball::SetState(const eBallState state)
{
	m_ballState = state;
}

eBallState Ball::GetState() const
{
	return m_ballState;
}

sf::Vector2f Ball::GetPosition() const
{
	return m_position;
}
