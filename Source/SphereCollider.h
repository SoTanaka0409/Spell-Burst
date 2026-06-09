#pragma once
#include "Collider.h"

class SphereCollider : public Collider
{
public:
	SphereCollider(Object2D* parent, VECTOR center, float radius);
	virtual ~SphereCollider();

	void Update(Collider* check) override;
	void Draw() override;

	void OnEnter() override;
	void OnTrigger() override;
	void OnExit() override;

};
