#pragma once
#include "Character.h"
#include "Barrier.h"

class SpecialBullet;

class Player : public Character
{
public:
    static int selectedCharacterType; // 1: Normal, 2: Girl, 3: Old
    
    enum AttackMode
    {
        AttackMode_Melee,   // 近接攻撃（ナイフ等）
        AttackMode_Special  // 必殺技（クールダウンあり）
    };

private:
    float attack;           // 基本攻撃力（レベルアップ等で変動可能）
    float attackTimer{};    // 通常攻撃の発射間隔を管理するタイマー
    float attackInterval{}; // 通常攻撃の発射間隔（しきい値）
    float attackTimer2{};  // サブ攻撃等の発射間隔を管理するタイマー
    float attackInterval2{}; // サブ攻撃の発射間隔（しきい値）
    float barrierCount{};
    AttackMode attackMode;  // 現在選択されている攻撃モード
    int specialCooldown;    // 必殺技が再度撃てるようになるまでのクールダウン時間（フレーム数）
	Barrier* barrier; // プレイヤーが展開するバリアオブジェクトへのポインタ（必要に応じて使用）

    // レベルアップと経験値（XP）の管理システム
    int level;          // 現在のレベル
    int xp;             // 獲得した経験値
    int xpNeeded;       // 次のレベルアップに必要な経験値量
    int levelUpTimer;   // レベルアップ演出（文字の点滅など）を表示する残り時間
    int spellGauge;     // スペルカード発動用のゲージ
    int maxSpellGauge;  // ゲージの最大値

public:
    Player();
    virtual ~Player() override;

    Barrier* GetBarrier() const { return barrier; }
    void Initialize();

    void Update() override;
    void Draw() override;

    void Attack();
    void Barrier();

    // ゲッター関数群
    AttackMode GetAttackMode() const { return attackMode; }
    int GetSpecialCooldown() const { return specialCooldown; }
    int GetLevel() const { return level; }
    int GetXp() const { return xp; }
    int GetXpNeeded() const { return xpNeeded; }
    int GetLevelUpTimer() const { return levelUpTimer; }
    int GetSpellGauge() const { return spellGauge; }
    int GetMaxSpellGauge() const { return maxSpellGauge; }

    void AddXp(int amount);
    virtual void TakeDamage(int damage) override;

    virtual void OnEnter(Collider* collider, Collider* check) override;
    virtual void OnTrigger(Collider* collider, Collider* check) override;
    virtual void OnExit(Collider* collider, Collider* check) override;
};