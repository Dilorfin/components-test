#include "RenderSystem.hpp"

void RenderSystem::addItem(RenderComponent* item)
{
	items.push_back(item);
}

void RenderSystem::removeItem(RenderComponent* item)
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
