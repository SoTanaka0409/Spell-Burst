#pragma once
#include "DxLib.h"
#include <vector>

class Object2D;
class ColliderManager;

class Collider
{
public:
	Collider(Object2D* parent);
	virtual ~Collider();

	virtual void Update(Collider* check);
	virtual void Draw();

	virtual void OnEnter();
	virtual void OnTrigger();
	virtual void OnExit();

	void HitCheck(Collider* check, bool isHit);

	void SetDeleteFlag(bool flag) { mbDeleteFlag = flag; }
	bool IsDeleteFlag() { return mbDeleteFlag; }

	Object2D* GetParentObject() 
	{
		return mpParentObject;
	}

	void InvalidateParent()
	{
		mpParentObject = nullptr;
	}

	void RemoveCollision(Collider* collider);

public:
	Object2D* mpParentObject;

	VECTOR mvPosition;
	VECTOR mvPosition2;
	float mfRadius;

	bool mbDeleteFlag;

protected:
	std::vector<Collider*> mCollisionList;
	ColliderManager* mpMyManager;
};
