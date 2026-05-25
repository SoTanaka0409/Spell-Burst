#pragma once
#include "Object2D.h"

class CapsuleCollider;

// 繝励Ξ繧､繝､繝ｼ・域桃菴懊く繝｣繝ｩ繧ｯ繧ｿ繝ｼ・峨・繝・・繧ｿ繧・険繧玖・縺・ｒ邂｡逅・☆繧九け繝ｩ繧ｹ
// Object2D繧堤ｶ呎価縺励∫判髱｢荳翫・謠冗判繧・ｽ薙◆繧雁愛螳壹ｒ謖√▲縺ｦ縺・∪縺吶・
class Player : public Object2D
{
public:
    // 繝励Ξ繧､繝､繝ｼ縺ｮ謾ｻ謦・婿豕輔ｒ螳夂ｾｩ縺吶ｋ蛻玲嫌蝙・
    enum AttackMode 
    {
        AttackMode_Melee,   // 霑第磁謾ｻ謦・ｼ医リ繧､繝慕ｭ会ｼ・
        AttackMode_Special  // 蠢・ｮｺ謚・医け繝ｼ繝ｫ繝繧ｦ繝ｳ縺ゅｊ・・
    };

private:
    float m_x, m_y;       // 繝励Ξ繧､繝､繝ｼ縺ｮ逕ｻ髱｢荳翫・XY蠎ｧ讓・
    float m_speed;        // 繝励Ξ繧､繝､繝ｼ縺ｮ遘ｻ蜍暮溷ｺｦ
    int m_hp;             // 迴ｾ蝨ｨ縺ｮ菴灘鴨・・P・・
    int m_maxHp;          // 譛螟ｧ菴灘鴨
    float mfAttack;       // 蝓ｺ譛ｬ謾ｻ謦・鴨・医Ξ繝吶Ν繧｢繝・・遲峨〒螟牙虚蜿ｯ閭ｽ・・
    float m_attackTimer{}; // 騾壼ｸｸ謾ｻ謦・・逋ｺ蟆・俣髫斐ｒ邂｡逅・☆繧九ち繧､繝槭・
    float m_AttackInterval{}; // 騾壼ｸｸ謾ｻ謦・・逋ｺ蟆・俣髫費ｼ医＠縺阪＞蛟､・・
    float m_AttackTimer_2{};  // 繧ｵ繝匁判謦・ｭ峨・逋ｺ蟆・俣髫斐ｒ邂｡逅・☆繧九ち繧､繝槭・
    float m_AttackInterval_2{}; // 繧ｵ繝匁判謦・・逋ｺ蟆・俣髫費ｼ医＠縺阪＞蛟､・・
    AttackMode m_attackMode;      // 迴ｾ蝨ｨ驕ｸ謚槭＆繧後※縺・ｋ謾ｻ謦・Δ繝ｼ繝・
    int m_specialCooldown;        // 蠢・ｮｺ謚縺悟・蠎ｦ謦・※繧九ｈ縺・↓縺ｪ繧九∪縺ｧ縺ｮ繧ｯ繝ｼ繝ｫ繝繧ｦ繝ｳ譎る俣・医ヵ繝ｬ繝ｼ繝謨ｰ・・
    CapsuleCollider* mpCollider;  // 蠖薙◆繧雁愛螳壹ｒ邂｡逅・☆繧九さ繝ｩ繧､繝繝ｼ・医き繝励そ繝ｫ迥ｶ/蜀・ｽ｢・・

    // 繝ｬ繝吶Ν繧｢繝・・縺ｨ邨碁ｨ灘､・・P・峨・邂｡逅・す繧ｹ繝・Β
    int m_level;          // 迴ｾ蝨ｨ縺ｮ繝ｬ繝吶Ν
    int m_xp;             // 迯ｲ蠕励＠縺溽ｵ碁ｨ灘､
    int m_xpNeeded;       // 谺｡縺ｮ繝ｬ繝吶Ν繧｢繝・・縺ｫ蠢・ｦ√↑邨碁ｨ灘､驥・
    int m_levelUpTimer;   // 繝ｬ繝吶Ν繧｢繝・・貍泌・・域枚蟄励・轤ｹ貊・↑縺ｩ・峨ｒ陦ｨ遉ｺ縺吶ｋ谿九ｊ譎る俣
    int m_spellGauge;     // 繧ｹ繝壹Ν繧ｫ繝ｼ繝臥匱蜍慕畑縺ｮ繧ｲ繝ｼ繧ｸ
    int m_maxSpellGauge;  // 繧ｲ繝ｼ繧ｸ縺ｮ譛螟ｧ蛟､

