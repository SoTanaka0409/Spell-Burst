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
	: mnSceneType(SCENE_TYPE::SCENE_NONE)
	, mnNextSceneType(SCENE_TYPE::SCENE_NONE)
	, SceneHard(false)
	, SceneNormal(false)
{
}

SceneManager::~SceneManager()
{
	if (mpCurrentScene != nullptr)
	{
		mpCurrentScene.reset();
	}
}

void SceneManager::Initialize()
{
	mnNextSceneType = SCENE_TYPE::SCENE_TITLE;
	ChangeSceneIfNeeded();
}

void SceneManager::Update()
{
	ChangeSceneIfNeeded();
	if (mpCurrentScene != nullptr)
	{
		mpCurrentScene->Update();
	}
}


void SceneManager::Draw()
{
	DebugLog("SceneManager::Draw() called! CurrentScene: %p\n", (void*)mpCurrentScene.get());
	if (mpCurrentScene != nullptr)
	{
		mpCurrentScene->Draw();
	}
}

void SceneManager::Finalize()
{
	if (mpCurrentScene != nullptr)
	{
		mpCurrentScene->Finalize();
		mpCurrentScene.reset();
	}
}

void SceneManager::ChangeSceneIfNeeded()
{
	if (mnSceneType == mnNextSceneType)
	{
		return;
	}
	SoundManager::GetInstance()->StopBGM();
	if (mpCurrentScene != nullptr)
	{
		mpCurrentScene->Finalize();
		mpCurrentScene.reset();
	}
	mnSceneType = mnNextSceneType;
	switch (mnSceneType)
	{
	case SCENE_TYPE::SCENE_TITLE:
		mpCurrentScene = std::make_unique<TitleScene>();
		break;
	case SCENE_TYPE::SCENE_LEVEL:
		mpCurrentScene = std::make_unique<StageSelectScene>();
		break;
	case SCENE_TYPE::SCENE_GAME:
		mpCurrentScene = std::make_unique<GameScene>();
		break;
	case SCENE_TYPE::SCENE_RESULT:
		mpCurrentScene = std::make_unique<ResultScene>();
		break;
	case SCENE_TYPE::SCENE_RULE:
		mpCurrentScene = std::make_unique<RuleScene>();
		break;
	default:
		mpCurrentScene = nullptr;
		break;
	}
	if (mpCurrentScene != nullptr)
	{
		mpCurrentScene->Initialize();
	}
}
