#pragma once
#include "../core/GameObject.hpp"
#include "../core/SceneManager.hpp"
#include "../core/GameObjectSystem.hpp"

#include "../systems/TurnSystem.hpp"
#include "../components/InputComponent.hpp"

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

		input->bind(sf::Keyboard::Num0, [this](const InputSystem::Type type) {
			this->setMyCircle(0);
		});
		input->bind(sf::Keyboard::Num1, [this](const InputSystem::Type type) {
			this->setMyCircle(1);
		});
		input->bind(sf::Keyboard::Num2, [this](const InputSystem::Type type) {
			this->setMyCircle(2);
		});
		input->bind(sf::Keyboard::Num3, [this](const InputSystem::Type type) {
			this->setMyCircle(3);
		});
		input->bind(sf::Keyboard::Num4, [this](const InputSystem::Type type) {
			this->setMyCircle(4);
		});
		input->bind(sf::Keyboard::Num5, [this](const InputSystem::Type type) {
			this->setMyCircle(5);
		});
		input->bind(sf::Keyboard::Num6, [this](const InputSystem::Type type) {
			this->setMyCircle(6);
		});
		input->bind(sf::Keyboard::Num7, [this](const InputSystem::Type type) {
			this->setMyCircle(7);
		});
		input->bind(sf::Keyboard::Num8, [this](const InputSystem::Type type) {
			this->setMyCircle(8);
		});
	}

	void setMyCircle(uint8_t cell)
	{
		auto* board = SystemLocator::getSystem<GameObjectSystem>()->getObjectById<Board>(this->boardId);
		const auto currentPlayer = SystemLocator::getSystem<TurnSystem>()->getPlayer();
		board->set(cell % 3, cell / 3, currentPlayer );
	}
};
