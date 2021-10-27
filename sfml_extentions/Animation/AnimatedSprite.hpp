#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Animation.hpp"

class AnimatedSprite final : public sf::Sprite
{
private:
	sf::Texture texture;
	
	Animation animation;

public:
	AnimatedSprite();

	AnimatedSprite& operator=(const AnimatedSprite& animation) = default;
	AnimatedSprite& operator=(AnimatedSprite&& animation) = default;

	void update(const sf::Time& deltaTime);
	void update(const int64_t microsecondsElapsed);

	void addFrame(const sf::IntRect& frame);

	void createMaskFromColor(sf::Color color);

	bool loadFromFile(const std::string& filename);
};