#include "Collider.h"
#include "Object2D.h"
#include "ColliderManager.h"
#include"ObjectManager.h"
#include <cassert>
#include"Master.h"

Collider::Collider(Object2D* parent)
	: parentObject(parent)
	, position(Vector2(0.0f, 0.0f))
	, position2(Vector2(0.0f, 0.0f))
	, radius(0.0f)
	, deleteFlag(false)
{
	assert(parent);
	Master::sceneManager->GetCurrentScene()->GetCollisionManager()->AddCollider(this);




}

Collider::~Collider()
{
	Master::sceneManager->GetCurrentScene()->GetCollisionManager()->RemoveCollider(this);
}

void Collider::HitCheck(Collider* check, bool isHit)
{


	if (isHit)
	{
		auto itr = std::find_if(
			collisionList.begin(),
			collisionList.end(),
			[&](Collider* col) { return col == check; } // ラムダ式
		);

		if (itr != collisionList.end())
		{
			this->parentObject->OnEnter(this, check);
		}
		else
		{	// リストに登録しておく
			collisionList.push_back(check);//任意のタイミングでしか追加しないようにすれば
			if (this->parentObject != nullptr)
			{
				this->parentObject->OnTrigger(this, check);
			}
		}
	}
	else
	{
		auto itr = std::find_if(
			collisionList.begin(),
			collisionList.end(),
			[&](Collider* col) { return col == check; } // ラムダ式
		);

		if (itr != collisionList.end())
		{
			if (this->parentObject != nullptr)
			{
				this->parentObject->OnExit(this, check);
			}
			collisionList.erase(itr);
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