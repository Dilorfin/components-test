#pragma once
#include <list>
#include <box2d/box2d.h>
#include <SFML/System/Vector2.hpp>

#include "../core/SystemLocator.hpp"

class B2Component;

class Box2dSystem final : public System<Box2dSystem>, public b2ContactListener
{
private:
	static constexpr float PX_IN_METER = 30.f;
	const float fixedTimeStep = 1.0f / 60.0f;
	const int32 velocityIterations = 6;
	const int32 positionIterations = 2;
	const b2Vec2 gravity{ 0, 0 };

public:
	b2World* world = nullptr;
	Box2dSystem(Box2dSystem&&) = delete;
	Box2dSystem(const Box2dSystem&) = delete;
	auto operator=(Box2dSystem&&) = delete;
	auto operator=(const Box2dSystem&) = delete;

	Box2dSystem();
	~Box2dSystem() override;

#ifdef _DEBUG
	void setDebugDraw(b2Draw* draw) const;
	void debugDraw() const;
#endif

	void registerComponent(B2Component* comp) const;
	void update(int64_t dt);

	[[nodiscard]] static float pixelsToMeters(const float px);
	[[nodiscard]] static b2Vec2 pixelsToMeters(const sf::Vector2f& px);
	[[nodiscard]] static float metersToPixels(const float meters);
	[[nodiscard]] static sf::Vector2f metersToPixels(const b2Vec2& meters);

	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
};

#include "box2dComponent.hpp"