#pragma once
#include "Character.h"
#include "Barrier.h"

class SpecialBullet;

class Player : public Character
{
public:
    static int kSelectedCharacterType; // 1: Normal, 2: Girl, 3: Old
    
    enum AttackMode
    {
        kAttackModeMelee,   // 近接攻撃（ナイフ等）
        kAttackModeSpecial  // 必殺技（クールダウンあり）
    };

private:
    float attack;           // 基本攻撃力（レベルアップ等で変動可能）
    float attack_timer_{};    // 通常攻撃の発射間隔を管理するタイマー
    float attack_interval_{}; // 通常攻撃の発射間隔（しきい値）
    float attack_timer2_{};  // サブ攻撃等の発射間隔を管理するタイマー
    float attack_interval2_{}; // サブ攻撃の発射間隔（しきい値）
    float barrier_count_{};
    AttackMode attack_mode_;  // 現在選択されている攻撃モード
    int special_cooldown_;    // 必殺技が再度撃てるようになるまでのクールダウン時間（フレーム数）
	Barrier* barrier_; // プレイヤーが展開するバリアオブジェクトへのポインタ（必要に応じて使用）

    // レベルアップと経験値（XP）の管理システム
    int level_;          // 現在のレベル
    int xp_;             // 獲得した経験値
    int xp_needed_;       // 次のレベルアップに必要な経験値量
    int level_up_timer_;   // レベルアップ演出（文字の点滅など）を表示する残り時間
    int spell_gauge_;     // スペルカード発動用のゲージ
    int max_spell_gauge_;  // ゲージの最大値

public:
    Player();
    virtual ~Player() override;

    Barrier* GetBarrier() const { return barrier_; }
    void Initialize();

    void Update() override;
    void Draw() override;

    void Attack();
    void Barrier();

    // ゲッター関数群
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