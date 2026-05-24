#pragma once
#include "Object2D.h"

class CapsuleCollider;

// 繝励Ξ繧､繝､繝ｼ縺ｮ蠢・ｮｺ謚・郁ｲｫ騾壼ｼｾ繧・ｼｷ蜉帙↑謾ｻ謦・ｼ峨ｒ邂｡逅・☆繧九け繝ｩ繧ｹ
class SpecialBullet : public Object2D {
private:
    float m_speed;      // 蠑ｾ縺ｮ遘ｻ蜍暮溷ｺｦ
    int m_damage;       // 荳弱∴繧九ム繝｡繝ｼ繧ｸ驥・
    bool m_isActive;    // 蠑ｾ縺梧怏蜉ｹ縺九←縺・°
    CapsuleCollider* mpCollider;

public:
    SpecialBullet(float x, float y);
    virtual ~SpecialBullet() override;

    virtual void Update() override;
    virtual void Draw() override;

    int GetDamage() const { return m_damage; }
    void Kill();

    virtual void OnTrigger(Collider* collider, Collider* check) override;
};
