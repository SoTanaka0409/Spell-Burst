#pragma once
#include "Character.h"
#include <memory>
#include "Barrier.h"

class SpecialBullet;

class Player : public Character
{
public:
    static int kSelectedCharacterType; // 1: Normal, 2: Girl, 3: Old
    
    enum AttackMode
    {
        kAttackModeMelee,   // 霑第磁謾ｻ謦・ｼ医リ繧､繝慕ｭ会ｼ・
        kAttackModeSpecial  // 蠢・ｮｺ謚・医け繝ｼ繝ｫ繝繧ｦ繝ｳ縺ゅｊ・・
    };

private:
    float attack;           // 蝓ｺ譛ｬ謾ｻ謦・鴨・医Ξ繝吶Ν繧｢繝・・遲峨〒螟牙虚蜿ｯ閭ｽ・・
    float attack_timer_{};    // 騾壼ｸｸ謾ｻ謦・・逋ｺ蟆・俣髫斐ｒ邂｡逅・☆繧九ち繧､繝槭・
    float attack_interval_{}; // 騾壼ｸｸ謾ｻ謦・・逋ｺ蟆・俣髫費ｼ医＠縺阪＞蛟､・・
    float attack_timer2_{};  // 繧ｵ繝匁判謦・ｭ峨・逋ｺ蟆・俣髫斐ｒ邂｡逅・☆繧九ち繧､繝槭・
    float attack_interval2_{}; // 繧ｵ繝匁判謦・・逋ｺ蟆・俣髫費ｼ医＠縺阪＞蛟､・・
    float barrier_count_{};
    AttackMode attack_mode_;  // 迴ｾ蝨ｨ驕ｸ謚槭＆繧後※縺・ｋ謾ｻ謦・Δ繝ｼ繝・
    int special_cooldown_;    // 蠢・ｮｺ謚縺悟・蠎ｦ謦・※繧九ｈ縺・↓縺ｪ繧九∪縺ｧ縺ｮ繧ｯ繝ｼ繝ｫ繝繧ｦ繝ｳ譎る俣・医ヵ繝ｬ繝ｼ繝謨ｰ・・
	std::weak_ptr<Barrier> barrier_; // 繝励Ξ繧､繝､繝ｼ縺悟ｱ暮幕縺吶ｋ繝舌Μ繧｢繧ｪ繝悶ず繧ｧ繧ｯ繝医∈縺ｮ繝昴う繝ｳ繧ｿ・亥ｿ・ｦ√↓蠢懊§縺ｦ菴ｿ逕ｨ・・

    // 繝ｬ繝吶Ν繧｢繝・・縺ｨ邨碁ｨ灘､・・P・峨・邂｡逅・す繧ｹ繝・Β
    int level_;          // 迴ｾ蝨ｨ縺ｮ繝ｬ繝吶Ν
    int xp_;             // 迯ｲ蠕励＠縺溽ｵ碁ｨ灘､
    int xp_needed_;       // 谺｡縺ｮ繝ｬ繝吶Ν繧｢繝・・縺ｫ蠢・ｦ√↑邨碁ｨ灘､驥・
    int level_up_timer_;   // 繝ｬ繝吶Ν繧｢繝・・貍泌・・域枚蟄励・轤ｹ貊・↑縺ｩ・峨ｒ陦ｨ遉ｺ縺吶ｋ谿九ｊ譎る俣
    int spell_gauge_;     // 繧ｹ繝壹Ν繧ｫ繝ｼ繝臥匱蜍慕畑縺ｮ繧ｲ繝ｼ繧ｸ
    int max_spell_gauge_;  // 繧ｲ繝ｼ繧ｸ縺ｮ譛螟ｧ蛟､

public:
    Player();
    virtual ~Player() override;

    std::shared_ptr<Barrier> GetBarrier() const { return barrier_.lock(); }
    void Initialize();

    void Update() override;
    void Draw() override;

    void Attack();
    void RunBarrierAttack();

    // 繧ｲ繝・ち繝ｼ髢｢謨ｰ鄒､
    AttackMode GetAttackMode() const { return attack_mode_; }
    int GetSpecialCooldown() const { return special_cooldown_; }
    int GetLevel() const { return level_; }
    int GetXp() const { return xp_; }
    int GetXpNeeded() const { return xp_needed_; }
    int GetLevelUpTimer() const { return level_up_timer_; }
    int GetSpellGauge() const { return spell_gauge_; }
    int GetMaxSpellGauge() const { return max_spell_gauge_; }

    void AddXp(int amount);
    virtual void TakeDamage(int damage_) override;

    virtual void OnEnter(Collider* collider_, Collider* check) override;
    virtual void OnTrigger(Collider* collider_, Collider* check) override;
    virtual void OnExit(Collider* collider_, Collider* check) override;
};
