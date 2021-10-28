#include "SpriteComponent.hpp"

#include "../core/GameObject.hpp"
#include "TransformComponent.hpp"

SpriteComponent::SpriteComponent(const std::string& fileName)
{
	if (!texture.loadFromFile(fileName))
	{
		// error...
	}
	sprite.setTexture(texture);
		
	sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
}

SpriteComponent::SpriteComponent(const std::string& fileName, const sf::IntRect& rect)
{
	if (!texture.loadFromFile(fileName, rect))
	{
		// error...
	}
	sprite.setTexture(texture);
}

void SpriteComponent::setSize(const float x, const float y)
{
	const auto size = texture.getSize();
	sprite.setScale(x / size.x, y / size.y);
}

void SpriteComponent::setSize(const sf::Vector2f& size)
{
	this->setSize(size.x, size.y);
}

void SpriteComponent::start()
{
	transform = gameObject->getComponent<TransformComponent>();
}

void SpriteComponent::update(const int64_t deltaTime)
{
	sprite.setPosition(transform->position);
	sprite.setRotation(transform->rotation);
}

void SpriteComponent::render(sf::RenderTarget& renderTarget)
{
	renderTarget.draw(sprite);
}
