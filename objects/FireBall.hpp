#pragma once
#include "../core/GameObject.hpp"
#include "../components/SpriteComponent.hpp"
#include "../components/MotionComponent.hpp"

class FireBall final : public GameObject
{
public:
	explicit FireBall(const sf::Vector2f& initPosition, const sf::Vector2f& velocity)
	{
		auto* sprite  = this->addComponent<SpriteComponent>("./assets/FireBall.png");
		sprite->setSize(32, 32);

		auto* transform = this->addComponent<TransformComponent>();
		transform->position = initPosition;

		auto* motion = this->addComponent<MotionComponent>();
		motion->velocity = velocity;
		motion->rotator = 0.75;
	}
};