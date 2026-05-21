#pragma once
#include "Object2D.h"

class CapsuleCollider;

// ボスキャラクターのデータや振る舞い、弾幕パターンを管理するクラス
class Boss : public Object2D {
private:
    float m_x, m_y;       // ボスの画面上のXY座標
    float m_speed;        // 移動速度
    int m_hp;             // 現在の体力
    int m_maxHp;          // 最大体力
    bool m_isActive;      // ボスが活動中かどうかのフラグ
    int m_bossType;       // ボスの種類（1〜3）
    
    // ランダム移動の目的地（ターゲット座標）
    float m_targetX, m_targetY;
    
    // 攻撃パターンと発射間隔を管理するタイマー
    int m_attackTimer;
    int m_patternIndex;

    // 撃破された際の死亡演出を管理するステータスとタイマー
    bool m_isDying;
    int m_deathTimer;
    
    // フェーズ（残機）と無敵時間を管理する変数
    int m_lives;
    int m_invincibleTimer;
    
    CapsuleCollider* mpCollider;

public:
    Boss(float x, float y, int bossType = 3);
    virtual ~Boss() override;

    // 毎フレーム呼ばれ、移動処理や攻撃処理、死亡時の演出を行う
    void Update() override;

    // 毎フレーム呼ばれ、ボスの画像や被ダメージ時の点滅効果を描画する
    void Draw() override;

    int GetHp() const { return m_hp; }
    int GetMaxHp() const { return m_maxHp; }
    bool IsActive() const { return m_isActive; }
    int GetLives() const { return m_lives; }

    float GetX() const { return m_x; }
    float GetY() const { return m_y; }
    float GetRadius() const { return 80.0f; }

    // プレイヤーの攻撃を受けた際に呼ばれるダメージ処理
    void TakeDamage(int damage);

    // ボスを完全に消滅させる処理
    void Kill();

    // 他のオブジェクトと重なっている時の処理（弾との当たり判定）
    virtual void OnTrigger(Collider* collider, Collider* check) override;

private:
    // ボスの弾幕パターン処理群
    void ShootRadialBarrage();    // 全方位（放射状）への弾幕
    void ShootFanBarrage();       // 扇状（前方広範囲）への弾幕
    void ShootTargetedBarrage();  // プレイヤーを狙う自機狙い弾幕
    void ShootSimpleBarrage();    // タイプ1用の単純な弾
    void ShootBouncingBarrage();  // タイプ2用の反射弾
    
    // 次のランダム移動の目的地を決定する
    void SelectNewTarget();
};
