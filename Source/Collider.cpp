#include "Collider.h"
#include "Object2D.h"
#include "ColliderManager.h"
#include"ObjectManager.h"
#include <cassert>
#include"Master.h"

Collider::Collider(Object2D* parent)
	: mpParentObject(parent)
	, mvPosition(Vector2(0.0f, 0.0f))
	, mvPosition2(Vector2(0.0f, 0.0f))
	, mfRadius(0.0f)
	, mbDeleteFlag(false)
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
			mCollisionList.begin(),
			mCollisionList.end(),
			[&](Collider* col) { return col == check; } // ラムダ式
		);

		if (itr != mCollisionList.end())
		{
			this->mpParentObject->OnEnter(this, check);
		}
		else
		{	// リストに登録しておく
			mCollisionList.push_back(check);//任意のタイミングでしか追加しないようにすれば
			if (this->mpParentObject != nullptr)
			{
				this->mpParentObject->OnTrigger(this, check);
			}
		}
	}
	else
	{
		auto itr = std::find_if(
			mCollisionList.begin(),
			mCollisionList.end(),
			[&](Collider* col) { return col == check; } // ラムダ式
		);

		if (itr != mCollisionList.end())
		{
			if (this->mpParentObject != nullptr)
			{
				this->mpParentObject->OnExit(this, check);
			}
			mCollisionList.erase(itr);
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