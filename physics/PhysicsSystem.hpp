#pragma once
#include <box2d/box2d.h>
#include <SFML/System/Vector2.hpp>

#include "../core/SystemLocator.hpp"

class PhysicsComponent;

class PhysicsSystem final : public System<PhysicsSystem>, public b2ContactListener
{
private:
	static constexpr float PX_IN_METER = 30.f;
	const float fixedTimeStep = 1.0f / 60.0f;
	const int32 velocityIterations = 6;
	const int32 positionIterations = 2;
	const b2Vec2 gravity{ 0, 0 };

#ifdef _DEBUG
	b2Draw* _draw = nullptr;
#endif // _DEBUG

public:
	b2World* world = nullptr;
	PhysicsSystem(PhysicsSystem&&) = delete;
	PhysicsSystem(const PhysicsSystem&) = delete;
	auto operator=(PhysicsSystem&&) = delete;
	auto operator=(const PhysicsSystem&) = delete;

	PhysicsSystem();
	~PhysicsSystem() override;

#ifdef _DEBUG
	void enableDebugDraw();
	void debugDraw() const;
#endif

	void registerComponent(PhysicsComponent* comp) const;
	void update(int64_t dt) const;

	[[nodiscard]] static float pixelsToMeters(const float px);
	[[nodiscard]] static b2Vec2 pixelsToMeters(const sf::Vector2f& px);
	[[nodiscard]] static float metersToPixels(const float meters);
	[[nodiscard]] static sf::Vector2f metersToPixels(const b2Vec2& meters);

	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
};

#include "PhysicsComponent.hpp"