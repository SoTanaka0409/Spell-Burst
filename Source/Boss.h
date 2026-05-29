#pragma once
#include "Object2D.h"

class CapsuleCollider;

// ボス用クラス（基底: Object2D）
// 残機（m_lives）やフェーズ移行時の無敵時間を管理し、弾幕パターンを切り替える
class Boss : public Object2D {
private:
    float m_speed; // ボスの移動速度
    int m_hp; // ボスの現在の体力（フェーズごと）
    int m_maxHp; // 現在のフェーズにおける最大体力
    bool m_isActive; // ボスが現在アクティブ（戦闘中）かどうか
    int m_bossType; // ボスの種類や行動パターンの識別子
    
    float m_targetX, m_targetY; // ボスが次に向かう移動目標座標
    
    int m_attackTimer; // 弾幕攻撃を発射するためのインターバル管理タイマー
    int m_patternIndex; // 現在実行中の攻撃パターンのインデックス

    bool m_isDying; // 死亡演出中かどうかのフラグ
    int m_deathTimer; // 死亡演出（爆発など）の進行を管理するタイマー
    
    int m_lives; // ボスの残りフェーズ数（残機）
    int m_invincibleTimer; // フェーズ移行時などの無敵時間タイマー
    int m_invincibleCycleTimer; // 無敵時の点滅エフェクト用タイマー
    
    CapsuleCollider* mpCollider; // 当たり判定用コライダー

public:
    Boss(float x, float y, int bossType = 3);
    virtual ~Boss() override;

    // [入力] なし
    // [出力] なし
    // [副作用] 座標の更新、被弾時の無敵状態管理、フェーズ毎の弾幕処理を行う
    void Update() override;

    // [入力] なし
    // [出力] なし
    // [副作用] 無敵点滅効果の適用や、死亡時の爆発エフェクトを描画する
    void Draw() override;

    int GetHp() const { return m_hp; }
    int GetMaxHp() const { return m_maxHp; }
    bool IsActive() const { return m_isActive; }
    int GetLives() const { return m_lives; }

    float GetX() const { return mvPosition.x; }
    float GetY() const { return mvPosition.y; }
    float GetRadius() const { return 80.0f; }

    // [入力] damage: ダメージ量
    // [出力] なし
    // [副作用] 無敵時間中でなければHPを減算し、0以下で次フェーズへ移行または死亡処理
    void TakeDamage(int damage);

    // [入力] なし
    // [出力] なし
    // [副作用] 死亡フラグ(m_isDying)を立て、消滅エフェクト用タイマーを開始する
    void Kill();

    // [入力] collider: 自身のコライダー, check: 相手のコライダー
    // [出力] なし
    // [副作用] プレイヤータグを検知した場合にダメージ処理を呼び出す
    virtual void OnTrigger(Collider* collider, Collider* check) override;

private:
    void ShootRadialBarrage();
    void ShootFanBarrage();
    void ShootTargetedBarrage();
    void ShootSimpleBarrage();
    void ShootBouncingBarrage();
    void ShootSpellCardBarrage();
    
    // [入力] なし
    // [出力] なし
    // [副作用] ボスの次のランダム移動先(m_targetX, m_targetY)を再計算する
    void SelectNewTarget();
};