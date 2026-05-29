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
    int GetHitCount() const { return m_hitCount; }

private:
    float m_deployInterval;
    float m_activeDuration;
    float m_timer;
    float m_radius;
    bool m_isDeployed;

	//Object2D mpObj; // 繝舌Μ繧｢繧貞ｱ暮幕縺吶ｋ繧ｪ繝悶ず繧ｧ繧ｯ繝医∈縺ｮ蜿ら・・医・繝ｬ繧､繝､繝ｼ繧・雰縺ｪ縺ｩ・・

    Collider* mpCollider;
    int m_hitCount; // 繝舌Μ繧｢縺碁亟縺・□蠑ｾ縺ｮ謨ｰ
};
