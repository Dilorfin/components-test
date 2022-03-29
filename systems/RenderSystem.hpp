#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <list>

#include "../core/SystemLocator.hpp"

class BaseRenderComponent;

class RenderSystem final : public System<RenderSystem, BaseRenderComponent>
{
private:
	sf::RenderTarget* renderTarget = nullptr;
	std::list<BaseRenderComponent*> items;
public:
	void setRenderTarget(sf::RenderTarget* renderTarget);
	[[nodiscard]] sf::RenderTarget* getRenderTarget() const;

	void add(BaseRenderComponent* item) override;
	void remove(BaseRenderComponent* item) override;

	void render() const;

	void clear() override;
};

#include "../components/RenderComponent.hpp"
