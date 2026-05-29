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

SceneManager* Master::sceneManager = nullptr;

SceneManager::SceneManager()
	: mnSceneType(SCENE_TYPE::SCENE_NONE)
	, mnNextSceneType(SCENE_TYPE::SCENE_NONE)
	, mpCurrentScene(nullptr)
	, SceneHard(false)
	, SceneNormal(false)
{
}

SceneManager::~SceneManager()
{
	if (mpCurrentScene != nullptr)
	{
		delete mpCurrentScene;
		mpCurrentScene = nullptr;
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
	DebugLog("SceneManager::Draw() called! CurrentScene: %p\n", (void*)mpCurrentScene);
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
		delete mpCurrentScene;
		mpCurrentScene = nullptr;
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
		delete mpCurrentScene;
		mpCurrentScene = nullptr;
	}
	mnSceneType = mnNextSceneType;
	switch (mnSceneType)
	{
	case SCENE_TYPE::SCENE_TITLE:
		mpCurrentScene = new TitleScene();
		break;
	case SCENE_TYPE::SCENE_LEVEL:
		mpCurrentScene = new StageSelectScene();
		break;
	case SCENE_TYPE::SCENE_GAME:
		mpCurrentScene = new GameScene();
		break;
	case SCENE_TYPE::SCENE_RESULT:
		mpCurrentScene = new ResultScene();
		break;
	case SCENE_TYPE::SCENE_RULE:
		mpCurrentScene = new RuleScene();
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
