#pragma once
#include <list>

#include "GameObject.hpp"
#include "System.hpp"

class GameObjectsManager final : public System<GameObjectsManager>
{
private:
	std::list<GameObject*> objects;
	object_id nextObjectId = 0;

public:
	~GameObjectsManager() override
	{
		for (const auto* obj : objects)
		{
			delete obj;
		}
	}

	void add(GameObject* object)
	{
		object->id = nextObjectId++;
		objects.push_back(object);
		object->start();
	}

	[[nodiscard]] GameObject* getObjectById(const object_id id) const
	{
		for (auto* obj : objects)
		{
			if(obj->getId() == id)
				return obj;
		}
		return nullptr;
	}

	template<typename TObject>
	[[nodiscard]] TObject* getObjectById(const object_id id) const
	{
		for (auto* obj : objects)
		{
			if(obj->getId() == id)
				return (TObject*)obj;
		}
		return nullptr;
	}

	void update(const int64_t deltaTime)
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
