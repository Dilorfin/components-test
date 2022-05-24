#pragma once
#include "Destroyable.hpp"

class PhysicsComponent;
template<typename TComponent>
constexpr size_t hash()
{
	if constexpr (std::is_base_of<PhysicsComponent, TComponent>())
	{
		return 0;
	}
	else return typeid(TComponent).hash_code();
}

class GameObject;

class BaseComponent : public Destroyable
{
protected:
	GameObject* gameObject = nullptr;
	friend class GameObject;

public:
	virtual ~BaseComponent() = default;

	virtual void start() {}
	virtual void update(const int64_t deltaTime) {}

	[[nodiscard]] virtual size_t hash_code() const = 0;
};

template<typename TComponent>
class Component : public BaseComponent
{
public:
	[[nodiscard]] size_t hash_code() const final
	{
		return hash<TComponent>();
	}
};
