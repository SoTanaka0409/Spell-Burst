#pragma once
#include "Object2D.h"

class Collider;

class Barrier : public Object2D
{
public:
    Barrier(float x, float y, float radius,Object2D::Tag2D obj);
    virtual ~Barrier();

    virtual void Update() override;
    virtual void Draw() override;
    virtual void OnTrigger(Collider* collider, Collider* check) override;

private:
    float m_deployInterval;
    float m_activeDuration;
    float m_timer;
    float m_radius;
    bool m_isDeployed;

	//Object2D mpObj; // バリアを展開するオブジェクトへの参照（プレイヤーや敵など）

    Collider* mpCollider;
};
