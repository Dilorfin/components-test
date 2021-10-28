#pragma once

#include <vector>
#include "Component.hpp"

class GameObject
{
private:
	std::vector<BaseComponent*> components;

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

	void addComponent(BaseComponent * component)
	{
		component->gameObject = this;
		components.push_back(component);
	}

	template<typename TComponent, typename... Ts>
	TComponent* addComponent(Ts&&... args)
	{
		auto* component = new TComponent(std::forward<Ts>(args)...);
		component->gameObject = this;
		components.push_back(component);
		return component;
	}

	void start() const;

	void update(const float deltaTime) const;
};
