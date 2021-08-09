#include "TextureManager.h"

TextureManager* TextureManager::GetInstance()
{
	if (!instance)
	{
		instance = new TextureManager();
	}

	return instance;
}

bool TextureManager::LoadTexture(const std::string& fileName, const std::string& textureIdentifier)
{
	auto* texture = new sf::Texture();

	if (texture->loadFromFile(fileName))
	{
		m_textureData[textureIdentifier] = texture;
		return true;
	}

	delete texture;
	return false;
}

bool TextureManager::RemoveTexture(const std::string& textureIdentifier)
{
	if (m_textureData.find(textureIdentifier) == m_textureData.end()) 
	{
		return false;
	}


	const auto* ptr = m_textureData[textureIdentifier];
	m_textureData.erase(textureIdentifier);

	delete ptr;
	return true;
}

void TextureManager::DrawTexture(const std::string& textureIdentifier, const sf::Vector2f& position, sf::RenderWindow& window, sf::Color colour)
{
	sf::Sprite sprite;
	sprite.setPosition(position);
	sprite.setColor(colour);
	sprite.setTexture(*m_textureData[textureIdentifier]);

	window.draw(sprite);
}

TextureManager* TextureManager::instance = nullptr;