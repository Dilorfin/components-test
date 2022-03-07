#include "RenderSystem.hpp"

void RenderSystem::addItem(BaseRenderComponent* item)
{
	items.push_back(item);
}

void RenderSystem::removeItem(BaseRenderComponent* item)
{
	std::erase(items, item);
}

void RenderSystem::render(sf::RenderTarget& renderTarget) const
{
	for(auto* item : items)
	{
		item->render(renderTarget);
	}
}
