#pragma once
#include <SFML/Graphics.hpp>
#include "../core/Component.hpp"
#include "../systems/RenderSystem.hpp"

class BaseRenderComponent
{
public:
	BaseRenderComponent()
	{
		SystemLocator::getInstance()->getSystem<RenderSystem>()->addItem(this);
	}

	virtual ~BaseRenderComponent() 
	{
		SystemLocator::getInstance()->getSystem<RenderSystem>()->removeItem(this);
	}

	virtual void render(sf::RenderTarget& renderTarget) = 0;
};

template<typename TComponent>
class RenderComponent : public Component<TComponent>, public BaseRenderComponent
{};
