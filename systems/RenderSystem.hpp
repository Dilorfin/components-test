#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class RenderComponent;

class RenderSystem final
{
private:
	std::vector<RenderComponent*> items;

	RenderSystem() = default;

public:
	static RenderSystem* getInstance()
	{
		static auto* instance = new RenderSystem;
		return instance;
	}

	void addItem(RenderComponent* item);
	void removeItem(RenderComponent* item);

	void render(sf::RenderTarget& renderTarget) const;
};

#include "../components/RenderComponent.hpp"