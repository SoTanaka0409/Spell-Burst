#pragma once
#include "Object2D.h"

class CapsuleCollider;

// 繝懊せ繧ｭ繝｣繝ｩ繧ｯ繧ｿ繝ｼ縺ｮ繝・・繧ｿ繧・険繧玖・縺・∝ｼｾ蟷輔ヱ繧ｿ繝ｼ繝ｳ繧堤ｮ｡逅・☆繧九け繝ｩ繧ｹ
class Boss : public Object2D {
private:
    float m_speed;        // 遘ｻ蜍暮溷ｺｦ
    int m_hp;             // 迴ｾ蝨ｨ縺ｮ菴灘鴨
    int m_maxHp;          // 譛螟ｧ菴灘鴨
    bool m_isActive;      // 繝懊せ縺梧ｴｻ蜍穂ｸｭ縺九←縺・°縺ｮ繝輔Λ繧ｰ
    int m_bossType;       // 繝懊せ縺ｮ遞ｮ鬘橸ｼ・縲・・・
    
    // 繝ｩ繝ｳ繝繝遘ｻ蜍輔・逶ｮ逧・慍・医ち繝ｼ繧ｲ繝・ヨ蠎ｧ讓呻ｼ・
    float m_targetX, m_targetY;
    
    // 謾ｻ謦・ヱ繧ｿ繝ｼ繝ｳ縺ｨ逋ｺ蟆・俣髫斐ｒ邂｡逅・☆繧九ち繧､繝槭・
    int m_attackTimer;
    int m_patternIndex;

    // 謦・ｴ縺輔ｌ縺滄圀縺ｮ豁ｻ莠｡貍泌・繧堤ｮ｡逅・☆繧九せ繝・・繧ｿ繧ｹ縺ｨ繧ｿ繧､繝槭・
    bool m_isDying;
    int m_deathTimer;
    
    // 繝輔ぉ繝ｼ繧ｺ・域ｮ区ｩ滂ｼ峨→辟｡謨ｵ譎る俣繧堤ｮ｡逅・☆繧句､画焚
    int m_lives;
    int m_invincibleTimer;
    int m_invincibleCycleTimer; // 5遘偵＃縺ｨ縺ｮ辟｡謨ｵ繧堤ｮ｡逅・☆繧九ち繧､繝槭・
    
    CapsuleCollider* mpCollider;

public:
    Boss(float x, float y, int bossType = 3);
    virtual ~Boss() override;

    // 豈弱ヵ繝ｬ繝ｼ繝蜻ｼ縺ｰ繧後∫ｧｻ蜍募・逅・ｄ謾ｻ謦・・逅・∵ｭｻ莠｡譎ゅ・貍泌・繧定｡後≧
    void Update() override;

    // 豈弱ヵ繝ｬ繝ｼ繝蜻ｼ縺ｰ繧後√・繧ｹ縺ｮ逕ｻ蜒上ｄ陲ｫ繝繝｡繝ｼ繧ｸ譎ゅ・轤ｹ貊・柑譫懊ｒ謠冗判縺吶ｋ
    void Draw() override;

    int GetHp() const { return m_hp; }
    int GetMaxHp() const { return m_maxHp; }
    bool IsActive() const { return m_isActive; }
    int GetLives() const { return m_lives; }

    float GetX() const { return mvPosition.x; }
    float GetY() const { return mvPosition.y; }
    float GetRadius() const { return 80.0f; }

    // 繝励Ξ繧､繝､繝ｼ縺ｮ謾ｻ謦・ｒ蜿励￠縺滄圀縺ｫ蜻ｼ縺ｰ繧後ｋ繝繝｡繝ｼ繧ｸ蜃ｦ逅・
    void TakeDamage(int damage);

    // 繝懊せ繧貞ｮ悟・縺ｫ豸域ｻ・＆縺帙ｋ蜃ｦ逅・
    void Kill();

    // 莉悶・繧ｪ繝悶ず繧ｧ繧ｯ繝医→驥阪↑縺｣縺ｦ縺・ｋ譎ゅ・蜃ｦ逅・ｼ亥ｼｾ縺ｨ縺ｮ蠖薙◆繧雁愛螳夲ｼ・
    virtual void OnTrigger(Collider* collider, Collider* check) override;

private:
    // 繝懊せ縺ｮ蠑ｾ蟷輔ヱ繧ｿ繝ｼ繝ｳ蜃ｦ逅・ｾ､
    void ShootRadialBarrage();    // 蜈ｨ譁ｹ菴搾ｼ域叛蟆・憾・峨∈縺ｮ蠑ｾ蟷・
    void ShootFanBarrage();       // 謇・憾・亥燕譁ｹ蠎・ｯ・峇・峨∈縺ｮ蠑ｾ蟷・
    void ShootTargetedBarrage();  // 繝励Ξ繧､繝､繝ｼ繧堤漁縺・・讖溽漁縺・ｼｾ蟷・
    void ShootSimpleBarrage();    // 繧ｿ繧､繝・逕ｨ縺ｮ蜊倡ｴ斐↑蠑ｾ
    void ShootBouncingBarrage();  // 繧ｿ繧､繝・逕ｨ縺ｮ蜿榊ｰ・ｼｾ
    
    // 谺｡縺ｮ繝ｩ繝ｳ繝繝遘ｻ蜍輔・逶ｮ逧・慍繧呈ｱｺ螳壹☆繧・
    void SelectNewTarget();
};
