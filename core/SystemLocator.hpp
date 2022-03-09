#pragma once
#include <map>

#include "GameObject.hpp"

class BaseSystem
{
public:
	virtual ~BaseSystem() = default;
	[[nodiscard]] virtual size_t hash_code() const = 0;
};

template<typename TSystem/*, typename TComponent*/>
class System : public BaseSystem
{
public:
	//virtual void registerComponent(TComponent* component) = 0;
	//virtual void unregisterComponent(TComponent* component) = 0;

	[[nodiscard]] size_t hash_code() const override
	{
		return typeid(TSystem).hash_code();
	}
};

//#include "GameObjectManager.hpp"
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
		//objects.clear();
	}

	void add(GameObject* object)
	{
		objects.push_back(object);
		object->start();
	}

	static void remove(GameObject* object)
	{
		object->destroy();
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

#include <typeinfo>

class SystemLocator final
{
private:
	friend class SceneManager;

	SystemLocator() = default;

	inline static SystemLocator* instance = nullptr;
	std::map<size_t, BaseSystem*> systems;

public:
	SystemLocator(SystemLocator&&) = delete;
	SystemLocator(const SystemLocator&) = delete;
	auto operator=(SystemLocator&&) = delete;
	auto operator=(const SystemLocator&) = delete;

	~SystemLocator()
	{
		this->clear();
	}

	static SystemLocator* getInstance()
	{
		if (instance == nullptr)
		{
			instance = new SystemLocator();
		}
		return instance;
	}

	template<typename TSystem>
	TSystem* getSystem()
	{
		const auto* instance = getInstance();
		const size_t id = typeid(TSystem).hash_code();
		if (!instance->systems.count(id))
		{
			//return nullptr;
			auto* system = new TSystem();
			systems[id] = system;
			return system;
		}
		return (TSystem*)systems.at(id);
	}

	/*template<typename TSystem, typename... Ts>
	TSystem* addSystem(Ts&&... args)
	{
		const size_t id = typeid(TSystem).hash_code();
		if (systems.count(id))
		{
			throw std::exception((std::string("System is already registered: ") + typeid(TSystem).name()).c_str());
		}

		auto* system = new TSystem(std::forward<Ts>(args)...);
		systems[id] = system;
		return system;
	}*/

	void clear()
	{
		const size_t id = typeid(GameObjectsManager).hash_code();
		delete systems[id];
		systems.erase(id);

		for (auto [key, system] : systems)
		{
			delete system;
		}
		systems.clear();
	}
};

class Scene
{
public:

};

class SceneManager final
{
private:
	Scene* currentScene = nullptr;

	bool _switch = false;

	inline static SceneManager* instance = nullptr;
public:

	static SceneManager* getInstance()
	{
		if (instance == nullptr)
		{
			instance = new SceneManager();
		}
		return instance;
	}

	~SceneManager()
	{
		delete currentScene;
	}

	void openScene()
	{
		_switch = true;
	}

protected:
	friend int main();

	template<typename TScene>
	void switchScenes()
	{
		if (!_switch) return;
		_switch = false;

		if (currentScene)
		{
			delete currentScene;
			SystemLocator::getInstance()->clear();
		}
		currentScene = (Scene*)new TScene();
	}
};
