#include "Ball.h"
#include "Constants.h"
#include "HelperFunctions.h"
#include "TextureManager.h"

Ball::Ball() :
	m_position({}),
	m_velocity({}),
	m_ballState(eBallState::e_stationary),
	m_type(eBallType::e_none),
	m_id(helpers::get_next_available_id())
{
}

Ball::Ball(const sf::Vector2f& position, const eBallType type) :
	m_position(position),
	m_velocity(0.f, 0.f),
	m_ballState(eBallState::e_stationary),
	m_type(type),
	m_id(helpers::get_next_available_id())
{
}

void Ball::Update(const float deltaTime)
{
	if (m_ballState == eBallState::e_moving) {
		m_velocity.x < 0 ? m_velocity.x += constants::k_friction * deltaTime : m_velocity.x -= constants::k_friction * deltaTime;
		m_velocity.y < 0 ? m_velocity.y += constants::k_friction * deltaTime : m_velocity.y -= constants::k_friction * deltaTime;

		m_position = m_position + (m_velocity * deltaTime);

		// Check Boundaries
		if (m_position.x < constants::k_tableTopLeft.x && m_velocity.x < 0.f || m_position.x > constants::k_tableBottomRight.x - constants::k_ballRadius * 2 && m_velocity.x > 0.f)
		{
			m_velocity.x *= -constants::k_bounceDampen;
		}

		if (m_position.y < constants::k_tableTopLeft.y && m_velocity.y < 0.f || m_position.y > constants::k_tableBottomRight.y - constants::k_ballRadius * 2 && m_velocity.y > 0.f)
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

void Ball::Render(sf::RenderWindow& window) const
{
	sf::Color colour;

	switch (m_type) {
	case eBallType::e_none:
		colour = { 0, 0, 0, 0 };
		break;
	case eBallType::e_cueBall: 
		colour = sf::Color::White;
		break;
	case eBallType::e_redBall:
		colour = sf::Color::Red;
		break;
	case eBallType::e_yellowBall:
		colour = {255, 196, 0, 255};
		break;
	case eBallType::e_blackBall: 
		colour = {21, 34, 56, 255};
		break;
	}

	TextureManager::GetInstance()->DrawTexture("Ball", m_position, window, colour);
}

void Ball::Shoot(const sf::Vector2f& velocity)
{
	m_velocity += velocity;
	m_ballState = eBallState::e_moving;
}

void Ball::Collide(Ball& other) const
{
	const sf::Vector2f otherBallCentre = other.GetCentrePosition();

	const sf::Vector2f ab = otherBallCentre - GetCentrePosition();

	if (helpers::sqr_magnitude(ab) < std::powf(constants::k_ballRadius * 2, 2))
	{
		// Get the magnitude of the ball's velocity
		const float directionMultiplier = helpers::magnitude(m_velocity) * 0.65f;

		// Shoot the other ball in the direction ab
		const sf::Vector2f direction = helpers::normalise(ab) * directionMultiplier;

		other.Shoot(direction);
	}
}

int Ball::GetId() const
{
	return m_id;
}

void Ball::SetState(const eBallState state)
{
	m_ballState = state;
}

eBallState Ball::GetState() const
{
	return m_ballState;
}

eBallType Ball::GetType() const
{
	return m_type;
}

sf::Vector2f Ball::GetPosition() const
{
	return m_position;
}

sf::Vector2f Ball::GetCentrePosition() const
{
	return { m_position.x + constants::k_ballRadius, m_position.y + constants::k_ballRadius };
}

sf::Vector2f Ball::GetVelocity() const
{
	return m_velocity;
}