    int m_stunTimer;      // 繧ｹ繧ｿ繝ｳ・郁｡悟虚荳崎・・峨・谿九ｊ譎る俣・医ヵ繝ｬ繝ｼ繝謨ｰ・・

public:
    Player();
    virtual ~Player() override;

    // 繧ｲ繝ｼ繝髢句ｧ区凾繧・Μ繝医Λ繧､譎ゅ↓繝励Ξ繧､繝､繝ｼ縺ｮ繧ｹ繝・・繧ｿ繧ｹ繧貞・譛溽憾諷九↓謌ｻ縺・
    void Initialize();

    // 豈弱ヵ繝ｬ繝ｼ繝蜻ｼ縺ｰ繧後√く繝ｼ繝懊・繝牙・蜉帙↓繧医ｋ遘ｻ蜍募・逅・ｄ謾ｻ謦・愛螳壹↑縺ｩ繧定｡後≧
    void Update() override;

    // 豈弱ヵ繝ｬ繝ｼ繝蜻ｼ縺ｰ繧後√・繝ｬ繧､繝､繝ｼ縺ｮ逕ｻ蜒上ｄ逕ｻ髱｢荳翫・蜷・ｨｮ繧ｨ繝輔ぉ繧ｯ繝医ｒ謠冗判縺吶ｋ
    void Draw() override;

    // 繝励Ξ繧､繝､繝ｼ縺梧判謦・ｒ陦後≧髫帙・蜈ｷ菴鍋噪縺ｪ蠑ｾ縺ｮ逕滓・繧・・逅・ｒ陦後≧
    void Attack();
    // 繧ｲ繝・ち繝ｼ髢｢謨ｰ鄒､・亥､夜Κ縺九ｉ繝励Ξ繧､繝､繝ｼ縺ｮ迥ｶ諷九ｒ蜿門ｾ励☆繧九◆繧√・髢｢謨ｰ・・
    float GetX() const { return m_x; }
    float GetY() const { return m_y; }
    int GetHp() const { return m_hp; }
    int GetMaxHp() const { return m_maxHp; }
    AttackMode GetAttackMode() const { return m_attackMode; }
    int GetSpecialCooldown() const { return m_specialCooldown; }
    int GetLevel() const { return m_level; }
    int GetXp() const { return m_xp; }
    int GetXpNeeded() const { return m_xpNeeded; }
    int GetLevelUpTimer() const { return m_levelUpTimer; }
    int GetStunTimer() const { return m_stunTimer; }
    int GetSpellGauge() const { return m_spellGauge; }
    int GetMaxSpellGauge() const { return m_maxSpellGauge; }

    void Stun(int frames) { m_stunTimer = frames; }

    // 謨ｵ繧貞偵＠縺滓凾縺ｫ邨碁ｨ灘､繧定ｿｽ蜉縺励∬ｦ丞ｮ壼､縺ｫ驕斐＠縺溘ｉ繝ｬ繝吶Ν繧｢繝・・縺輔○繧句・逅・
    void AddXp(int amount);

    // 謨ｵ繧・雰縺ｮ蠑ｾ縺ｫ蠖薙◆縺｣縺滓凾縺ｫ繝繝｡繝ｼ繧ｸ繧貞女縺代？P繧呈ｸ帙ｉ縺吝・逅・
    void TakeDamage(int damage);
    void Heal(int amount);

    // 蠖薙◆繧雁愛螳壹・繧､繝吶Φ繝医ワ繝ｳ繝峨Λ・井ｻ悶・繧ｪ繝悶ず繧ｧ繧ｯ繝医→陦晉ｪ√＠縺溽椪髢薙↓蜻ｼ縺ｰ繧後ｋ・・
    virtual void OnEnter(Collider* collider, Collider* check) override;

    // 蠖薙◆繧雁愛螳壹・繧､繝吶Φ繝医ワ繝ｳ繝峨Λ・井ｻ悶・繧ｪ繝悶ず繧ｧ繧ｯ繝医→驥阪↑縺｣縺ｦ縺・ｋ髢捺ｯ弱ヵ繝ｬ繝ｼ繝蜻ｼ縺ｰ繧後ｋ・・
    virtual void OnTrigger(Collider* collider, Collider* check) override;

    // 蠖薙◆繧雁愛螳壹・繧､繝吶Φ繝医ワ繝ｳ繝峨Λ・井ｻ悶・繧ｪ繝悶ず繧ｧ繧ｯ繝医→髮｢繧後◆迸ｬ髢薙↓蜻ｼ縺ｰ繧後ｋ・・
    virtual void OnExit(Collider* collider, Collider* check) override;
};
