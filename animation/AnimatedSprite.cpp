#include "AnimatedSprite.hpp"

#include <SFML/Graphics/Image.hpp>
#include <SFML/System/Time.hpp>

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

void AnimatedSprite::addFrame(const sf::Vector2i& frame)
{
	animation.addFrame(frame);
}

void AnimatedSprite::setFrameSize(const sf::Vector2i& frameSize)
{
	animation.setFrameSize(frameSize);
}

void AnimatedSprite::setSize(const float x, const float y)
{
	this->setScale({x / size.x, y / size.y});
}

void AnimatedSprite::setSize(const sf::Vector2f& size)
{
	this->setSize(size.x, size.y);
}

void AnimatedSprite::createMaskFromColor(const sf::Color color)
{
	sf::Image image = texture.copyToImage();
	image.createMaskFromColor(color);
	// ReSharper disable once CppNoDiscardExpression
	texture.loadFromImage(image);
}

bool AnimatedSprite::loadFromFile(const std::string& filename)
{
	return texture.loadFromFile(filename);
}