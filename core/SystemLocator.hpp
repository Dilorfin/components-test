#pragma once
#include <map>
#include <typeinfo>

#include "GameObject.hpp"
#include "System.hpp"
#include "GameObjectSystem.hpp"

class SystemLocator final
{
private:
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
	static TSystem* getSystem()
	{
		const size_t id = typeid(TSystem).hash_code();
		if (!getInstance()->systems.count(id))
		{
			auto* system = new TSystem();
			instance->systems[id] = system;
			return system;
			//return nullptr;
		}
		return (TSystem*)instance->systems.at(id);
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

protected:
	friend class SceneManager;

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
