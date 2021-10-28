#pragma once
#include "TransformComponent.hpp"

class MotionComponent final : public Component<MotionComponent>
{
private:
	TransformComponent* transform = nullptr;

public:

	sf::Vector2f velocity;
	float rotator = 0;

	void start() override
	{
		transform = gameObject->getComponent<TransformComponent>();
	}

	void update(const float deltaTime) override
	{
		transform->position += deltaTime * velocity;
		transform->rotation += deltaTime * rotator;
	}
};