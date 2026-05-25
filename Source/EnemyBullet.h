#pragma once
#include "Object2D.h"

class CapsuleCollider;

// 謨ｵ繧ｭ繝｣繝ｩ繧ｯ繧ｿ繝ｼ・磯尅鬲壹ｄ繝懊せ・峨′逋ｺ蟆・☆繧句ｼｾ繧堤ｮ｡逅・☆繧九け繝ｩ繧ｹ
class EnemyBullet : public Object2D {
private:
    float m_dx, m_dy;   // 遘ｻ蜍墓婿蜷代・繝吶け繝医Ν
    float m_speed;      // 蠑ｾ縺ｮ遘ｻ蜍暮溷ｺｦ
    bool m_isActive;    // 蠑ｾ縺梧怏蜉ｹ縺九←縺・°
    CapsuleCollider* mpCollider;

    bool m_canReflect;
    bool m_hasReflected;
    bool m_isStunBullet; // 繧ｹ繧ｿ繝ｳ蜉ｹ譫懊ｒ謖√▽蠑ｾ縺九←縺・°
    int m_homingTimer;   // 霑ｽ蟆ｾ・医・繝ｼ繝溘Φ繧ｰ・峨☆繧区ｮ九ｊ繝輔Ξ繝ｼ繝謨ｰ
    int m_homingDelayTimer;

public:
    EnemyBullet(float x, float y, float dx, float dy, float speed, bool canReflect = false, bool isStunBullet = false, int homingFrames = 0, int homingDelayFrames = 0);
    virtual ~EnemyBullet() override;

    void Update() override;
    void Draw() override;

    void Kill();

    virtual void OnTrigger(Collider* collider, Collider* check) override;
};
