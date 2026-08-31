#include "Collider.h"
#include "ObjectManager.h"
#include "Object2D.h"
#include "ColliderManager.h"
#include "ObjectManager.h"
#include <cassert>
#include "Master.h"

/// @brief Collider を生成する
/// @param parent parent の値
Collider::Collider(Object2D* parent)
	: parent_object_(parent)
	, position_(Vector2(0.0f, 0.0f))
	, position2_(Vector2(0.0f, 0.0f))
	, radius_(0.0f)
	, delete_flag_(false)
{
	assert(parent);

	Master::sceneManager->GetCurrentScene()->GetCollisionManager()->AddCollider(this);
}

/// @brief 破棄処理を行う
Collider::~Collider()
{
	if (Master::sceneManager && Master::sceneManager->GetCurrentScene())
	{
		auto colMgr = Master::sceneManager->GetCurrentScene()->GetCollisionManager();
		if (colMgr)
		{
			for (auto* col : colMgr->GetColliderList())
			{
				if (col != this)
				{
					col->RemoveCollision(this);
				}
			}
			colMgr->RemoveCollider(this);
		}
	}
}

/// @brief HitCheck を実行する
/// @param check check の値
/// @param isHit isHit の値
void Collider::HitCheck(Collider* check, bool isHit)
{
	if (isHit)
	{
		auto itr = std::find_if(
			collision_list_.begin(),
			collision_list_.end(),
			[&](Collider* col) { return col == check; }
		);

		if (itr != collision_list_.end())
		{
			if (this->parent_object_ != nullptr)
			{
				this->parent_object_->OnTrigger(this, check);
			}
		}
		else
		{
			collision_list_.push_back(check);
			if (this->parent_object_ != nullptr)
			{
				this->parent_object_->OnEnter(this, check);
			}
		}
	}
	else
	{
		auto itr = std::find_if(
			collision_list_.begin(),
			collision_list_.end(),
			[&](Collider* col) { return col == check; }
		);

		if (itr != collision_list_.end())
		{
			if (this->parent_object_ != nullptr)
			{
				this->parent_object_->OnExit(this, check);
			}
			collision_list_.erase(itr);
		}
	}
}

/// @brief 毎フレームの更新処理を行う
/// @param check check の値
void Collider::Update(Collider* check)
{
}

/// @brief 描画処理を行う
void Collider::Draw()
{
}

/// @brief 接触開始時の処理を行う
void Collider::OnEnter()
{
}

/// @brief 接触中の処理を行う
void Collider::OnTrigger()
{
}

/// @brief 接触終了時の処理を行う
void Collider::OnExit()
{
}

/// @brief RemoveCollision を実行する
/// @param collider collider の値
void Collider::RemoveCollision(Collider* collider)
{
	auto itr = std::find(collision_list_.begin(), collision_list_.end(), collider);
	if (itr != collision_list_.end())
	{
		collision_list_.erase(itr);
	}
}
