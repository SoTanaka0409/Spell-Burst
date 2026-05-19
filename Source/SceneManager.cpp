#include"SceneManager.h"
#include"ObjectManager.h"
#include"Scene.h"
//
//#include"GameScene.h"








SceneManager::SceneManager()
	:mnSceneType(SCENE_TYPE::SCENE_NONE)
	, mnNextSceneType(SCENE_TYPE::SCENE_NONE)
	, mpCurrentScene(nullptr)
	,SceneHard(false)//ハードシーンかどうか
	,SceneNormal(false)//ノーマルシーンかどうか
{

}

SceneManager::~SceneManager()
{

}
void SceneManager::Initialize()
{
	////初期シーンの設定
	//mnNextSceneType = SCENE_TYPE::SCENE_RESULTWIN;

	//mnNextSceneType = SCENE_TYPE::SCENE_NAME;
	//mnNextSceneType = SCENE_TYPE::SCENE_3D;
	//mnNextSceneType = SCENE_TYPE::SCENE_RESULTWIN;
	mnNextSceneType = SCENE_TYPE::SCENE_3D;

	//シーン遷移させる
	ChangeSceneIfNeeded();

}



void SceneManager::Update()
{
	//シーンの更新






	mpCurrentScene->Update();
}

void SceneManager::Draw()
{
	//シーンの描画
	mpCurrentScene->Draw();
}

void SceneManager::Finalize()
{

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
		//現在のシーンの終了処理をする
		mpCurrentScene->Finalize();

		//一旦シーン自体も破棄しておく
		delete mpCurrentScene;
		mpCurrentScene = nullptr;
	}

	//次のシーンにするためシーンタイプを更新
	mnSceneType = mnNextSceneType;

	//mnSceneTypeに応じてシーンを生成する
	switch (mnSceneType)
	{
	
	case SCENE_TYPE::SCENE_3D:
		mpCurrentScene = new Scene3D();
		break;
	
		
	}
	//シーンの生成がされているはずなので、初期化処理を読んでおく
	mpCurrentScene->Initialize();

}