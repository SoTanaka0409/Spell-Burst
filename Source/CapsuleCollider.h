#pragma once
#include "Collider.h"

// 2D Capsule Collider class
// Can represent a circle if pos1 == pos2
class CapsuleCollider : public Collider
{
public:
	CapsuleCollider(Object2D* parent, VECTOR pos1, VECTOR pos2, float radius);
	virtual ~CapsuleCollider() override;

	void Update(Collider* check) override;
	void Draw() override;

	void OnEnter() override;
	void OnTrigger() override;
	void OnExit() override;
};