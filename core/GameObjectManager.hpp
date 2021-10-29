#pragma once
#include <list>

#include "GameObject.hpp"

class GameObjectsManager final
{
private:
	inline static GameObjectsManager* instance = nullptr;
	std::list<GameObject*> objects;
	std::list<GameObject*> destroyed;

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
		destroyed.push_back(object);
	}

	void update(const float deltaTime)
	{
		for (auto obj : destroyed)
		{
			objects.remove(obj);
			delete obj;
		}
		destroyed.clear();

		for (const auto* obj : objects)
		{
			obj->update(deltaTime);
		}
	}
};