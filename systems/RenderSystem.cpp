#include "RenderSystem.hpp"

void RenderSystem::addItem(BaseRenderComponent* item)
{
	items.push_back(item);
}

void RenderSystem::removeItem(BaseRenderComponent* item)
{
	items.erase(std::remove(std::begin(items), std::end(items), item), std::end(items));
}

void RenderSystem::render(sf::RenderTarget& renderTarget) const
{
	for(auto* item : items)
	{
		item->render(renderTarget);
	}
}
