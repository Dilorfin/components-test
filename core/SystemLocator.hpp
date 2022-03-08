#pragma once
#include <map>
#include <string>

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
		for (auto [key, system] : systems)
		{
			delete system;
		}
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
		const auto* instance = getInstance();
		const size_t id = typeid(TSystem).hash_code();
		if (!instance->systems.count(id))
		{
			return nullptr;
		}
		return (TSystem*)instance->systems.at(id);
	}


	template<typename TSystem, typename... Ts>
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
	}
};