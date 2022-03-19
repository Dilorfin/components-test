#pragma once
#include <list>
#include <SFML/Graphics.hpp>

#include "../core/SystemLocator.hpp"

class BaseRenderComponent;

class RenderSystem final : public System<RenderSystem>
{
private:
	sf::RenderTarget* renderTarget = nullptr;
	std::list<BaseRenderComponent*> items;
public:
	void setRenderTarger(sf::RenderTarget* renderTarget);
	sf::RenderTarget* getRenderTarget();

	void addItem(BaseRenderComponent* item);
	void removeItem(BaseRenderComponent* item);

	void render() const;
};

#include "../components/RenderComponent.hpp"
