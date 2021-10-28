#include "SpriteComponent.hpp"

#include "../core/GameObject.hpp"
#include "TransformComponent.hpp"

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
