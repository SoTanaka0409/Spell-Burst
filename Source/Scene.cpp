#include "Scene.h"
#include "ObjectManager.h"
#include "Master.h"
#include "ColliderManager.h"
#include "DebugLog.h"

/// @brief Scene を生成する
Scene::Scene()
{
	// シーン内のオブジェクトと当たり判定を管理するマネージャーを生成する
	object_manager_ = std::make_unique<ObjectManager>();
	collider_manager_ = std::make_unique<ColliderManager>();
}

/// @brief 破棄処理を行う
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

// 全オブジェクトの描画をマネージャー経由でまとめて行う
/// @brief 描画処理を行う
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

// 全オブジェクトの更新と当たり判定処理をまとめて行う
/// @brief 毎フレームの更新処理を行う
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

/// @brief GetObjectManager を実行する
/// @return ObjectManager* 戻り値
ObjectManager* Scene::GetObjectManager()
{
	return object_manager_.get();
}

/// @brief GetCollisionManager を実行する
/// @return ColliderManager* 戻り値
ColliderManager* Scene::GetCollisionManager()
{
	return collider_manager_.get();
}
