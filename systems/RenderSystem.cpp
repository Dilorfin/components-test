#include "RenderSystem.hpp"

void RenderSystem::setRenderTarger(sf::RenderTarget* renderTarget)
{
	this->renderTarget = renderTarget;
}

sf::RenderTarget* RenderSystem::getRenderTarget()
{
	assert(!!renderTarget);
	return renderTarget;
}

void RenderSystem::addItem(BaseRenderComponent* item)
{
	items.push_back(item);
}

void RenderSystem::removeItem(BaseRenderComponent* item)
{
	items.erase(std::remove(std::begin(items), std::end(items), item), std::end(items));
}

void RenderSystem::render() const
{
	assert(!!renderTarget);

	for(auto* item : items)
	{
		item->render(*renderTarget);
	}
}
