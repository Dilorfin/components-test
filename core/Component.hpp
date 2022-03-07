#pragma once

class GameObject;

class BaseComponent 
{
protected:
	GameObject* gameObject = nullptr;
	friend class GameObject;

public:
	virtual ~BaseComponent() = default;

	virtual void start() {}
	virtual void update(const int64_t deltaTime) {}

	[[nodiscard]] virtual size_t hash_code() const = 0;
};

template<typename TComponent>
class Component : public BaseComponent
{
public:
	[[nodiscard]] size_t hash_code() const final
	{
		return typeid(TComponent).hash_code();
	}
};