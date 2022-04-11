#pragma once
#include "core/SystemLocator.hpp"
#include "core/SceneManager.hpp"

#include "../objects/Player.hpp"
#include "../objects/Board.hpp"
#include "../objects/Gui.hpp"

class GameScene final : Scene
{
public:
	GameScene()
	{
		const auto boardId = SystemLocator::getSystem<GameObjectSystem>()->add(new Board);
		SystemLocator::getSystem<GameObjectSystem>()->add(new Player(boardId));
		SystemLocator::getSystem<GameObjectSystem>()->add(new Gui(boardId));
	}
};
