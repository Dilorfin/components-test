#pragma once
#include <functional>
#include <vector>

#include "SystemLocator.hpp"

class Scene
{
public:
	virtual ~Scene() = default;
};

class SceneManager final
{
private:
	std::vector<std::function<Scene* ()>> scenesFabrics;
	std::map<std::string, size_t> scenesNames;

	Scene* currentScene = nullptr;
	size_t currentSceneId = 0;

	bool _switch = false;
	size_t nextScene = 0;

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

	[[nodiscard]] size_t getScenesCount() const
	{
		return this->scenesFabrics.size();
	}
	[[nodiscard]] size_t getCurrentSceneId() const
	{
		return currentSceneId;
	}

	void addScene(const std::string& name, const std::function<Scene* ()>& scene)
	{
		assert(scenesNames.count(name) == 0);
		scenesNames.insert({ name, scenesFabrics.size() });
		scenesFabrics.push_back(scene);
	}

	void loadScene(const std::string& name)
	{
		assert(scenesNames.count(name) > 0);
		this->loadScene(scenesNames[name]);
	}
	void loadScene(const size_t& id)
	{
		assert(!scenesFabrics.empty());
		assert(id < scenesFabrics.size());

		_switch = true;
		this->nextScene = id;
	}
	void reloadScene()
	{
		this->loadScene(this->currentSceneId);
	}

protected:
	friend int main();

	void switchScenes()
	{
		if (!_switch) return;
		_switch = false;

		if (currentScene)
		{
			delete currentScene;
			SystemLocator::getInstance()->clear();
		}

		currentScene = scenesFabrics[nextScene]();
	}
};
