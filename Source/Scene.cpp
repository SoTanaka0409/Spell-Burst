#include "Scene.h"
#include "ObjectManager.h"
#include "Master.h"
#include "ColliderManager.h"
#include "DebugLog.h"

Scene::Scene()
{
	// シーン固有のオブジェクトおよび当たり判定を管理するため専用のマネージャーを生成
	mpObjectManager = new ObjectManager();
	mpColliderManager = new ColliderManager();
}

Scene::~Scene()
{
	if (mpObjectManager != nullptr)
	{
		mpObjectManager->DeleteAll2D();
		delete mpObjectManager;
	}
	if (mpColliderManager != nullptr)
	{
		mpColliderManager->DeleteAllCollider();
		delete mpColliderManager;
	}
}

// 全オブジェクトの描画処理をマネージャー経由で一括実行
void Scene::Draw()
{
	if (mpObjectManager != nullptr)
	{
		mpObjectManager->Draw();
	}
	if (mpColliderManager != nullptr)
	{
		mpColliderManager->Draw();
	}
}

// 全オブジェクトの状態更新および当たり判定処理を一括実行
void Scene::Update()
{
	if (mpObjectManager != nullptr)
	{
		mpObjectManager->Update();
	}
	if (mpColliderManager != nullptr)
	{
		mpColliderManager->Update();
	}
}