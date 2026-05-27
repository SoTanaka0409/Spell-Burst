#pragma once
#include "Collider.h"
#include"Object2D.h"
class CapsuleCollider : public Collider
{
public:
	CapsuleCollider(Object2D* parent, VECTOR pos1, VECTOR pos2, float radius);
	virtual ~CapsuleCollider();

	void Update(Collider* check) override;
	void Draw() override;

	

	//ww
};