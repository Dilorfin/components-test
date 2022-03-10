#pragma once
#include "SystemLocator.hpp"

class Scene
{
public:
	virtual ~Scene() = default;
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
