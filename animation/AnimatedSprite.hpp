#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Animation.hpp"

class AnimatedSprite final : public sf::Sprite
{
private:
	sf::Vector2i size;

	sf::Texture texture;

	Animation animation;

public:
	AnimatedSprite();
	~AnimatedSprite() override = default;
	AnimatedSprite(const AnimatedSprite& animation) = default;
	AnimatedSprite(AnimatedSprite&& animation) = default;

	AnimatedSprite& operator=(const AnimatedSprite& animation) = default;
	AnimatedSprite& operator=(AnimatedSprite&& animation) = default;

	void update(const sf::Time& deltaTime);
	void update(const int64_t microsecondsElapsed);

	void addFrame(const sf::Vector2i& frame);
	void setFrameSize(const sf::Vector2i& frameSize);

	void setSize(float x, float y);
	void setSize(const sf::Vector2f& size);

	void createMaskFromColor(sf::Color color);

	bool loadFromFile(const std::string& filename);
};