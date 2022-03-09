#pragma once
#include <SFML/System/Vector2.hpp>

#include "box2dComponent.hpp"
#include "box2dSystem.hpp"

class CirclePhysicsComponent final : public B2Component
{
public:
	CirclePhysicsComponent(const float radius, const sf::Vector2f position, const b2BodyType bodyType)
	{
		b2BodyDef bodyDef;

		bodyDef.position = Box2dSystem::pixelsToMeters(position);// - sf::Vector2f(radius, radius)/2.f);
		bodyDef.type = bodyType;
		body = world->CreateBody(&bodyDef);

		b2CircleShape shape;
		shape.m_radius = Box2dSystem::pixelsToMeters(radius);
		b2FixtureDef fixtureDef;
		fixtureDef.density = 1.f;
		fixtureDef.friction = 0.7f;
		fixtureDef.shape = &shape;
		fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
		body->CreateFixture(&fixtureDef);
	}

	~CirclePhysicsComponent() override
	{
		world->DestroyBody(body);
	}

	[[nodiscard]] float getRadius() const
	{
		b2Fixture* fixture = body->GetFixtureList();
		return Box2dSystem::metersToPixels(fixture->GetShape()->m_radius);
	}
	void setRadius(const float radius) const
	{
		b2Fixture* fixture = body->GetFixtureList();
		fixture->GetShape()->m_radius = Box2dSystem::pixelsToMeters(radius);
	}

	[[nodiscard]] sf::Vector2f getPosition() const override
	{
		const sf::Vector2f position = Box2dSystem::metersToPixels(body->GetPosition());
		//const float radius = getRadius();
		return position;// + sf::Vector2f(radius, radius);
	}
	void setPosition(const sf::Vector2f& position) const override
	{
		const float radius = getRadius();
		const auto tempPos = position;// - sf::Vector2f(radius, radius)/2.f;
		body->SetTransform(Box2dSystem::pixelsToMeters(tempPos), body->GetAngle());
	}
};
