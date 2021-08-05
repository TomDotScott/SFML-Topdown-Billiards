#include "Ball.h"
#include "Constants.h"

Ball::Ball(const sf::Vector2f& position) :
	m_position(position),
	m_velocity(0.f, 0.f),
	m_ballState(eBallState::e_stationary),
	m_selected(false)
{
	m_ball.setRadius(constants::k_ballRadius);
	m_ball.setFillColor(sf::Color::White);
}

void Ball::Update(const float deltaTime, const int mouseX, const int mouseY, const bool mousePressed)
{
	switch (m_ballState) {
	case eBallState::e_stationary:
		// TODO: Take mouse input
		if (mousePressed)
		{
			// Find the distance from the centre of the ball
			const sf::Vector2f ballCentre{
				m_position.x + constants::k_ballRadius,
				m_position.y + constants::k_ballRadius
			};

			const sf::Vector2f mouseToBall{ ballCentre.x - static_cast<float>(mouseX) , ballCentre.y - static_cast<float>(mouseY) };

			const float sqrDistance = powf(mouseToBall.x, 2.f) + powf(mouseToBall.y, 2.f);


			if (m_selected) {
				const float mag = sqrtf(sqrDistance);
				m_velocity = mouseToBall / mag;

				m_velocity *= 100.f;

				printf("MOUSE POSITION: (%i, %i)\nBALL CENTRE: (%f, %f)\nSQR DISTANCE: %f\nDISTANCE: %f\nNew velocity: (%f, %f)\n\n", mouseX, mouseY, ballCentre.x, ballCentre.y, sqrDistance, sqrtf(sqrDistance), m_velocity.x, m_velocity.y);

			}else
			{
				// Select the ball if it's in range
				if (sqrDistance < powf(constants::k_ballRadius, 2))
				{
					printf("Ball Selected\n");
					m_selected = true;
				}
			}

		}

		if (m_selected && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_ballState = eBallState::e_moving;
			m_selected = false;
		}

		break;

	case eBallState::e_moving:
		m_velocity.x < 0 ? m_velocity.x += constants::k_friction * deltaTime : m_velocity.x -= constants::k_friction * deltaTime;
		m_velocity.y < 0 ? m_velocity.y += constants::k_friction * deltaTime : m_velocity.y -= constants::k_friction * deltaTime;

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

		if((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y) < 0.01f)
		{
			m_velocity = { 0.f, 0.f };
			m_ballState = eBallState::e_stationary;
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
