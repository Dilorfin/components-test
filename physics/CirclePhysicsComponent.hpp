#pragma once
#include <SFML/System/Vector2.hpp>

#include "PhysicsComponent.hpp"
#include "PhysicsSystem.hpp"

class CirclePhysicsComponent final : public PhysicsComponent
{
private:
	b2Fixture* fixture = nullptr;
	
public:
	CirclePhysicsComponent(const float radius, const sf::Vector2f position, const b2BodyType bodyType)
	{
		b2BodyDef bodyDef;

		bodyDef.position = PhysicsSystem::pixelsToMeters(position);// - sf::Vector2f(radius, radius)/2.f);
		bodyDef.type = bodyType;
		body = world->CreateBody(&bodyDef);

		b2CircleShape shape;
		shape.m_radius = PhysicsSystem::pixelsToMeters(radius);
		b2FixtureDef fixtureDef;
		fixtureDef.density = 1.f;
		fixtureDef.friction = 0.7f;
		fixtureDef.shape = &shape;
		//fixtureDef.userData.pointer = static_cast<uintptr_t>(this->gameObject->getId());
		fixture = body->CreateFixture(&fixtureDef);
	}

	~CirclePhysicsComponent() override
	{
		world->DestroyBody(body);
	}

	void start() override
	{
		fixture->GetUserData().pointer = static_cast<uintptr_t>(this->gameObject->getId());
		PhysicsComponent::start();
	}

	[[nodiscard]] float getRadius() const
	{
		b2Fixture* fixture = body->GetFixtureList();
		return PhysicsSystem::metersToPixels(fixture->GetShape()->m_radius);
	}
	void setRadius(const float radius) const
	{
		b2Fixture* fixture = body->GetFixtureList();
		fixture->GetShape()->m_radius = PhysicsSystem::pixelsToMeters(radius);
	}

	[[nodiscard]] sf::Vector2f getPosition() const override
	{
		const sf::Vector2f position = PhysicsSystem::metersToPixels(body->GetPosition());
		//const float radius = getRadius();
		return position;// + sf::Vector2f(radius, radius);
	}
	void setPosition(const sf::Vector2f& position) const override
	{
		const float radius = getRadius();
		const auto tempPos = position;// - sf::Vector2f(radius, radius)/2.f;
		body->SetTransform(PhysicsSystem::pixelsToMeters(tempPos), body->GetAngle());
	}
};
