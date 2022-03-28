#pragma once
#include <map>
#include <typeinfo>

#include "System.hpp"
#include "GameObjectSystem.hpp"

class SystemLocator final
{
private:
	SystemLocator() = default;

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
		static SystemLocator instance;
		return &instance;
	}

	template<typename TSystem>
	static TSystem* getSystem()
	{
		const size_t id = typeid(TSystem).hash_code();
		if (!getInstance()->systems.count(id))
		{
			auto* system = new TSystem();
			getInstance()->systems[id] = system;
			return system;
		}
		return (TSystem*)getInstance()->systems.at(id);
	}

protected:
	friend class SceneManager;

	void clear()
	{
		const size_t id = typeid(GameObjectSystem).hash_code();
		if (systems.count(id))
		{
			delete systems[id];
			systems.erase(id);
		}

		for (auto [key, system] : systems)
		{
			delete system;
		}
		systems.clear();
	}
};
