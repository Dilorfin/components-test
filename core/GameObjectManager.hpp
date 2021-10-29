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
		object->destroy();
	}

	void update(const float deltaTime)
	{
		auto it = objects.begin(); 
		while(it != objects.end())
		{
			auto * obj = *it;
			obj->update(deltaTime);

			if(obj->isDestroyed())
			{
				it = objects.erase(it);
				delete obj;
			}
			else ++it;
		}
	}
};
