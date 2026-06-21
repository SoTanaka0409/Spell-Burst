#pragma once
#include "Character.h"
#include "Barrier.h"

class SpecialBullet;

class Player : public Character
{
public:
    static int s_selectedCharacterType; // 1: Normal, 2: Girl, 3: Old
    
    enum AttackMode
    {
        AttackMode_Melee,   // 近接攻撃（ナイフ等）
        AttackMode_Special  // 必殺技（クールダウンあり）
    };

private:
    float mfAttack;           // 基本攻撃力（レベルアップ等で変動可能）
    float m_attackTimer{};    // 通常攻撃の発射間隔を管理するタイマー
    float m_AttackInterval{}; // 通常攻撃の発射間隔（しきい値）
    float m_AttackTimer_2{};  // サブ攻撃等の発射間隔を管理するタイマー
    float m_AttackInterval_2{}; // サブ攻撃の発射間隔（しきい値）
    float m__BarrierCount{};
    AttackMode m_attackMode;  // 現在選択されている攻撃モード
    int m_specialCooldown;    // 必殺技が再度撃てるようになるまでのクールダウン時間（フレーム数）
	Barrier* mpBarrier; // プレイヤーが展開するバリアオブジェクトへのポインタ（必要に応じて使用）

    // レベルアップと経験値（XP）の管理システム
    int m_level;          // 現在のレベル
    int m_xp;             // 獲得した経験値
    int m_xpNeeded;       // 次のレベルアップに必要な経験値量
    int m_levelUpTimer;   // レベルアップ演出（文字の点滅など）を表示する残り時間
    int m_spellGauge;     // スペルカード発動用のゲージ
    int m_maxSpellGauge;  // ゲージの最大値

public:
    Player();
    virtual ~Player() override;

    Barrier* GetBarrier() const { return mpBarrier; }
    void Initialize();

    void Update() override;
    void Draw() override;

    void Attack();
    void Bariier();

    // ゲッター関数群
    AttackMode GetAttackMode() const { return m_attackMode; }
    int GetSpecialCooldown() const { return m_specialCooldown; }
    int GetLevel() const { return m_level; }
    int GetXp() const { return m_xp; }
    int GetXpNeeded() const { return m_xpNeeded; }
    int GetLevelUpTimer() const { return m_levelUpTimer; }
    int GetSpellGauge() const { return m_spellGauge; }
    int GetMaxSpellGauge() const { return m_maxSpellGauge; }

    void AddXp(int amount);
    virtual void TakeDamage(int damage) override;

    virtual void OnEnter(Collider* collider, Collider* check) override;
    virtual void OnTrigger(Collider* collider, Collider* check) override;
    virtual void OnExit(Collider* collider, Collider* check) override;
};