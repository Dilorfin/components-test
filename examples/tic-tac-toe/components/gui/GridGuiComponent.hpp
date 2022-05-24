#pragma once
#include <cassert>
#include <SFML/Graphics.hpp>

#include "core/SystemLocator.hpp"
#include "core/components/RenderComponent.hpp"

class GridGuiComponent final : public RenderComponent<GridGuiComponent>
{
private:
	const sf::IntRect rect;
	const sf::Vector2<uint8_t> parts;

	sf::RenderTexture texture;
	sf::Sprite sprite;

public:
	explicit GridGuiComponent(const sf::IntRect rect, const sf::Vector2<uint8_t> parts)
		: rect(rect), parts(parts)
	{
		assert(parts.x > 0);
		assert(parts.y > 0);

		constexpr float lineWidth = 2;
		sf::RectangleShape line;
		line.setFillColor(sf::Color::White);

		const auto created = texture.create(sf::Vector2u(rect.width, rect.height), sf::ContextSettings(0, 0,
												sf::RenderTexture::getMaximumAntialiasingLevel()));
		assert(created);

		const float offsetX = rect.width / parts.x;
		const float offsetY = rect.height / parts.y;

		line.setSize(sf::Vector2f(lineWidth, (float)rect.height));
		for (int i = 0; i < parts.x+1; i++)
		{
			line.setPosition(sf::Vector2f(offsetX * i - lineWidth/2, 0));
			texture.draw(line);
		}
		
		line.setSize(sf::Vector2f((float)rect.width, lineWidth));
		for (int i = 0; i < parts.x+1; i++)
		{
			line.setPosition(sf::Vector2f(0, offsetY * i - lineWidth/2));
			texture.draw(line);
		}
		texture.display();
		sprite.setTexture(texture.getTexture());
	}

	void render(sf::RenderTarget& renderTarget) override
	{
		renderTarget.draw(sprite);
	}
};