#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "../../core/SceneManager.hpp"

TEST_CASE("scenes count")
{
	SUBCASE("on create count is zero")
	{
		const auto* manager = SceneManager::getInstance();

		const auto count = manager->getScenesCount();

		CHECK(count == 0);
	}

	SUBCASE("multiple scenes count")
	{
		auto* manager = SceneManager::getInstance();

		manager->addScene("0", []()->Scene* { return new Scene(); });
		manager->addScene("1", []()->Scene* { return new Scene(); });
		manager->addScene("2", []()->Scene* { return new Scene(); });

		const auto count = manager->getScenesCount();

		CHECK(count == 3);
	}

	SceneManager::getInstance()->clear();
}

TEST_CASE("scene loading")
{
	SUBCASE("load by name")
	{
		auto* manager = SceneManager::getInstance();

		manager->addScene("0", []()->Scene* { return new Scene(); });
		manager->addScene("1", []()->Scene* { return new Scene(); });
		const std::string sceneName = "2";
		const auto sceneId = manager->addScene(sceneName, []()->Scene* { return new Scene(); });

		manager->loadScene(sceneName);
		manager->update();

		const auto currentId = manager->getCurrentSceneId();
		const auto currentName = manager->getCurrentSceneName();

		CHECK(currentId == sceneId);
		CHECK(currentName == sceneName);
	}

	SUBCASE("load by id")
	{
		auto* manager = SceneManager::getInstance();

		manager->addScene("0", []()->Scene* { return new Scene(); });
		manager->addScene("1", []()->Scene* { return new Scene(); });
		const std::string sceneName = "2";
		const auto sceneId = manager->addScene(sceneName, []()->Scene* { return new Scene(); });

		manager->loadScene(sceneId);
		manager->update();

		const auto currentId = manager->getCurrentSceneId();
		const auto currentName = manager->getCurrentSceneName();

		CHECK(currentId == sceneId);
		CHECK(currentName == sceneName);
	}

	SUBCASE("scene reloading")
	{
		auto* manager = SceneManager::getInstance();

		manager->addScene("0", []()->Scene* { return new Scene(); });
		manager->addScene("42", []()->Scene* { return new Scene(); });
		const std::string sceneName = "1";
		const auto sceneId = manager->addScene(sceneName, []()->Scene* { return new Scene(); });

		manager->loadScene(sceneId);
		manager->update();

		manager->reloadScene();

		const auto currentId = manager->getCurrentSceneId();
		const auto currentName = manager->getCurrentSceneName();

		CHECK(currentId == sceneId);
		CHECK(currentName == sceneName);
	}

	SceneManager::getInstance()->clear();
}
