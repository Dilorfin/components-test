#pragma once
#include <algorithm>
#include <list>
#include <SFML/Graphics.hpp>

#include "core/SystemLocator.hpp"

class BaseRenderComponent;

class RenderSystem final : public System<RenderSystem>
{
private:
	sf::RenderTarget* renderTarget = nullptr;
	std::list<BaseRenderComponent*> items;
public:
	void setRenderTarget(sf::RenderTarget* renderTarget);
	[[nodiscard]] sf::RenderTarget* getRenderTarget() const;

	void addItem(BaseRenderComponent* item);
	void removeItem(BaseRenderComponent* item);

	void render() const;
};

#include "../components/RenderComponent.hpp"
