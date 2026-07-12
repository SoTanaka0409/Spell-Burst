#include "Collider.h"
#include "ObjectManager.h"
#include "Object2D.h"
#include "ColliderManager.h"
#include"ObjectManager.h"
#include <cassert>
#include"Master.h"

Collider::Collider(Object2D* parent)
	: parentObject(parent)
	, position_(Vector2(0.0f, 0.0f))
	, position2(Vector2(0.0f, 0.0f))
	, radius_(0.0f)
	, delete_flag_(false)
{
	assert(parent);
	Master::sceneManager->GetCurrentScene()->GetCollisionManager()->AddCollider(this);




}

Collider::~Collider()
{
	if (Master::sceneManager && Master::sceneManager->GetCurrentScene()) {
		auto colMgr = Master::sceneManager->GetCurrentScene()->GetCollisionManager();
		if (colMgr) {
			for (auto* col : colMgr->GetColliderList()) {
				if (col != this) {
					col->RemoveCollision(this);
				}
			}
			colMgr->RemoveCollider(this);
		}
	}
}

void Collider::HitCheck(Collider* check, bool isHit)
{


	if (isHit)
	{
		auto itr = std::find_if(
			collision_list_.begin(),
			collision_list_.end(),
			[&](Collider* col) { return col == check; } // ラムダ式
		);

		if (itr != collision_list_.end())
		{
			// 継続接触中 → OnTrigger（毎フレーム呼ばれる）
			if (this->parentObject != nullptr)
			{
				this->parentObject->OnTrigger(this, check);
			}
		}
		else
		{	// 初回接触 → リストに登録してOnEnterを呼ぶ
			collision_list_.push_back(check);
			if (this->parentObject != nullptr)
			{
				this->parentObject->OnEnter(this, check);
			}
		}
	}
	else
	{
		auto itr = std::find_if(
			collision_list_.begin(),
			collision_list_.end(),
			[&](Collider* col) { return col == check; } // ラムダ式
		);

		if (itr != collision_list_.end())
		{
			if (this->parentObject != nullptr)
			{
				this->parentObject->OnExit(this, check);
			}
			collision_list_.erase(itr);
		}
	}
}




void Collider::Update(Collider* check)
{

}

void Collider::Draw()
{

}

void Collider::OnEnter()
{

}

void Collider::OnTrigger()
{

}

void Collider::OnExit()
{

}

void Collider::RemoveCollision(Collider* collider_)
{
    auto itr = std::find(collision_list_.begin(), collision_list_.end(), collider_);
    if (itr != collision_list_.end()) {
        collision_list_.erase(itr);
    }
}
