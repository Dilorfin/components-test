#include "box2dSystem.hpp"

#include "../core/GameObject.hpp"
#include "../core/GameObjectManager.hpp"

B2Component::B2Component()
{
	SystemLocator::getSystem<Box2dSystem>()->registerComponent(this);
}

void B2Component::start()
{
	this->transform = gameObject->getComponent<TransformComponent>();
}

void B2Component::update(const int64_t deltaTime)
{
	transform->position = this->getPosition();
	transform->rotation = this->getAngle();
}

float B2Component::getAngle() const
{
	return body->GetAngle();
}

void B2Component::setAngle(const float angle) const
{
	body->SetTransform(body->GetPosition(), angle);
}

void B2Component::applyLinearImpulse(sf::Vector2f impulse, sf::Vector2f point) const
{
	body->ApplyLinearImpulse({ impulse.x, impulse.y }, { point.x, point.y }, true);
}

void B2Component::applyAngularImpulse(const float impulse) const
{
	body->ApplyAngularImpulse(impulse, true);
}

void B2Component::applyForce(sf::Vector2f force, sf::Vector2f point) const
{
	body->ApplyForce({ force.x, force.y }, { point.x, point.y }, true);
}

void B2Component::applyForceToCenter(sf::Vector2f force) const
{
	body->ApplyForceToCenter({ force.x, force.y }, true);
}

void B2Component::applyLinearImpulseToCenter(sf::Vector2f impulse) const
{
	body->ApplyLinearImpulseToCenter({ impulse.x, impulse.y }, true);
}

void B2Component::applyTorque(const float torque) const
{
	body->ApplyTorque(torque, true);
}

void B2Component::setBeginContactTrigger(const std::function<void(B2Component*)>& func)
{
	beginContactTrigger = func;
}

void B2Component::setEndContactTrigger(const std::function<void(B2Component*)>& func)
{
	endContactTrigger = func;
}

size_t B2Component::hash_code() const
{
	return typeid(B2Component).hash_code();
}

void B2Component::beginContact(B2Component* another) const
{
	if (beginContactTrigger.has_value())
	{
		beginContactTrigger.value()(another);
	}
}

void B2Component::endContact(B2Component* another) const
{
	if (endContactTrigger.has_value())
	{
		endContactTrigger.value()(another);
	}
}

Box2dSystem::Box2dSystem()
	: world(new b2World(gravity))
{
	world->SetContactListener(this);
}

Box2dSystem::~Box2dSystem()
{
	delete world;
}

#ifdef _DEBUG
void Box2dSystem::setDebugDraw(b2Draw* draw) const
{
	world->SetDebugDraw(draw);
}

void Box2dSystem::debugDraw() const
{
	world->DebugDraw();
}
#endif

void Box2dSystem::registerComponent(B2Component* comp) const
{
	comp->world = this->world;
}

void Box2dSystem::update(int64_t dt) const
{
	world->Step(fixedTimeStep, velocityIterations, positionIterations);
}

float Box2dSystem::pixelsToMeters(const float px)
{
	return px / PX_IN_METER;
}

b2Vec2 Box2dSystem::pixelsToMeters(const sf::Vector2f& px)
{
	return {
		pixelsToMeters(px.x),
		pixelsToMeters(px.y)
	};
}

float Box2dSystem::metersToPixels(const float meters)
{
	return meters * PX_IN_METER;
}

sf::Vector2f Box2dSystem::metersToPixels(const b2Vec2& meters)
{
	return {
		metersToPixels(meters.x),
		metersToPixels(meters.y)
	};
}

void Box2dSystem::BeginContact(b2Contact* contact)
{
	const auto userDataA = contact->GetFixtureA()->GetUserData();
	const auto userDataB = contact->GetFixtureB()->GetUserData();

	auto* gameObjectA = SystemLocator::getSystem<GameObjectsManager>()->getObjectById((uint32_t)userDataA.pointer);
	auto* gameObjectB = SystemLocator::getSystem<GameObjectsManager>()->getObjectById((uint32_t)userDataB.pointer);

	if(!gameObjectA || !gameObjectB)
		return;

	auto* compA = gameObjectA->getComponent<B2Component>();
	auto* compB = gameObjectB->getComponent<B2Component>();

	if(!compA || !compB)
		return;

	compA->beginContact(compB);
	compB->beginContact(compA);
}

void Box2dSystem::EndContact(b2Contact* contact)
{
	const auto userDataA = contact->GetFixtureA()->GetUserData();
	const auto userDataB = contact->GetFixtureB()->GetUserData();

	auto* gameObjectA = SystemLocator::getSystem<GameObjectsManager>()->getObjectById((uint32_t)userDataA.pointer);
	auto* gameObjectB = SystemLocator::getSystem<GameObjectsManager>()->getObjectById((uint32_t)userDataB.pointer);

	if(!gameObjectA || !gameObjectB)
		return;

	auto* compA = gameObjectA->getComponent<B2Component>();
	auto* compB = gameObjectB->getComponent<B2Component>();

	if(!compA || !compB)
		return;

	compA->endContact(compB);
	compB->endContact(compA);
}

void Box2dSystem::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{}

void Box2dSystem::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{}
