#include "AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite()
	: Sprite(texture), animation(*this)
{}

void AnimatedSprite::update(const sf::Time& deltaTime)
{
	animation.update(deltaTime);
}

void AnimatedSprite::update(const int64_t microsecondsElapsed)
{
	this->update(sf::microseconds(microsecondsElapsed));
}

void AnimatedSprite::addFrame(const sf::IntRect& frame)
{
	animation.addFrame(frame);
}

void AnimatedSprite::createMaskFromColor(const sf::Color color)
{
	sf::Image image = texture.copyToImage();
	image.createMaskFromColor(color);
	texture.loadFromImage(image);
}

bool AnimatedSprite::loadFromFile(const std::string& filename)
{
	return texture.loadFromFile(filename);
}