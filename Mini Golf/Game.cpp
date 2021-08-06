#include "Game.h"

#include "Constants.h"
#include "HelperFunctions.h"

Game::Game() :
	m_ball(
		{
	static_cast<float>(constants::k_screenWidth) / 2.f,
		static_cast<float>(constants::k_screenHeight) / 2
		}),
	m_isBallSelected(false)
{
}

void Game::Update(const float deltaTime, const int mouseX, const int mouseY, const bool mousePressed)
{
	UpdateInput(mouseX, mouseY, mousePressed);
	m_ball.Update(deltaTime);
}

void Game::Render(sf::RenderWindow& window)
{
	m_ball.Render(window);
}

void Game::UpdateInput(const int mouseX, const int mouseY, const bool mousePressed)
{
	if (m_ball.GetState() == eBallState::e_stationary) {
		if (mousePressed)
		{
			// Find the distance from the centre of the ball
			const sf::Vector2f ballCentre{
				m_ball.GetPosition().x + constants::k_ballRadius,
				m_ball.GetPosition().y + constants::k_ballRadius
			};

			const sf::Vector2f mouseToBall{ ballCentre.x - static_cast<float>(mouseX) , ballCentre.y - static_cast<float>(mouseY) };

			const float sqrDistance = powf(mouseToBall.x, 2.f) + powf(mouseToBall.y, 2.f);


			if (m_isBallSelected) {
				// The distance between the ball and the mouse
				const float mag = sqrtf(sqrDistance);

				// Vector pointing in the right direction
				m_ballShootVelocity = mouseToBall / mag;

				// Clamp the distance dragged between the min and max
				float clampedDistance = helpers::clamp(constants::k_minMouseDistance, constants::k_maxMouseDistance, mag);

				clampedDistance *= constants::k_velocityMultiplier;

				m_ballShootVelocity *= clampedDistance;

				printf("Distance between mouse and ball: %f\n\n\n", mag);


			}
			else
			{
				// Select the ball if it's in range
				if (sqrDistance < powf(constants::k_ballRadius, 2))
				{
					printf("Ball Selected\n");
					m_isBallSelected = true;
				}
			}
		}
		else
		{
			if (m_isBallSelected) {
				m_ball.Shoot(m_ballShootVelocity);
				m_isBallSelected = false;
			}
		}
	}
}