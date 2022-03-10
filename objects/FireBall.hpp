#pragma once
#include "../core/GameObject.hpp"
#include "../components/SpriteComponent.hpp"
#include "../components/TimerComponent.hpp"
#include "../physics/CirclePhysicsComponent.hpp"

class CirclePhysicsComponent;

class FireBall final : public GameObject
{
public:
	FireBall(const sf::Vector2f& initPosition, const sf::Vector2f& velocity)
	{
		auto* timer = this->addComponent<TimerComponent>();
		timer->setEndTime(sf::seconds(5).asMicroseconds());
		timer->setTrigger([this] {
			this->destroy();
		});

		auto* sprite = this->addComponent<SpriteComponent>("./assets/FireBall.png");
		sprite->setSize(32, 32);

		this->addComponent<TransformComponent>();

		/*auto* motion = this->addComponent<MotionComponent>();
		motion->velocity = velocity;
		motion->rotator = 0.75;*/

		const auto* physics = this->addComponent<CirclePhysicsComponent>(16.f, initPosition, b2_dynamicBody);
		physics->applyLinearImpulseToCenter(velocity);
		physics->applyTorque(0.75f);
	}
};
