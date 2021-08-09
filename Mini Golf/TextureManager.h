#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>

class TextureManager
{
public:
	static TextureManager* GetInstance();

	bool LoadTexture(const std::string& fileName, const std::string& textureIdentifier);
	bool RemoveTexture(const std::string& textureIdentifier);
	void DrawTexture(const std::string& textureIdentifier, const sf::Vector2f& position, sf::RenderWindow& window, sf::Color colour = sf::Color::White);

private:
	static TextureManager* instance;
	
	std::unordered_map<std::string, sf::Texture*> m_textureData;

	TextureManager() = default;
};
