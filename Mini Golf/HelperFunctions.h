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
}