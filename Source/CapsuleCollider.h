#include "Vector2.h"
#pragma once
#include "Collider.h"
#include"Object2D.h"
class CapsuleCollider : public Collider
{
public:
	CapsuleCollider(Object2D* parent, Vector2 pos1, Vector2 pos2, float radius_);
	virtual ~CapsuleCollider();

	void Update(Collider* check) override;
	void Draw() override;

	

	//ww
};