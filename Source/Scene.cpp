#include "Scene.h"
#include "ObjectManager.h"
#include "Master.h"
#include "ColliderManager.h"
#include "DebugLog.h"

Scene::Scene()
{
	// シーン固有のオブジェクトおよび当たり判定を管理するため専用のマネージャーを生成
	mpObjectManager = std::make_unique<ObjectManager>();
	mpColliderManager = std::make_unique<ColliderManager>();
}

Scene::~Scene()
{
	if (mpObjectManager != nullptr)
	{
		mpObjectManager->DeleteAll2D();
		mpObjectManager.reset();
	}
	if (mpColliderManager != nullptr)
	{
		mpColliderManager->DeleteAllCollider();
		mpColliderManager.reset();
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