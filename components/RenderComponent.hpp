#pragma once
#include <SFML/Graphics.hpp>

class RenderComponent
{
public:
	RenderComponent();
	virtual ~RenderComponent();

	virtual void render(sf::RenderTarget& renderTarget) = 0;
};
