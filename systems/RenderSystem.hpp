#pragma once
#include <list>
#include <SFML/Graphics.hpp>

#include "../core/SystemLocator.hpp"

class BaseRenderComponent;

class RenderSystem final : public System<RenderSystem>
{
private:
	std::list<BaseRenderComponent*> items;
public:
	void addItem(BaseRenderComponent* item);
	void removeItem(BaseRenderComponent* item);

	void render(sf::RenderTarget& renderTarget) const;
};

#include "../components/RenderComponent.hpp"
