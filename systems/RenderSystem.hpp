#pragma once
#include <list>
#include <SFML/Graphics.hpp>

class RenderComponent;

class RenderSystem final
{
private:
	std::list<RenderComponent*> items;

	RenderSystem() = default;
	inline static RenderSystem* instance = nullptr;
public:
	RenderSystem(RenderSystem&&) = delete;
	RenderSystem(const RenderSystem&) = delete;
	auto operator=(RenderSystem&&) = delete;
	auto operator=(const RenderSystem&) = delete;

	static RenderSystem* getInstance()
	{
		if(instance == nullptr)
		{
			instance = new RenderSystem();
		}
		return instance;
	}

	void addItem(RenderComponent* item);
	void removeItem(RenderComponent* item);

	void render(sf::RenderTarget& renderTarget) const;
};

#include "../components/RenderComponent.hpp"