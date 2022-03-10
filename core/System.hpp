#pragma once
#include <typeinfo>

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