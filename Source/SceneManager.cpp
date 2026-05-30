#include "SceneManager.h"
#include "ObjectManager.h"
#include "Scene.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "DebugLog.h"

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
	// Start from the title screen
	mnNextSceneType = SCENE_TYPE::SCENE_TITLE;

	// Call scene switching process
	ChangeSceneIfNeeded();
}

void SceneManager::Update()
{
	// Process scene changes if necessary
	ChangeSceneIfNeeded();

	// Update current scene
	if (mpCurrentScene != nullptr)
	{
		mpCurrentScene->Update();
	}
}


void SceneManager::Draw()
{
	DebugLog("SceneManager::Draw() called! CurrentScene: %p\n", (void*)mpCurrentScene);
	// draw the current scene
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
	// If the scene does not change, do nothing
	if (mnSceneType == mnNextSceneType)
	{
		return;
	}

	// If there is a current scene, perform end processing and discard it.
	if (mpCurrentScene != nullptr)
	{
		mpCurrentScene->Finalize();
		delete mpCurrentScene;
		mpCurrentScene = nullptr;
	}

	// Update scene type
	mnSceneType = mnNextSceneType;

	// generate a new scene
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
	default:
		mpCurrentScene = nullptr;
		break;
	}

	// If the generation is successful, call the initialization process
	if (mpCurrentScene != nullptr)
	{
		mpCurrentScene->Initialize();
	}
}