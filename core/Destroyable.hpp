#pragma once
class Destroyable
{
private:
	bool _isDestroyed = false;
public:
	void destroy()
	{
		_isDestroyed = true;
	}
	[[nodiscard]] bool isDestroyed() const
	{
		return _isDestroyed;
	}
};