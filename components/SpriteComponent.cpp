#include "SpriteComponent.hpp"

#include "../core/GameObject.hpp"
#include "TransformComponent.hpp"

void SpriteComponent::start()
{
	gameObject->getComponent<TransformComponent>();
}

void SpriteComponent::render(sf::RenderTarget& renderTarget)
{
	renderTarget.draw(sprite);
}
