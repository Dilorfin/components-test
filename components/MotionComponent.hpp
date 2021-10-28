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

	void update(const int64_t deltaTime) override
	{
		transform->position += deltaTime * 0.00125f * velocity;
		transform->rotation += deltaTime * 0.00125f * rotator ;
	}
};