#pragma once
#include <cassert>
#include <SFML/Graphics.hpp>

#include "core/SystemLocator.hpp"
#include "core/components/RenderComponent.hpp"

#include "../../systems/TurnSystem.hpp"

class BottomInfoGuiComponent final : public RenderComponent<BottomInfoGuiComponent>
{
private:
	sf::CircleShape circle;
	sf::Font font;
	sf::Font font2;
	sf::Text text;

public:
	explicit BottomInfoGuiComponent(const sf::IntRect rect)
		: text("Current player:", font, 15)
	{
		const auto loaded = font.loadFromFile("assets/tuffy.ttf");
		assert(loaded);

		const auto textPositionY = rect.top + rect.height/2.f - text.getLocalBounds().height/2.f;
		text.setPosition({0, textPositionY});

		circle.setRadius(12);
		const auto circlePositionY = rect.top + rect.height/2.f - circle.getRadius();
		circle.setPosition(sf::Vector2f(rect.left + text.getLocalBounds().width, circlePositionY));
	}

	void render(sf::RenderTarget& renderTarget) override
	{
		const auto player = SystemLocator::getSystem<TurnSystem>()->getPlayer();
		assert(player != PlayerColors::None);

		if (player == PlayerColors::Red)
		{
			circle.setFillColor(sf::Color::Red);
		}
		else
		{
			circle.setFillColor(sf::Color::Blue);
		}

		renderTarget.draw(circle);
		renderTarget.draw(text);
	}
};
