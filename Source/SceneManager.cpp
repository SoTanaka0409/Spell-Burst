#include"SceneManager.h"
#include"ObjectManager.h"
#include"Scene.h"
#include"TitleScene.h"
#include"GameScene.h"
#include"ResultScene.h"

SceneManager::SceneManager()
	:mnSceneType(SCENE_TYPE::SCENE_NONE)
	, mnNextSceneType(SCENE_TYPE::SCENE_NONE)
	, mpCurrentScene(nullptr)
	,SceneHard(false)
	,SceneNormal(false)
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
	//最初のシーンの設定
	mnNextSceneType = SCENE_TYPE::SCENE_TITLE;

	//シーン遷移を行う
	ChangeSceneIfNeeded();
}

void SceneManager::Update()
{
	//シーンの更新
	if (mpCurrentScene != nullptr)
	{
		mpCurrentScene->Update();
	}
}

void SceneManager::Draw()
{
	//シーンの描画
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
	//現在のシーンと次のシーンが一緒であれば何もしない
	if (mnSceneType == mnNextSceneType)
	{
		return;
	}
	if (mpCurrentScene != nullptr)
	{
		//現在のシーンの終了処理を行う
		mpCurrentScene->Finalize();

		//一旦シーンそのものを破棄しておく
		delete mpCurrentScene;
		mpCurrentScene = nullptr;
	}

	//次のシーンにするためシーンタイプを更新
	mnSceneType = mnNextSceneType;

	//mnSceneTypeに応じてシーンを生成する
	switch (mnSceneType)
	{
	case SCENE_TYPE::SCENE_TITLE:
		mpCurrentScene = new TitleScene();
		break;

	case SCENE_TYPE::SCENE_GAME:
		mpCurrentScene = new GameScene();
		break;

	case SCENE_TYPE::SCENE_RESULT:
		mpCurrentScene = new ResultScene();
		break;

	default:
		// 未定義のシーンタイプの場合はタイトルシーンへ
		mnSceneType = SCENE_TYPE::SCENE_TITLE;
		mpCurrentScene = new TitleScene();
		break;
	}

	//シーンの生成が終わったので、初期化処理を呼ぶ
	if (mpCurrentScene != nullptr)
	{
		mpCurrentScene->Initialize();
	}
}
