#pragma once
#include "core/GameObject.hpp"

#include "../components/gui/GridGuiComponent.hpp"
#include "../components/gui/BottomInfoGuiComponent.hpp"

class Gui final : public GameObject
{
public:
	explicit Gui(const object_id boardId)
	{
		auto const* const board = SystemLocator::getSystem<GameObjectSystem>()->getObjectById<Board>(boardId);
		const auto boardRect = board->getRectangle();

		const auto windowSize = SystemLocator::getSystem<RenderSystem>()->getRenderTarget()->getSize();
		const auto bottomSize = sf::IntRect({ 0, boardRect.height }, sf::Vector2i(windowSize.x, windowSize.y - boardRect.height));

		this->addComponent<GridGuiComponent>(boardRect, sf::Vector2<uint8_t>(3, 3));
		this->addComponent<BottomInfoGuiComponent>(bottomSize);
	}
};
