#include "PhysicsSystem.hpp"

#include "core/GameObject.hpp"
#include "core/systems/GameObjectSystem.hpp"

#ifdef _DEBUG
#include "PhysicsDebugDraw.hpp"
#include "../systems/RenderSystem.hpp"
#endif // _DEBUG

PhysicsComponent::PhysicsComponent()
{
	SystemLocator::getSystem<PhysicsSystem>()->registerComponent(this);
}

void PhysicsComponent::start()
{
	this->transform = gameObject->getComponent<TransformComponent>();
	this->update(0);
}

void PhysicsComponent::update(const int64_t deltaTime)
{
	transform->position = this->getPosition();
	transform->rotation = this->getAngle();
}

float PhysicsComponent::getAngle() const
{
	return body->GetAngle();
}

void PhysicsComponent::setAngle(const float angle) const
{
	body->SetTransform(body->GetPosition(), angle);
}

void PhysicsComponent::applyLinearImpulse(sf::Vector2f impulse, sf::Vector2f point) const
{
	body->ApplyLinearImpulse({ impulse.x, impulse.y }, { point.x, point.y }, true);
}

void PhysicsComponent::applyAngularImpulse(const float impulse) const
{
	body->ApplyAngularImpulse(impulse, true);
}

void PhysicsComponent::applyForce(sf::Vector2f force, sf::Vector2f point) const
{
	body->ApplyForce({ force.x, force.y }, { point.x, point.y }, true);
}

void PhysicsComponent::applyForceToCenter(sf::Vector2f force) const
{
	body->ApplyForceToCenter({ force.x, force.y }, true);
}

void PhysicsComponent::applyLinearImpulseToCenter(sf::Vector2f impulse) const
{
	body->ApplyLinearImpulseToCenter({ impulse.x, impulse.y }, true);
}

void PhysicsComponent::applyTorque(const float torque) const
{
	body->ApplyTorque(torque, true);
}

void PhysicsComponent::setBeginContactTrigger(const std::function<void(PhysicsComponent*)>& func)
{
	beginContactTrigger = func;
}

void PhysicsComponent::setEndContactTrigger(const std::function<void(PhysicsComponent*)>& func)
{
	endContactTrigger = func;
}

void PhysicsComponent::beginContact(PhysicsComponent* another) const
{
	if (beginContactTrigger.has_value())
	{
		beginContactTrigger.value()(another);
	}
}

void PhysicsComponent::endContact(PhysicsComponent* another) const
{
	if (endContactTrigger.has_value())
	{
		endContactTrigger.value()(another);
	}
}

PhysicsSystem::PhysicsSystem()
	: world(new b2World(gravity))
{
	world->SetContactListener(this);
}

PhysicsSystem::~PhysicsSystem()
{
	delete world;
}

#ifdef _DEBUG
void PhysicsSystem::enableDebugDraw()
{
	this->_draw = new PhysicsDebugDraw(SystemLocator::getSystem<RenderSystem>()->getRenderTarget());
	this->_draw->AppendFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);
	world->SetDebugDraw(_draw);
}

void PhysicsSystem::debugDraw() const
{
	world->DebugDraw();
}
#endif

void PhysicsSystem::registerComponent(PhysicsComponent* comp) const
{
	comp->world = this->world;
}

void PhysicsSystem::update(int64_t dt) const
{
	world->Step(fixedTimeStep, velocityIterations, positionIterations);
}

float PhysicsSystem::pixelsToMeters(const float px)
{
	return px / PX_IN_METER;
}

b2Vec2 PhysicsSystem::pixelsToMeters(const sf::Vector2f& px)
{
	return {
		pixelsToMeters(px.x),
		pixelsToMeters(px.y)
	};
}

float PhysicsSystem::metersToPixels(const float meters)
{
	return meters * PX_IN_METER;
}

sf::Vector2f PhysicsSystem::metersToPixels(const b2Vec2& meters)
{
	return {
		metersToPixels(meters.x),
		metersToPixels(meters.y)
	};
}

void PhysicsSystem::BeginContact(b2Contact* contact)
{
	const auto userDataA = contact->GetFixtureA()->GetUserData();
	const auto userDataB = contact->GetFixtureB()->GetUserData();

	auto* gameObjectA = SystemLocator::getSystem<GameObjectSystem>()->getObjectById((uint32_t)userDataA.pointer);
	auto* gameObjectB = SystemLocator::getSystem<GameObjectSystem>()->getObjectById((uint32_t)userDataB.pointer);

	if(!gameObjectA || !gameObjectB)
		return;

	auto* compA = gameObjectA->getComponent<PhysicsComponent>();
	auto* compB = gameObjectB->getComponent<PhysicsComponent>();

	if(!compA || !compB)
		return;

	compA->beginContact(compB);
	compB->beginContact(compA);
}

void PhysicsSystem::EndContact(b2Contact* contact)
{
	const auto userDataA = contact->GetFixtureA()->GetUserData();
	const auto userDataB = contact->GetFixtureB()->GetUserData();

	auto* gameObjectA = SystemLocator::getSystem<GameObjectSystem>()->getObjectById((uint32_t)userDataA.pointer);
	auto* gameObjectB = SystemLocator::getSystem<GameObjectSystem>()->getObjectById((uint32_t)userDataB.pointer);

	if(!gameObjectA || !gameObjectB)
		return;

	auto* compA = gameObjectA->getComponent<PhysicsComponent>();
	auto* compB = gameObjectB->getComponent<PhysicsComponent>();

	if(!compA || !compB)
		return;

	compA->endContact(compB);
	compB->endContact(compA);
}

void PhysicsSystem::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{}

void PhysicsSystem::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{}
