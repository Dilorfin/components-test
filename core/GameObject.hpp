#pragma once

#include <list>

#include "Component.hpp"

typedef uint32_t object_id;

class GameObjectsManager;

class GameObject
{
private:
	friend GameObjectsManager;
	object_id id;

	std::list<BaseComponent*> components;
	bool _isDestroyed = false;
public:
	virtual ~GameObject();

	template<typename TComponent>
	TComponent* getComponent()
	{
		const auto id = typeid(TComponent).hash_code();
		for (auto* comp : components)
		{
			if (comp->hash_code() == id)
			{
				return (TComponent*)comp;
			}
		}
		return nullptr;
	}

	template<typename TComponent, typename... Ts>
	TComponent* addComponent(Ts&&... args)
	{
		auto* component = new TComponent(std::forward<Ts>(args)...);
		component->gameObject = this;
		components.push_back(component);
		return component;
	}

	[[nodiscard]] object_id getId() const
	{
		return id;
	}

	void start() const;
	void update(const int64_t deltaTime) const;

	void destroy()
	{
		_isDestroyed = true;
	}
	[[nodiscard]] bool isDestroyed() const
	{
		return _isDestroyed;
	}
};
