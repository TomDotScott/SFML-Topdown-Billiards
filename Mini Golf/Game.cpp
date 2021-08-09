#include "Game.h"

#include "Constants.h"
#include "HelperFunctions.h"
#include "TextureManager.h"

Game::Game() :
	m_isCueBallSelected(false),
	m_powerBar({ 6.f, 40.f })
{
	TextureManager::GetInstance()->LoadTexture("Resources/Pool_Table.png", "Background");
	TextureManager::GetInstance()->LoadTexture("Resources/Pool_Ball.png", "Ball");


	m_balls[0] = Ball(sf::Vector2f(constants::k_screenWidth / 2.f, constants::k_screenHeight / 2.f), eBallType::e_cueBall);
	m_balls[1] = Ball(sf::Vector2f(helpers::rand_range(0, constants::k_screenWidth), helpers::rand_range(0, constants::k_screenHeight)), eBallType::e_redBall);
	m_balls[2] = Ball(sf::Vector2f(helpers::rand_range(0, constants::k_screenWidth), helpers::rand_range(0, constants::k_screenHeight)), eBallType::e_redBall);
	m_balls[3] = Ball(sf::Vector2f(helpers::rand_range(0, constants::k_screenWidth), helpers::rand_range(0, constants::k_screenHeight)), eBallType::e_redBall);
	m_balls[4] = Ball(sf::Vector2f(helpers::rand_range(0, constants::k_screenWidth), helpers::rand_range(0, constants::k_screenHeight)), eBallType::e_redBall);
	m_balls[5] = Ball(sf::Vector2f(helpers::rand_range(0, constants::k_screenWidth), helpers::rand_range(0, constants::k_screenHeight)), eBallType::e_redBall);
	m_balls[6] = Ball(sf::Vector2f(helpers::rand_range(0, constants::k_screenWidth), helpers::rand_range(0, constants::k_screenHeight)), eBallType::e_redBall);
	m_balls[7] = Ball(sf::Vector2f(helpers::rand_range(0, constants::k_screenWidth), helpers::rand_range(0, constants::k_screenHeight)), eBallType::e_redBall);
	m_balls[8] = Ball(sf::Vector2f(helpers::rand_range(0, constants::k_screenWidth), helpers::rand_range(0, constants::k_screenHeight)), eBallType::e_yellowBall);
	m_balls[9] = Ball(sf::Vector2f(helpers::rand_range(0, constants::k_screenWidth), helpers::rand_range(0, constants::k_screenHeight)), eBallType::e_yellowBall);
	m_balls[10] = Ball(sf::Vector2f(helpers::rand_range(0, constants::k_screenWidth), helpers::rand_range(0, constants::k_screenHeight)), eBallType::e_yellowBall);
	m_balls[11] = Ball(sf::Vector2f(helpers::rand_range(0, constants::k_screenWidth), helpers::rand_range(0, constants::k_screenHeight)), eBallType::e_yellowBall);
	m_balls[12] = Ball(sf::Vector2f(helpers::rand_range(0, constants::k_screenWidth), helpers::rand_range(0, constants::k_screenHeight)), eBallType::e_yellowBall);
	m_balls[13] = Ball(sf::Vector2f(helpers::rand_range(0, constants::k_screenWidth), helpers::rand_range(0, constants::k_screenHeight)), eBallType::e_yellowBall);
	m_balls[14] = Ball(sf::Vector2f(helpers::rand_range(0, constants::k_screenWidth), helpers::rand_range(0, constants::k_screenHeight)), eBallType::e_yellowBall);
	m_balls[15] = Ball(sf::Vector2f(helpers::rand_range(0, constants::k_screenWidth), helpers::rand_range(0, constants::k_screenHeight)), eBallType::e_blackBall);
	
}

void Game::Update(const float deltaTime, const int mouseX, const int mouseY, const bool mousePressed)
{
	UpdateInput(mouseX, mouseY, mousePressed);

	for (auto& ball : m_balls)
	{
		ball.Update(deltaTime);
	}

	printf("VelX: %f, VelY: %f\n", m_balls[0].GetVelocity().x, m_balls[0].GetVelocity().y);

	CheckCollisions();
}

void Game::Render(sf::RenderWindow& window)
{
	TextureManager::GetInstance()->DrawTexture("Background", { 0.f, 0.f }, window);

	for (auto& ball : m_balls)
	{
		ball.Render(window);
	}

	// Render the power bar next to the ball
	if (m_isCueBallSelected) {
		sf::RectangleShape powerBarOutline({ 8.f, -40.f });
		powerBarOutline.setFillColor(sf::Color::Black);

		float powerBarXPosition = m_balls[0].GetPosition().x + 25.f;
		float powerBarYPosition = m_balls[0].GetPosition().y + 2 * constants::k_ballRadius;

		powerBarOutline.setPosition({ powerBarXPosition, powerBarYPosition });
		window.draw(powerBarOutline);

		m_powerBar.setPosition({ powerBarXPosition + 1.f, powerBarYPosition + 1.f });

		window.draw(m_powerBar);
	}
}

void Game::UpdateInput(const int mouseX, const int mouseY, const bool mousePressed)
{
	if (m_balls[0].GetState() == eBallState::e_stationary) {
		if (mousePressed)
		{
			// Find the distance from the centre of the cue ball
			const sf::Vector2f ballCentre = m_balls[0].GetCentrePosition();

			const sf::Vector2f mouseToBall{ ballCentre.x - static_cast<float>(mouseX) , ballCentre.y - static_cast<float>(mouseY) };

			const float sqrDistance = helpers::sqr_magnitude(mouseToBall);


			if (m_isCueBallSelected) {
				// Vector pointing in the right direction
				m_cueBallShootVelocity = helpers::normalise(mouseToBall);

				// Clamp the distance dragged between the min and max
				const float clampedDistance = helpers::clamp(constants::k_minMouseDistance, constants::k_maxMouseDistance, helpers::magnitude(mouseToBall));

				m_cueBallShootVelocity *= clampedDistance * constants::k_velocityMultiplier;

				// Adjust power bar
				const float powerPercentage = clampedDistance / constants::k_maxMouseDistance;
				const float lerpedPowerBarHeight = helpers::lerp(1.f, 38.f, powerPercentage);

				m_powerBar.setSize({ m_powerBar.getSize().x, -lerpedPowerBarHeight });

			}
			else
			{
				// Select the ball if it's in range
				if (sqrDistance < powf(constants::k_ballRadius, 2))
				{
					m_isCueBallSelected = true;
				}
			}
		}
		else
		{
			if (m_isCueBallSelected) {
				m_balls[0].Shoot(m_cueBallShootVelocity);
				m_isCueBallSelected = false;
			}
		}
	}
}

void Game::CheckCollisions()
{
	for (auto& ball : m_balls)
	{
		const sf::Vector2f ballCentre = ball.GetCentrePosition();

		for (auto& otherBall : m_balls)
		{
			if (ball.GetId() != otherBall.GetId())
			{
				ball.Collide(otherBall);
			}
		}
	}
}
