#include "../GameObject.hpp"

GameObject::~GameObject()
{
	for (const auto* comp : components)
	{
		delete comp;
	}
}

void GameObject::start() const
{
	for (auto* comp : components)
	{
		comp->start();
	}
}

void GameObject::update(const int64_t deltaTime) const
{
	for (auto* comp : components)
	{
		comp->update(deltaTime);
	}
}
