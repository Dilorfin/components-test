#pragma once
#include <SFML/Graphics.hpp>
#include "../core/Component.hpp"
#include "../systems/RenderSystem.hpp"

class BaseRenderComponent
{
public:
	BaseRenderComponent()
	{
		SystemLocator::getSystem<RenderSystem>()->add(this);
	}

	virtual ~BaseRenderComponent() 
	{
		SystemLocator::getSystem<RenderSystem>()->remove(this);
	}

	virtual void render(sf::RenderTarget& renderTarget) = 0;
};

template<typename TComponent>
class RenderComponent : public Component<TComponent>, public BaseRenderComponent
{};
