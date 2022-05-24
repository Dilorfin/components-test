#include "../SpriteComponent.hpp"

SpriteComponent::SpriteComponent(const std::string& fileName)
{
	const bool textureLoaded = texture.loadFromFile(fileName);
	assert(textureLoaded);

	sprite.setTexture(texture);
		
	sprite.setOrigin({sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f});
}

SpriteComponent::SpriteComponent(const std::string& fileName, const sf::IntRect& rect)
{
	const bool textureLoaded = texture.loadFromFile(fileName, rect);
	assert(textureLoaded);
	
	sprite.setTexture(texture);
}

void SpriteComponent::setSize(const float x, const float y)
{
	const auto size = texture.getSize();
	sprite.setScale({x / size.x, y / size.y});
}

void SpriteComponent::setSize(const sf::Vector2f& size)
{
	this->setSize(size.x, size.y);
}

void SpriteComponent::start()
{
	transform = gameObject->getComponent<TransformComponent>();
	assert(transform);
}

void SpriteComponent::update(const int64_t deltaTime)
{
	sprite.setPosition(transform->position);
	sprite.setRotation(sf::degrees(transform->rotation));
}

void SpriteComponent::render(sf::RenderTarget& renderTarget)
{
	renderTarget.draw(sprite);
}
