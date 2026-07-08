#include "Scene.h"
#include "ObjectManager.h"
#include "Master.h"
#include "ColliderManager.h"
#include "DebugLog.h"

Scene::Scene()
{
	// シーン固有のオブジェクトおよび当たり判定を管理するため専用のマネージャーを生成
	object_manager_ = std::make_unique<ObjectManager>();
	collider_manager_ = std::make_unique<ColliderManager>();
}

Scene::~Scene()
{
	if (object_manager_ != nullptr)
	{
		object_manager_->DeleteAll2D();
		object_manager_.reset();
	}
	if (collider_manager_ != nullptr)
	{
		collider_manager_->DeleteAllCollider();
		collider_manager_.reset();
	}
}

// 全オブジェクトの描画処理をマネージャー経由で一括実行
void Scene::Draw()
{
	if (object_manager_ != nullptr)
	{
		object_manager_->Draw();
	}
	if (collider_manager_ != nullptr)
	{
		collider_manager_->Draw();
	}
}

// 全オブジェクトの状態更新および当たり判定処理を一括実行
void Scene::Update()
{
	if (object_manager_ != nullptr)
	{
		object_manager_->Update();
	}
	if (collider_manager_ != nullptr)
	{
		collider_manager_->Update();
	}
}
