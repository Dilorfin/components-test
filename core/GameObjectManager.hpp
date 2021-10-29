#pragma once
#include <list>

#include "GameObject.hpp"
#include "SystemLocator.hpp"

class GameObjectsManager final : public System<GameObjectsManager>
{
private:
	std::list<GameObject*> objects;

public:
	~GameObjectsManager() override
	{
		for (const auto* obj : objects)
		{
			delete obj;
		}
	}

	void addObject(GameObject* object)
	{
		objects.push_back(object);
		object->start();
	}

	static void removeObject(GameObject* object)
	{
		object->destroy();
	}

	void update(const float deltaTime)
	{
		auto it = objects.begin();
		while (it != objects.end())
		{
			auto* obj = *it;
			obj->update(deltaTime);

			if (obj->isDestroyed())
			{
				it = objects.erase(it);
				delete obj;
			}
			else ++it;
		}
	}
};
