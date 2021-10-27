#include "RenderComponent.hpp"

#include "../systems/RenderSystem.hpp"

RenderComponent::RenderComponent()
{
	RenderSystem::getInstance()->addItem(this);
}

RenderComponent::~RenderComponent()
{
	RenderSystem::getInstance()->removeItem(this);
}
