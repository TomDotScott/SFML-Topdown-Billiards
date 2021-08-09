#pragma once

namespace constants
{
	constexpr int k_screenWidth = 720;
	constexpr int k_screenHeight = 480;

	const sf::Vector2f k_tableTopLeft{ 62.f, 121.f };
	const sf::Vector2f k_tableBottomRight{ 658.f, 425.f };

	constexpr float k_friction = 125.7f;
	constexpr float k_bounceDampen = 0.6f;
	constexpr float k_ballRadius = 8.f;

	constexpr float k_minMouseDistance = 15.f;
	constexpr float k_maxMouseDistance = 150.f;

	constexpr float k_velocityMultiplier = 4.5f;

}
