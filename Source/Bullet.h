#pragma once
#include "Object2D.h"

class CapsuleCollider;

// 繝励Ξ繧､繝､繝ｼ縺檎匱蟆・☆繧矩壼ｸｸ縺ｮ蠑ｾ繧堤ｮ｡逅・☆繧九け繝ｩ繧ｹ
class Bullet : public Object2D
{
public:
    Bullet(float x, float y,float damage);
    virtual ~Bullet() override;
    void Draw() override;
    void Update() override;
    bool IsActive() { return m_isActive; }

    // Collision helper
    float GetX() { return mvPosition.x; }
    float GetY() { return mvPosition.y; }
    float GetRadius() const { return 10.0f; }
    int GetDamage() const { return m_damage; }
    void Kill();

	void AddReceivedDamage() { m_recivedDamage++; }

    virtual void OnTrigger(Collider* collider, Collider* check) override;

private:
    float m_speed;        // 蠑ｾ縺ｮ遘ｻ蜍暮溷ｺｦ
    bool m_isActive;      // 蠑ｾ縺梧怏蜉ｹ縺九←縺・°
    int m_damage;         // 蠑ｾ縺御ｸ弱∴繧九ム繝｡繝ｼ繧ｸ驥・
	int m_recivedDamage;    // ダメージを受けた回数  
	int m_MaxrecivedDamage; // ダメージを受けてmaxになると技を出す
    CapsuleCollider* mpCollider;
};
