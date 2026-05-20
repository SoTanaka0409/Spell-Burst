#include "SceneManager.h"
#include "ObjectManager.h"
#include "Scene.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "ResultScene.h"

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
	// 最初はタイトル画面から開始する
	mnNextSceneType = SCENE_TYPE::SCENE_TITLE;

	// シーン切り替え処理を呼び出す
	ChangeSceneIfNeeded();
}

void SceneManager::Update()
{
	// シーン切り替えが必要なら処理する
	ChangeSceneIfNeeded();

	// 現在のシーンを更新する
	if (mpCurrentScene != nullptr)
	{
		mpCurrentScene->Update();
	}
}

#include "DebugLog.h"

void SceneManager::Draw()
{
	DebugLog("SceneManager::Draw() called! CurrentScene: %p\n", (void*)mpCurrentScene);
	// 現在のシーンを描画する
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
	// シーンが変わらない場合は何もしない
	if (mnSceneType == mnNextSceneType)
	{
		return;
	}

	// 現在のシーンがある場合は終了処理を行って破棄する
	if (mpCurrentScene != nullptr)
	{
		mpCurrentScene->Finalize();
		delete mpCurrentScene;
		mpCurrentScene = nullptr;
	}

	// シーンタイプを更新
	mnSceneType = mnNextSceneType;

	// 新しいシーンを生成する
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

	// 生成に成功していれば初期化処理を呼ぶ
	if (mpCurrentScene != nullptr)
	{
		mpCurrentScene->Initialize();
	}
}