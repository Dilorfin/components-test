#pragma once
#include "../systems/RenderSystem.hpp"
#include "../systems/TurnSystem.hpp"
#include "../objects/Board.hpp"

class BoardDisplayComponent final : public RenderComponent<BoardDisplayComponent>
{
private:
	Board* board = nullptr;

	sf::CircleShape red;
	sf::CircleShape blue;
	const float cell = 100;
	const float offset = 10;

public:
	BoardDisplayComponent()
	{
		constexpr float radius = 40;

		red.setRadius(radius);
		red.setFillColor(sf::Color::Red);

		blue.setRadius(radius);
		blue.setFillColor(sf::Color::Blue);
	}

	void start() override
	{
		board = (Board*)this->gameObject;
	}

	void render(sf::RenderTarget& renderTarget) override
	{
		for (uint8_t x = 0; x < 3; x++)
		{
			for (uint8_t y = 0; y < 3; y++)
			{
				sf::Vector2f position(x * cell + offset, y * cell + offset);
				if (board->get(x, y) == PlayerColors::Red)
				{
					red.setPosition(position);
					renderTarget.draw(red);
				}
				else if (board->get(x, y) == PlayerColors::Blue)
				{
					blue.setPosition(position);
					renderTarget.draw(blue);
				}
			}
		}
	}
};