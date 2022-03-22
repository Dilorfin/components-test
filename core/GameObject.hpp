#pragma once

#include <list>

#include "Component.hpp"
#include "../physics/PhysicsComponent.hpp"

typedef uint32_t object_id;

class GameObjectsManager;

class GameObject : public Destroyable
{
private:
	friend GameObjectsManager;
	object_id id = 0;

	std::list<BaseComponent*> components;
	
public:

	virtual ~GameObject()
	{
		auto * ph = this->getComponent<PhysicsComponent>();
		components.erase(std::remove(std::begin(components), std::end(components), ph), std::end(components));
		delete ph;

		for (const auto* comp : components)
		{
			delete comp;
		}
	}

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
		assert(this->getComponent<TComponent>() == nullptr);

		auto* component = new TComponent(std::forward<Ts>(args)...);
		component->gameObject = this;

		components.push_back(component);
		return component;
	}

	[[nodiscard]] object_id getId() const
	{
		return id;
	}

	void start() const
	{
		for (auto* comp : components)
		{
			comp->start();
		}
	}

	void update(const int64_t deltaTime)
	{
		auto it = components.begin();
		while (it != components.end())
		{
			auto* comp = *it;
			comp->update(deltaTime);

			if (comp->isDestroyed())
			{
				it = components.erase(it);
				delete comp;
			}
			else ++it;
		}
	}
};
