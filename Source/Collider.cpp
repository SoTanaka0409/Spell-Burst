#include "Collider.h"
#include "ObjectManager.h"
#include "Object2D.h"
#include "ColliderManager.h"
#include "ObjectManager.h"
#include <cassert>
#include "Master.h"

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

void Collider::RemoveCollision(Collider* collider)
{
	auto itr = std::find(collision_list_.begin(), collision_list_.end(), collider);
	if (itr != collision_list_.end())
	{
		collision_list_.erase(itr);
	}
}
