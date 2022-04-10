#pragma once
#include <cstdint>

#include "../core/System.hpp"

enum class PlayerColors { None, Red, Blue };

class TurnSystem : public System<TurnSystem>
{
private:
	uint8_t _turn = 0;

public:
	[[nodiscard]] PlayerColors getPlayer() const
	{
		return _turn%2 ? PlayerColors::Red : PlayerColors::Blue;
	}

	[[nodiscard]] uint8_t getTurn() const
	{
		return _turn;
	}

	void turn() 
	{
		_turn++;
	}
};
