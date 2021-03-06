#pragma once
#include <functional>
#include <vector>

#include "systems/RenderSystem.hpp"
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
	size_t nextSceneId = 0;

	SceneManager() = default;

public:

	static SceneManager* getInstance()
	{
		static SceneManager instance;
		return &instance;
	}

	~SceneManager()
	{
		delete currentScene;
	}

	void update()
	{
		if (!_switch) return;
		_switch = false;

		if (currentScene)
		{
			auto* render = SystemLocator::getSystem<RenderSystem>()->getRenderTarget();
			render->setView(render->getDefaultView());

			delete currentScene;
			SystemLocator::getInstance()->clear();
			SystemLocator::getSystem<RenderSystem>()->setRenderTarget(render);
		}

		currentScene = scenesFabrics[nextSceneId]();
		currentSceneId = nextSceneId;
	}

	[[nodiscard]] size_t getScenesCount() const
	{
		return this->scenesFabrics.size();
	}
	[[nodiscard]] size_t getCurrentSceneId() const
	{
		return currentSceneId;
	}
	[[nodiscard]] std::string getCurrentSceneName() const
	{
		assert(currentScene);
		auto predicate = [this](std::pair<std::string, size_t> pair)->bool {
			return this->currentSceneId == pair.second;
		};
		const auto resultIt = std::find_if(std::begin(scenesNames), std::end(scenesNames), predicate);
		assert(resultIt != std::end(scenesNames));
		return resultIt->first;
	}

	size_t addScene(const std::string& name, const std::function<Scene* ()>& scene)
	{
		assert(scenesNames.count(name) == 0);

		const auto id = scenesFabrics.size();

		scenesNames.insert({ name, id });
		scenesFabrics.push_back(scene);

		return id;
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
		this->nextSceneId = id;
	}
	void reloadScene()
	{
		this->loadScene(this->currentSceneId);
	}

	void clear()
	{
		scenesFabrics.clear();
		scenesNames.clear();

		if (currentScene)
		{
			delete currentScene;
			currentScene = nullptr;
		}

		_switch = false;

		currentSceneId = 0;
		nextSceneId = 0;
	}
};
