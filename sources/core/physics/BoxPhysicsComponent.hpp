#pragma once
#include <SFML/System/Vector2.hpp>

#include "PhysicsComponent.hpp"
#include "PhysicsSystem.hpp"

class BoxPhysicsComponent final : public PhysicsComponent
{
private:
	sf::Vector2f size;
	b2Fixture* fixture = nullptr;
	
public:
	BoxPhysicsComponent(const sf::Vector2f size, const sf::Vector2f position, const b2BodyType bodyType)
		: size(size)
	{
		b2BodyDef bodyDef;
		bodyDef.position = PhysicsSystem::pixelsToMeters(position - size/2.f);
		bodyDef.type = bodyType;
		body = world->CreateBody(&bodyDef);

		b2PolygonShape shape;
		const auto m = PhysicsSystem::pixelsToMeters(size / 2.f);
		shape.SetAsBox(m.x, m.y);
		b2FixtureDef fixtureDef;
		fixtureDef.density = 1.f;
		fixtureDef.friction = 0.7f;
		fixtureDef.shape = &shape;
		//fixtureDef.userData.pointer = static_cast<uintptr_t>(this->gameObject->getId());
		fixture = body->CreateFixture(&fixtureDef);
	}

	~BoxPhysicsComponent() override
	{
		world->DestroyBody(body);
	}

	void start() override
	{
		fixture->GetUserData().pointer = static_cast<uintptr_t>(this->gameObject->getId());
		PhysicsComponent::start();
	}

	[[nodiscard]] sf::Vector2f getPosition() const override
	{
		return PhysicsSystem::metersToPixels(body->GetPosition()) - size/2.f;
	}

	void setPosition(const sf::Vector2f& position) const override
	{
		const auto angle = body->GetAngle();
		body->SetTransform(PhysicsSystem::pixelsToMeters(position - size/2.f), angle);
	}
	void setSize(const sf::Vector2f& size) const
	{
		const auto m_size = PhysicsSystem::pixelsToMeters(size / 2.f);
		b2Fixture* fixture = body->GetFixtureList();
		((b2PolygonShape*)fixture->GetShape())->SetAsBox(m_size.x, m_size.y);
	}

};
