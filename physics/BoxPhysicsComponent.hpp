#pragma once
#include <SFML/System/Vector2.hpp>

#include "box2dComponent.hpp"
#include "box2dSystem.hpp"

class BoxPhysicsComponent final : public B2Component
{
private:
	sf::Vector2f size;
	b2Fixture* fixture = nullptr;
public:
	BoxPhysicsComponent(const sf::Vector2f size, const sf::Vector2f position, const b2BodyType bodyType)
		: size(size)
	{
		b2BodyDef bodyDef;
		bodyDef.position = Box2dSystem::pixelsToMeters(position - size/2.f);
		bodyDef.type = bodyType;
		body = world->CreateBody(&bodyDef);

		b2PolygonShape shape;
		const auto m = Box2dSystem::pixelsToMeters(size / 2.f);
		shape.SetAsBox(m.x, m.y);
		b2FixtureDef fixtureDef;
		fixtureDef.density = 1.f;
		fixtureDef.friction = 0.7f;
		fixtureDef.shape = &shape;
		fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
		fixture = body->CreateFixture(&fixtureDef);
	}

	void update(const int64_t deltaTime) override
	{
		B2Component::update(deltaTime);
		fixture->GetUserData().pointer = (uintptr_t)this;
	}

	[[nodiscard]] sf::Vector2f getPosition() const override
	{
		return Box2dSystem::metersToPixels(body->GetPosition()) - size/2.f;
	}

	void setPosition(const sf::Vector2f& position) const override
	{
		const auto angle = body->GetAngle();
		body->SetTransform(Box2dSystem::pixelsToMeters(position - size/2.f), angle);
	}
	void setSize(const sf::Vector2f& size) const
	{
		const auto m_size = Box2dSystem::pixelsToMeters(size / 2.f);
		b2Fixture* fixture = body->GetFixtureList();
		((b2PolygonShape*)fixture->GetShape())->SetAsBox(m_size.x, m_size.y);
	}

	~BoxPhysicsComponent() override
	{
		world->DestroyBody(body);
	}
};
