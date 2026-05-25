#pragma once
#include "Object2D.h"

class CapsuleCollider;

// 繝?繧ｯ繧ｿ繝｜岨
// Object2D 繧?ｶ呎value縺?∫?髱「荳翫・謠行版繧・ｽ薙◆繧?鞁螳壹r謖√▲縺ｦ縺・∪縺吶・
class Player : public Object2D
{
public:
    // I'm sorry for the inconvenience, but I don't like it.
    enum AttackMode 
    {
        AttackMode_Melee,   // 1st Magnetic Circle, Medical Research, and Enthusiasm Society.
        AttackMode_Special  // Fly・Yoko・Medical・Consistency・Constipation・・
    };

private:
    float m_x, m_y;       // EncouragementΞ繧、繝、繝ｼ縺ｮ?髱「荳翫・XY蠎ｧ讓・
    float m_speed;        // Encouragement Ξ connection, connection, connection
    int m_hp;             // This is a duck...P...
    int m_maxHp;          // A wild duck
    float mfAttack;       // 蝓子譛謬款?・螟・MEDICINE Ξ?吶Ν繧"繝...遲峨〒螟芯蜿ｯ閭ｽ...
    float m_attackTimer{}; // I'm sorry for the inconvenience...
    float m_AttackInterval{}; // Sorry for the inconvenience...
    float m_AttackTimer_2{};  // 繧繧??・ｭ峨・逋ｺ蟆・髫斐邂｡逅・☆繧９ち繧、繝槭・
    float m_AttackInterval_2{}; // 繧ｵ??謦・・逋蟆・?髫髫 ＼Physician＠?saka＞蛟、・・・
    AttackMode m_attackMode;      // 迴蝨ｨ驕ku?槭&??※?・k欠?・Δ繝ｼ繝・
    int m_specialCooldown;        // 萢・ｪｺ謚縺迺?・蠎ｦ謦・※繧９h縺・↓?ｪ繧９∪縺ｧ縺
    CapsuleCollider* mpCollider;  // 薙◆繧??螳壹r邂。 ☆繧９さ繝ｩ繧、繝繝ｼ・?繧??繝繝ｫ迥か/蜀・ｽ``...

    // 繝繝吶Ν繧「繝...縺ｨ邨Goｨ灘､...P・峨・邂｡逅・す繧ｹ繝・Β
    int m_level;          // Please enter a question.
    int m_xp;             // Encourage the persimmons @?溽ａｨ灘
    int m_xpNeeded;       // 谺。
    int m_levelUpTimer;   // ?繝吶Ν繧'繝・貍secretion・轤兄?・轤KE貊・↑縺ｩ・?陦ｨｺ縺吶k谿9J?るま
    int m_spellGauge;     // 繧ｹ繝壹Ν繧ｫ繝ｼ繝臥匱蜍朕 Field 繧ｮｲｲ繝ｼ繧ｼ
    int m_maxSpellGauge;  // 繧い繝ｼ繧く縺ｮ譛螟ｧ蛟、

    int m_stunTimer;      // 繧?ｿ繝繝、遁。 Gokuenzaki... 谿 谿久??、medical ??繝繝繝謨...

public:
    Player();
    virtual ~Player() override;

    // 繧い繝ｼ繝 繧繧、Μ繝PhysicianΛ繧､?↓繝?繧､
    void Initialize();

    // 豈小繝ｬ繝ｼ繝荼ｼ縺ｰ繧after√ く繝ｼ繝懊・繝ANG・蜉
    void Update() override;

    // 豈小か?繝ｼ繝?ｼ縺ｰ繧after √・繝ｬ繧、繝、繝ｼ縺ｮ逕
    void Draw() override;

    // EncouragementΞ繧、繝、繝ｼ縺梧文謦・After r陦≧髫帙、蜈菽菴?縺ｪ蠑ｾ縺ｮ逕滓、繧・・逅・After ≧
    void Attack();
    // 繧い繝、ち繼髢「謨鄒、、亥、夜??９i繝?繧繧、繝
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

    // 謨繧田 detective＠縺滓凾縺?灘灘､繧? Soshu ?縺 encouragement∬ｦ丞
    void AddXp(int amount);

    // 繝繧繧ｮ蠑ｾ縺ｫ蠖薙◆縺”??凾縺繝繝.
    void TakeDamage(int damage);
    void Heal(int amount);

    // Isanagi 
    virtual void OnEnter(Collider* collider, Collider* check) override;

    // ◆ I love the goose, I'm a doctor, I'm in pain, I'm in pain, I'm in agony
    virtual void OnTrigger(Collider* collider, Collider* check) override;

    // Isanagi 
    virtual void OnExit(Collider* collider, Collider* check) override;
};
