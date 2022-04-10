#pragma once
#include "core/GameObject.hpp"
#include "core/SceneManager.hpp"
#include "core/systems/GameObjectSystem.hpp"
#include "core/components/InputComponent.hpp"

#include "../systems/TurnSystem.hpp"
#include "../objects/Board.hpp"

class Player final : public GameObject
{
private:
	object_id boardId;

public:
	explicit Player(const object_id boardId)
		: boardId(boardId)
	{
		auto* input = this->addComponent<InputComponent>();
		input->bind(sf::Keyboard::R, [this](const InputSystem::Type type) {
			SceneManager::getInstance()->reloadScene();
		});

		input->bind(sf::Keyboard::Numpad1, [this](const InputSystem::Type type) {
			this->setMyCircle(0, 2);
		});
		input->bind(sf::Keyboard::Numpad2, [this](const InputSystem::Type type) {
			this->setMyCircle(1, 2);
		});
		input->bind(sf::Keyboard::Numpad3, [this](const InputSystem::Type type) {
			this->setMyCircle(2, 2);
		});
		input->bind(sf::Keyboard::Numpad4, [this](const InputSystem::Type type) {
			this->setMyCircle(0, 1);
		});
		input->bind(sf::Keyboard::Numpad5, [this](const InputSystem::Type type) {
			this->setMyCircle(1, 1);
		});
		input->bind(sf::Keyboard::Numpad6, [this](const InputSystem::Type type) {
			this->setMyCircle(2, 1);
		});
		input->bind(sf::Keyboard::Numpad7, [this](const InputSystem::Type type) {
			this->setMyCircle(0, 0);
		});
		input->bind(sf::Keyboard::Numpad8, [this](const InputSystem::Type type) {
			this->setMyCircle(1, 0);
		});
		input->bind(sf::Keyboard::Numpad9, [this](const InputSystem::Type type) {
			this->setMyCircle(2, 0);
		});
	}

	void setMyCircle(uint8_t x, uint8_t y) const
	{
		auto* board = SystemLocator::getSystem<GameObjectSystem>()->getObjectById<Board>(this->boardId);
		const auto currentPlayer = SystemLocator::getSystem<TurnSystem>()->getPlayer();
		board->set(x, y, currentPlayer);
	}
};
