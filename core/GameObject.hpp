#pragma once

#include <list>

#include "Component.hpp"

class GameObject : public Destroyable
{
private:
	std::list<BaseComponent*> components;
public:
	virtual ~GameObject()
	{
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
		auto* component = new TComponent(std::forward<Ts>(args)...);
		component->gameObject = this;
		components.push_back(component);
		return component;
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
