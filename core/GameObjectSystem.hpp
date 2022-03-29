#pragma once
#include <list>
#include <cassert>
#include <algorithm>

#include "GameObject.hpp"
#include "System.hpp"

class GameObjectSystem final : public System<GameObjectSystem, GameObject>
{
private:
	std::list<GameObject*> objects;
	object_id nextObjectId = 0;

public:
	~GameObjectSystem() override
	{
		for (const auto* obj : objects)
		{
			delete obj;
		}
	}

	void add(GameObject* object) override
	{
		assert(std::find(objects.begin(), objects.end(), object) == objects.end());

		object->id = nextObjectId++;
		objects.push_back(object);
		object->start();
	}

	void remove(GameObject* object) override
	{
		object->destroy();
	}

	void clear() override
	{
		this->nextObjectId = 0;
		for (const auto* obj : objects)
		{
			delete obj;
		}
		objects.clear();
	}

	[[nodiscard]] GameObject* getObjectById(const object_id id) const
	{
		for (auto* obj : objects)
		{
			if (obj->getId() == id)
				return obj;
		}
		return nullptr;
	}

	template<typename TObject>
	[[nodiscard]] TObject* getObjectById(const object_id id) const
	{
		for (auto* obj : objects)
		{
			if (obj->getId() == id)
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
