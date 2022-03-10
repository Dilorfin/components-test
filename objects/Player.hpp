#pragma once
#include "../core/GameObject.hpp"
#include "../core/SceneSystem.hpp"
#include "../core/GameObjectSystem.hpp"

#include "../components/AnimatedSpriteComponent.hpp"
#include "../components/InputComponent.hpp"
#include "../components/TransformComponent.hpp"
#include "../components/MotionComponent.hpp"

#include "FireBall.hpp"

class Player final : public GameObject
{
private:
	enum class Direction { Left, Right, Up, Down };

	TransformComponent* transform = nullptr;
	MotionComponent* motion = nullptr;

	float speed = 0.4f;

public:
	explicit Player(const sf::Vector2f& initPosition)
		: transform(this->addComponent<TransformComponent>()),
		  motion(this->addComponent<MotionComponent>())
	{
		transform->position = initPosition;

		auto* animation = this->addComponent<AnimatedSpriteComponent>("assets/hurray.png");
		animation->setFrameSize(sf::Vector2i(64, 64));
		animation->addFrame(sf::Vector2i(0, 0));
		animation->addFrame(sf::Vector2i(64, 0));
		animation->addFrame(sf::Vector2i(128, 0));

		auto* input = this->addComponent<InputComponent>();
		input->bind(sf::Keyboard::Left, [this](const InputSystem::Type type) {
			this->castFireBall(type, Direction::Left);
		});
		input->bind(sf::Keyboard::Right, [this](const InputSystem::Type type) {
			this->castFireBall(type, Direction::Right);
		});
		input->bind(sf::Keyboard::Down, [this](const InputSystem::Type type) {
			this->castFireBall(type, Direction::Down);
		});
		input->bind(sf::Keyboard::Up, [this](const InputSystem::Type type) {
			this->castFireBall(type, Direction::Up);
		});

		input->bind(sf::Keyboard::W, [this](const InputSystem::Type type) {
			this->motion->velocity.y = type == InputSystem::Type::Pressed ? -speed : 0;
		});
		input->bind(sf::Keyboard::S, [this](const InputSystem::Type type) {
			this->motion->velocity.y = type == InputSystem::Type::Pressed ? speed  : 0;
		});
		input->bind(sf::Keyboard::D, [this](const InputSystem::Type type) {
			this->motion->velocity.x = type == InputSystem::Type::Pressed ? speed  : 0;
		});
		input->bind(sf::Keyboard::A, [this](const InputSystem::Type type) {
			this->motion->velocity.x = type == InputSystem::Type::Pressed ? -speed : 0;
		});

		input->bind(sf::Keyboard::F, [this](const InputSystem::Type type) {
			SceneManager::getInstance()->openScene();
		});
	}

	void castFireBall(const InputSystem::Type type, const Direction dir) const
	{
		if(type != InputSystem::Type::Pressed) return;

		sf::Vector2f velocity;
		switch (dir)
		{
		case Direction::Left:
			velocity = sf::Vector2f(-0.5, 0);
			break;
		case Direction::Right:
			velocity = sf::Vector2f(0.5, 0);
			break;
		case Direction::Up:
			velocity = sf::Vector2f(0, -0.5);
			break;
		case Direction::Down:
			velocity = sf::Vector2f(0, 0.5);
			break;
		}

		const auto system = SystemLocator::getInstance()->getSystem<GameObjectsManager>();
		system->add(new FireBall(transform->position, velocity));
	}
};