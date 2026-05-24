#pragma once
#include "Object2D.h"
#include"Barrier.h"
class CapsuleCollider;

// プレイヤー（操作キャラクター）のデータや振る舞いを管理するクラス
// Object2Dを継承し、画面上の描画や当たり判定を持っています。
class Player : public Object2D
{
public:
    // プレイヤーの攻撃方法を定義する列挙型
    enum AttackMode
    {
        AttackMode_Melee,   // 近接攻撃（ナイフ等）
        AttackMode_Special  // 必殺技（クールダウンあり）
    };

private:
    float m_speed;            // プレイヤーの移動速度
    int m_hp;                 // 現在の体力（HP）
    int m_maxHp;              // 最大体力
    float mfAttack;           // 基本攻撃力（レベルアップ等で変動可能）
    float m_attackTimer{};    // 通常攻撃の発射間隔を管理するタイマー
    float m_AttackInterval{}; // 通常攻撃の発射間隔（しきい値）
    float m_AttackTimer_2{};  // サブ攻撃等の発射間隔を管理するタイマー
    float m_AttackInterval_2{}; // サブ攻撃の発射間隔（しきい値）
    float m__BarrierCount{};
    AttackMode m_attackMode;  // 現在選択されている攻撃モード
    int m_specialCooldown;    // 必殺技が再度撃てるようになるまでのクールダウン時間（フレーム数）
    CapsuleCollider* mpCollider; // 当たり判定を管理するコライダー（カプセル状/円形）
	Barrier* mpBarrier; // プレイヤーが展開するバリアオブジェクトへのポインタ（必要に応じて使用）


    // レベルアップと経験値（XP）の管理システム
    int m_level;          // 現在のレベル
    int m_xp;             // 獲得した経験値
    int m_xpNeeded;       // 次のレベルアップに必要な経験値量
    int m_levelUpTimer;   // レベルアップ演出（文字の点滅など）を表示する残り時間
    int m_spellGauge;     // スペルカード発動用のゲージ
    int m_maxSpellGauge;  // ゲージの最大値

    int m_stunTimer;      // スタン（行動不能）の残り時間（フレーム数）

public:
    Player();
    virtual ~Player() override;

    // ゲーム開始時やリトライ時にプレイヤーのステータスを初期状態に戻す
    void Initialize();

    // 毎フレーム呼ばれ、キーボード入力による移動処理や攻撃判定などを行う
    void Update() override;

    // 毎フレーム呼ばれ、プレイヤーの画像や画面上の各種エフェクトを描画する
    void Draw() override;

    // プレイヤーが攻撃を行う際の具体的な弾の生成や処理を行う
    void Attack();
    void Bariier();

    // ゲッター関数群（外部からプレイヤーの状態を取得するための関数）
    float GetX() const { return mvPosition.x; }
    float GetY() const { return mvPosition.y; }
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

    // 敵を倒した時に経験値を追加し、規定値に達したらレベルアップさせる処理
    void AddXp(int amount);

    // 敵や敵の弾に当たった時にダメージを受け、HPを減らす処理
    void TakeDamage(int damage);

    // 当たり判定のイベントハンドラ（他のオブジェクトと衝突した瞬間に呼ばれる）
    virtual void OnEnter(Collider* collider, Collider* check) override;

    // 当たり判定のイベントハンドラ（他のオブジェクトと重なっている間、毎フレーム呼ばれる）
    virtual void OnTrigger(Collider* collider, Collider* check) override;

    // 当たり判定のイベントハンドラ（他のオブジェクトと離れた瞬間に呼ばれる）
    virtual void OnExit(Collider* collider, Collider* check) override;
};