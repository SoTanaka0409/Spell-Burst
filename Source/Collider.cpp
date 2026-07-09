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
		Master::sceneManager->GetCurrentScene()->GetCollisionManager()->RemoveCollider(this);
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
			this->parentObject->OnEnter(this, check);
		}
		else
		{	// リストに登録しておく
			collision_list_.push_back(check);//任意のタイミングでしか追加しないようにすれば
			if (this->parentObject != nullptr)
			{
				this->parentObject->OnTrigger(this, check);
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
