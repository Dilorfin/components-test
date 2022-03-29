#include "RenderSystem.hpp"

void RenderSystem::setRenderTarget(sf::RenderTarget* renderTarget)
{
	this->renderTarget = renderTarget;
}

sf::RenderTarget* RenderSystem::getRenderTarget() const
{
	assert(renderTarget);
	return renderTarget;
}

void RenderSystem::add(BaseRenderComponent* item)
{
	items.push_back(item);
}

void RenderSystem::remove(BaseRenderComponent* item)
{
	items.erase(std::remove(std::begin(items), std::end(items), item), std::end(items));
}

void RenderSystem::render() const
{
	assert(renderTarget);

	for(auto* item : items)
	{
		item->render(*renderTarget);
	}
}
