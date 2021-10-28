#pragma once
#include "../core/GameObject.hpp"
#include "../core/GameObjectManager.hpp"

#include "../components/AnimatedSpriteComponent.hpp"
#include "../components/InputComponent.hpp"
#include "../components/TransformComponent.hpp"

#include "../objects/FireBall.hpp"

class Player final : public GameObject
{
private:
	TransformComponent* transform = nullptr;
	enum class Direction { Left, Right, Up, Down };

public:
	explicit Player(const sf::Vector2f& initPosition)
		: transform(this->addComponent<TransformComponent>())
	{
		transform->position = initPosition;

		auto* animation = this->addComponent<AnimatedSpriteComponent>("assets/hurray.png");
		animation->setFrameSize(sf::Vector2i(64, 64));
		animation->addFrame(sf::Vector2i(0, 0));
		animation->addFrame(sf::Vector2i(64, 0));
		animation->addFrame(sf::Vector2i(128, 0));

		auto* input = this->addComponent<InputComponent>();
		input->bind(sf::Keyboard::Left, [this] {
			this->castFireBall(Direction::Left);
		});
		input->bind(sf::Keyboard::Right, [this] {
			this->castFireBall(Direction::Right);
		});
		input->bind(sf::Keyboard::Down, [this] {
			this->castFireBall(Direction::Down);
		});
		input->bind(sf::Keyboard::Up, [this] {
			this->castFireBall(Direction::Up);
		});
	}

	void castFireBall(Direction dir) const
	{
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

		auto* objectsManager = GameObjectsManager::getInstance();
		objectsManager->addObject(new FireBall(transform->position, velocity));
	}
};