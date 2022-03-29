#pragma once
#include <typeinfo>

class BaseSystem
{
public:
	virtual ~BaseSystem() = default;
	[[nodiscard]] virtual size_t hash_code() const = 0;
};

template<typename TSystem, typename TComponent>
class System : public BaseSystem
{
public:
	virtual void add(TComponent* component) = 0;
	virtual void remove(TComponent* component) = 0;

	[[nodiscard]] size_t hash_code() const override
	{
		return typeid(TSystem).hash_code();
	}
};
