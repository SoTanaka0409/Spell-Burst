#include "Scene.h"
#include "ObjectManager.h"
#include "Master.h"
#include "ColliderManager.h"
#include "DebugLog.h"

Scene::Scene()
{
	// シーン固有のオブジェクトおよび当たり判定を管理するため専用のマネージャーを生成
	objectManager = std::make_unique<ObjectManager>();
	colliderManager = std::make_unique<ColliderManager>();
}

Scene::~Scene()
{
	if (objectManager != nullptr)
	{
		objectManager->DeleteAll2D();
		objectManager.reset();
	}
	if (colliderManager != nullptr)
	{
		colliderManager->DeleteAllCollider();
		colliderManager.reset();
	}
}

// 全オブジェクトの描画処理をマネージャー経由で一括実行
void Scene::Draw()
{
	if (objectManager != nullptr)
	{
		objectManager->Draw();
	}
	if (colliderManager != nullptr)
	{
		colliderManager->Draw();
	}
}

// 全オブジェクトの状態更新および当たり判定処理を一括実行
void Scene::Update()
{
	if (objectManager != nullptr)
	{
		objectManager->Update();
	}
	if (colliderManager != nullptr)
	{
		colliderManager->Update();
	}
}