#include "SceneManager.h"
#include "ObjectManager.h"
#include "Scene.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "RuleScene.h"
#include "DebugLog.h"
#include "Master.h"
#include "SoundManager.h"

std::unique_ptr<SceneManager> Master::sceneManager = nullptr;

SceneManager::SceneManager()
	: sceneType(SCENE_TYPE::SCENE_NONE)
	, nextSceneType(SCENE_TYPE::SCENE_NONE)
	, SceneHard(false)
	, SceneNormal(false)
{
}

SceneManager::~SceneManager()
{
	if (currentScene != nullptr)
	{
		currentScene.reset();
	}
}

void SceneManager::Initialize()
{
	nextSceneType = SCENE_TYPE::SCENE_TITLE;
	ChangeSceneIfNeeded();
}

void SceneManager::Update()
{
	ChangeSceneIfNeeded();
	if (currentScene != nullptr)
	{
		currentScene->Update();
	}
}


void SceneManager::Draw()
{
	DebugLog("SceneManager::Draw() called! CurrentScene: %p\n", (void*)currentScene.get());
	if (currentScene != nullptr)
	{
		currentScene->Draw();
	}
}

void SceneManager::Finalize()
{
	if (currentScene != nullptr)
	{
		currentScene->Finalize();
		currentScene.reset();
	}
}

void SceneManager::ChangeSceneIfNeeded()
{
	if (sceneType == nextSceneType)
	{
		return;
	}
	SoundManager::GetInstance()->StopBGM();
	if (currentScene != nullptr)
	{
		currentScene->Finalize();
		currentScene.reset();
	}
	sceneType = nextSceneType;
	switch (sceneType)
	{
	case SCENE_TYPE::SCENE_TITLE:
		currentScene = std::make_unique<TitleScene>();
		break;
	case SCENE_TYPE::SCENE_LEVEL:
		currentScene = std::make_unique<StageSelectScene>();
		break;
	case SCENE_TYPE::SCENE_GAME:
		currentScene = std::make_unique<GameScene>();
		break;
	case SCENE_TYPE::SCENE_RESULT:
		currentScene = std::make_unique<ResultScene>();
		break;
	case SCENE_TYPE::SCENE_RULE:
		currentScene = std::make_unique<RuleScene>();
		break;
	default:
		currentScene = nullptr;
		break;
	}
	if (currentScene != nullptr)
	{
		currentScene->Initialize();
	}
}
