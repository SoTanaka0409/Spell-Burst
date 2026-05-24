#pragma once
#include "Object2D.h"

class CapsuleCollider;

// 繝励Ξ繧､繝､繝ｼ縺ｮ霑第磁謾ｻ謦・ｼ医リ繧､繝輔ｄ蜑｣縺ｮ謖ｯ繧奇ｼ峨ｒ邂｡逅・☆繧九け繝ｩ繧ｹ
class MeleeAttack : public Object2D {
private:
    int m_lifetime; // 謾ｻ謦・・謖∫ｶ壽凾髢難ｼ医ヵ繝ｬ繝ｼ繝謨ｰ・・
    int m_damage;   // 荳弱∴繧九ム繝｡繝ｼ繧ｸ驥・
    CapsuleCollider* mpCollider;

public:
    MeleeAttack(float x, float y);
    virtual ~MeleeAttack() override;

    virtual void Update() override;
    virtual void Draw() override;

    int GetDamage() const { return m_damage; }
    void Kill();

    virtual void OnTrigger(Collider* collider, Collider* check) override;
};
