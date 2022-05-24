#pragma once
#include "core/GameObject.hpp"
#include "core/components/AnimatedSpriteComponent.hpp"
#include "core/physics/BoxPhysicsComponent.hpp"

class Dummy final : public GameObject
{
public:
	explicit Dummy(const sf::Vector2f& initPosition)
	{
		auto* sprite = this->addComponent<AnimatedSpriteComponent>("./assets/bat.png");
		sprite->setFrameSize({ 64, 64 });
		sprite->addFrame({ 0, 0 });
		sprite->addFrame({ 0, 64 });

		this->addComponent<TransformComponent>();
		auto* phComp = this->addComponent<BoxPhysicsComponent>(sf::Vector2f(64, 64), initPosition, b2_dynamicBody);
		phComp->setBeginContactTrigger([](PhysicsComponent* comp) {
			std::cout << "begin contact" << std::endl;
		});
		phComp->setEndContactTrigger([](PhysicsComponent* comp) {
			std::cout << "end contact" << std::endl;
		});
	}
};
