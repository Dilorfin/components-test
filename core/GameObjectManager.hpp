#pragma once
#include <list>

#include "GameObject.hpp"

class GameObjectsManager final
{
private:
	inline static GameObjectsManager* instance = nullptr;
	std::list<GameObject*> objects;

	GameObjectsManager() = default;
public:
	GameObjectsManager(const GameObjectsManager&) = delete;
	GameObjectsManager(GameObjectsManager&&) = delete;
	auto operator=(const GameObjectsManager&) = delete;
	auto operator=(GameObjectsManager&&) = delete;

	static GameObjectsManager * getInstance()
	{
		if (instance == nullptr)
		{
			instance = new GameObjectsManager();
		}
		return instance;
	}

	~GameObjectsManager()
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

	void removeObject(GameObject* object)
	{
		std::erase(objects, object);
	}

	void update(const float deltaTime) const 
	{
		for (const auto* obj : objects)
		{
			obj->update(deltaTime);
		}
	}
};