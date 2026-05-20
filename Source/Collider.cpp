#include "Collider.h"
#include "Object2D.h"
#include "ColliderManager.h"
#include "Master.h"
#include "Scene.h"
#include "SceneManager.h"
#include <cassert>
#include <algorithm>

Collider::Collider(Object2D* parent)
	: mpParentObject(parent)
	, mvPosition(VGet(0.0f, 0.0f, 0.0f))
	, mvPosition2(VGet(0.0f, 0.0f, 0.0f))
	, mfRadius(0.0f)
	, mbDeleteFlag(false)
	, mpMyManager(nullptr)
{
	assert(parent);

	// Register with current scene's ColliderManager
	if (Master::sceneManager != nullptr && Master::sceneManager->GetCurrentScene() != nullptr)
	{
		mpMyManager = Master::sceneManager->GetCurrentScene()->GetCollisionManager();
		if (mpMyManager != nullptr)
		{
			mpMyManager->AddCollider(this);
		}
	}
}

Collider::~Collider()
{
	if (mpMyManager != nullptr)
	{
		mpMyManager->RemoveCollider(this);
	}
}

void Collider::HitCheck(Collider* check, bool isHit)
{
	if (isHit)
	{
		auto itr = std::find_if(
			mCollisionList.begin(),
			mCollisionList.end(),
			[&](Collider* col) { return col == check; }
		);

		if (itr != mCollisionList.end())
		{
			if (this->mpParentObject != nullptr)
			{
				mpParentObject->OnEnter(this, check);
			}
		}
		else
		{
			mCollisionList.push_back(check);
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
			[&](Collider* col) { return col == check; }
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

void Collider::RemoveCollision(Collider* collider)
{
	auto itr = std::find(mCollisionList.begin(), mCollisionList.end(), collider);
	if (itr != mCollisionList.end())
	{
		mCollisionList.erase(itr);
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
