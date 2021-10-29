#pragma once
#include <list>
#include <SFML/Graphics.hpp>

#include "../core/SystemLocator.hpp"

class RenderComponent;

class RenderSystem final : public System<RenderSystem>
{
private:
	std::list<RenderComponent*> items;
public:
	void addItem(RenderComponent* item);
	void removeItem(RenderComponent* item);

	void render(sf::RenderTarget& renderTarget) const;
};

#include "../components/RenderComponent.hpp"