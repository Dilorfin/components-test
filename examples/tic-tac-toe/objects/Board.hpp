#pragma once
#include "core/GameObject.hpp"
#include "core/SystemLocator.hpp"

#include "../systems/TurnSystem.hpp"

class BoardDisplayComponent;

class Board : public GameObject
{
private:
	PlayerColors board[3][3]{};

public:
	Board()
	{
		this->addComponent<BoardDisplayComponent>();
		for (uint8_t x = 0; x < 3; x++)
		{
			for (uint8_t y = 0; y < 3; y++)
			{
				board[x][y] = PlayerColors::None;
			}
		}
	}

	[[nodiscard]] PlayerColors get(uint8_t x, uint8_t y) const
	{
		return board[x][y];
	}
	void set(uint8_t x, uint8_t y, PlayerColors value)
	{
		assert(x < 3);
		assert(y < 3);

		if(board[x][y] != PlayerColors::None)
			return;

		board[x][y] = value;
		SystemLocator::getSystem<TurnSystem>()->turn();
	}

	[[nodiscard]] sf::IntRect getRectangle() const
	{
		const auto windowSize = SystemLocator::getSystem<RenderSystem>()->getRenderTarget()->getSize();
		return {
			{0, 0},
			sf::Vector2i(windowSize.x, windowSize.x)
		};
	}
};

#include "../components/BoardDisplayComponent.hpp"
