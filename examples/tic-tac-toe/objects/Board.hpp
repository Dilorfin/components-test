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
	}

	[[nodiscard]] PlayerColors get(uint8_t x, uint8_t y) const
	{
		return board[x][y];
	}
	void set(uint8_t x, uint8_t y, PlayerColors value)
	{
		if(board[x][y] != PlayerColors::None)
			return;

		board[x][y] = value;
		SystemLocator::getSystem<TurnSystem>()->turn();
	}
};

#include "../components/BoardDisplayComponent.hpp"
