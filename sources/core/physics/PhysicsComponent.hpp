#pragma once
#include <functional>
#include <optional>

#include <box2d/box2d.h>

#include "core/Component.hpp"
#include "core/components/TransformComponent.hpp"

class PhysicsSystem;

class PhysicsComponent : public Component<PhysicsComponent>
{
private:
	friend PhysicsSystem;

	std::optional<std::function<void(PhysicsComponent*)>> beginContactTrigger;
	std::optional<std::function<void(PhysicsComponent*)>> endContactTrigger;

protected:
	TransformComponent* transform = nullptr;
	b2World* world = nullptr;
	b2Body* body = nullptr;

public:
	explicit PhysicsComponent();

	void start() override;
	void update(const int64_t deltaTime) override;

	[[nodiscard]] virtual sf::Vector2f getPosition() const = 0;
	virtual void setPosition(const sf::Vector2f& position) const = 0;

	[[nodiscard]] float getAngle() const;
	void setAngle(float angle) const;

	void applyLinearImpulse(sf::Vector2f impulse, sf::Vector2f point) const;
	void applyAngularImpulse(const float impulse) const;
	void applyForce(sf::Vector2f force, sf::Vector2f point) const;
	void applyForceToCenter(sf::Vector2f force) const;
	void applyLinearImpulseToCenter(sf::Vector2f impulse) const;
	void applyTorque(const float torque) const;
	void setBeginContactTrigger(const std::function<void(PhysicsComponent*)>& func);
	void setEndContactTrigger(const std::function<void(PhysicsComponent*)>& func);

private:
	void beginContact(PhysicsComponent* another) const;
	void endContact(PhysicsComponent* another) const;
};
