#pragma once

class GameObject;

class BaseComponent 
{
protected:
	GameObject* gameObject = nullptr;
	friend class GameObject;

public:
	virtual ~BaseComponent() = default;

	virtual void start() = 0;
	virtual void update(const int64_t deltaTime) = 0;

	[[nodiscard]] virtual size_t hash_code() const = 0;
};

template<typename TComponent>
class Component : public BaseComponent
{
public:

	virtual void start() override
	{}

	virtual void update(const int64_t deltaTime) override
	{}

	[[nodiscard]] size_t hash_code() const final
	{
		return typeid(TComponent).hash_code();
	}
};