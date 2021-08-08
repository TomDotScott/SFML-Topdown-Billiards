#pragma once
namespace helpers
{
	inline constexpr float clamp(const float min, const float max, const float val)
	{
		if (val < min) return min;

		if (val > max) return max;

		return val;
	}

	inline constexpr float lerp(const float a, const float b, const float t)
	{
		return a * (1 - t) + b * t;
	}

	inline constexpr float inverse_lerp(const float a, const float b, const float t)
	{
		return (t - a) / (b - a);
	}

	inline float sqr_magnitude(const sf::Vector2f v)
	{
		return std::powf(v.x, 2) + std::powf(v.y, 2);
	}

	inline float magnitude(const sf::Vector2f v)
	{
		return std::sqrtf(sqr_magnitude(v));
	}

	inline sf::Vector2f normalise(const sf::Vector2f v)
	{
		const float mag = magnitude(v);

		return v / mag;
	}

	inline int rand_range(const int min, const int max)
	{
		static bool first = true;

		if(first)
		{
			srand(time(nullptr));
			first = false;
		}

		return min + (rand() % (max - min + 1));
	}

	static int get_next_available_id()
	{
		static int id = 0;
		return id++;
	}
}