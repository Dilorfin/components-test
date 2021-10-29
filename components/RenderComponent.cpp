#include "RenderComponent.hpp"

#include "../systems/RenderSystem.hpp"

RenderComponent::RenderComponent()
{
	SystemLocator::getSystem<RenderSystem>()->addItem(this);
}

RenderComponent::~RenderComponent()
{
	SystemLocator::getSystem<RenderSystem>()->removeItem(this);
}
