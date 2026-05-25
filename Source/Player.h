#pragma once
#include "Object2D.h"
<<<<<<< HEAD

class CapsuleCollider;

// プレイヤー�E�操作キャラクター�E��EチE�EタめE��る�EぁE��管琁E��るクラス
// Object2Dを継承し、画面上�E描画めE��たり判定を持ってぁE��す、E
class Player : public Object2D
{
public:
    // プレイヤーの攻撁E��法を定義する列挙垁E
    enum AttackMode 
=======
#include"Barrier.h"
class CapsuleCollider;

// プレイヤー（操作キャラクター）のデータや振る舞いを管理するクラス
// Object2Dを継承し、画面上の描画や当たり判定を持っています。class SpecialBullet;

class Player : public Object2D
{
public:
    static int s_selectedCharacterType; // 1: Normal, 2: Girl, 3: Old
    
    // プレイヤーの攻撃方法を定義する列挙型
    enum AttackMode
>>>>>>> main
    {
        AttackMode_Melee,   // 近接攻撁E��ナイフ等！E
        AttackMode_Special  // 忁E��技�E�クールダウンあり�E�E
    };
<<<<<<< HEAD

private:
    float m_x, m_y;       // プレイヤーの画面上�EXY座樁E
    float m_speed;        // プレイヤーの移動速度
    int m_hp;             // 現在の体力�E�EP�E�E
    int m_maxHp;          // 最大体力
<<<<<<< HEAD
    float mfAttack;       // 基本攻撁E���E�レベルアチE�E等で変動可能�E�E
    float m_attackTimer{}; // 通常攻撁E�E発封E��隔を管琁E��るタイマ�E
    float m_AttackInterval{}; // 通常攻撁E�E発封E��隔（しきい値�E�E
    float m_AttackTimer_2{};  // サブ攻撁E���E発封E��隔を管琁E��るタイマ�E
    float m_AttackInterval_2{}; // サブ攻撁E�E発封E��隔（しきい値�E�E
    AttackMode m_attackMode;      // 現在選択されてぁE��攻撁E��ーチE
    int m_specialCooldown;        // 忁E��技が�E度撁E��るよぁE��なるまでのクールダウン時間�E�フレーム数�E�E
    CapsuleCollider* mpCollider;  // 当たり判定を管琁E��るコライダー�E�カプセル状/冁E���E�E
=======
    float mfAttack;       // 基本攻撃力（レベルアップ等で変動可能）
    float m_attackTimer{}; // 通常攻撃の発射間隔を管理するタイマー
    float m_AttackInterval{}; // 通常攻撃の発射間隔（しきい値）
    float m_AttackTimer_2{};  // サブ攻撃等の発射間隔を管理するタイマー
    float m_AttackInterval_2{}; // サブ攻撃の発射間隔（しきい値）
    AttackMode m_attackMode;      // 現在選択されている攻撃モード
    int m_specialCooldown;        // 必殺技が再度撃てるようになるまでのクールダウン時間（フレーム数）
    CapsuleCollider* mpCollider;  // 当たり判定を管理するコライダー（カプセル状/円形）
=======
    

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

>>>>>>> main
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca

    // レベルアチE�Eと経験値�E�EP�E��E管琁E��スチE��
    int m_level;          // 現在のレベル
    int m_xp;             // 獲得した経験値
    int m_xpNeeded;       // 次のレベルアチE�Eに忁E��な経験値釁E
    int m_levelUpTimer;   // レベルアチE�E演�E�E�文字�E点滁E��ど�E�を表示する残り時間
    int m_spellGauge;     // スペルカード発動用のゲージ
    int m_maxSpellGauge;  // ゲージの最大値

    int m_stunTimer;      // スタン�E�行動不�E�E��E残り時間�E�フレーム数�E�E

public:
    Player();
    virtual ~Player() override;

    // ゲーム開始時めE��トライ時にプレイヤーのスチE�Eタスを�E期状態に戻ぁE
    void Initialize();

    // 毎フレーム呼ばれ、キーボ�Eド�E力による移動�E琁E��攻撁E��定などを行う
    void Update() override;

    // 毎フレーム呼ばれ、�Eレイヤーの画像や画面上�E吁E��エフェクトを描画する
    void Draw() override;

    // プレイヤーが攻撁E��行う際�E具体的な弾の生�EめE�E琁E��行う
    void Attack();
<<<<<<< HEAD
    // ゲチE��ー関数群�E�外部からプレイヤーの状態を取得するため�E関数�E�E
=======
<<<<<<< HEAD
    // ゲッター関数群（外部からプレイヤーの状態を取得するための関数）
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca
    float GetX() const { return m_x; }
    float GetY() const { return m_y; }
=======
    void Bariier();

    // ゲッター関数群（外部からプレイヤーの状態を取得するための関数）
    float GetX() const { return mvPosition.x; }
    float GetY() const { return mvPosition.y; }
>>>>>>> main
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

    // 敵を倒した時に経験値を追加し、規定値に達したらレベルアチE�Eさせる�E琁E
    void AddXp(int amount);

    // 敵めE��の弾に当たった時にダメージを受け、HPを減らす�E琁E
    void TakeDamage(int damage);
    void Heal(int amount);

    // 当たり判定�Eイベントハンドラ�E�他�Eオブジェクトと衝突した瞬間に呼ばれる�E�E
    virtual void OnEnter(Collider* collider, Collider* check) override;

<<<<<<< HEAD
    // 当たり判定�Eイベントハンドラ�E�他�Eオブジェクトと重なってぁE��間毎フレーム呼ばれる�E�E
=======
<<<<<<< HEAD
    // 当たり判定のイベントハンドラ（他のオブジェクトと重なっている間毎フレーム呼ばれる）
=======
    // 当たり判定のイベントハンドラ（他のオブジェクトと重なっている間、毎フレーム呼ばれる）
>>>>>>> main
>>>>>>> 240f2f277102418da5ddb286e12d12d717854dca
    virtual void OnTrigger(Collider* collider, Collider* check) override;

    // 当たり判定�Eイベントハンドラ�E�他�Eオブジェクトと離れた瞬間に呼ばれる�E�E
    virtual void OnExit(Collider* collider, Collider* check) override;
<<<<<<< HEAD
};
=======
};
>>>>>>> main
