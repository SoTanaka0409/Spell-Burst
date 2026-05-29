#pragma once
#include "Object2D.h"

class CapsuleCollider;

// 敵キャラクターの基底クラス（Object2D継承）
// 敵の種類ごとの行動パターンやHP、プレイヤー弾との衝突判定を管理する
class Enemy : public Object2D {
private:
    float m_speed; // 敵キャラクターの移動速度
    bool m_isActive; // 画面内に存在し活動状態にあるかどうかのフラグ
    int m_hp; // 現在の体力値
    int m_maxHp; // 体力の最大値（描画用）
    CapsuleCollider* mpCollider; // 当たり判定用コライダー

    int m_enemyType;      // 敵の種別（外見や行動パターンを決定）
    int m_attackTimer;    // 弾を発射するまでのインターバルタイマー

    float m_targetX, m_targetY; // ランダム移動時の目的地座標
    void SelectNewTarget();     

public:
    Enemy(float x, float y, int enemyType = 1);
    virtual ~Enemy() override;

    // [入力] なし
    // [出力] なし
    // [副作用] 敵の移動処理、画面外判定による削除、弾の発射タイマー更新を行う
    void Update() override;

    // [入力] なし
    // [出力] なし
    // [副作用] 敵のスプライト（敵種別に応じた画像や図形）およびHPバーを描画する
    void Draw() override;

    bool IsActive() const { return m_isActive; }
    int GetHp() const { return m_hp; }
    int GetEnemyType() const { return m_enemyType; }
    int GetMaxHp() const { return m_maxHp; }

    // [入力] damage: 受けるダメージ量
    // [出力] なし
    // [副作用] HPを減算し、0以下の場合は死亡エフェクトを発生させスコア等を加算する
    void TakeDamage(int damage);

    float GetX() const { return mvPosition.x; }
    float GetY() const { return mvPosition.y; }
    float GetRadius() const { 
        if (m_enemyType == 4) return 45.0f;
        return 15.0f; 
    }

    // [入力] なし
    // [出力] なし
    // [副作用] 敵オブジェクトの生存フラグをオフにし、マネージャーによる削除対象とする
    void Kill();

    // [入力] collider: 自身のコライダー, check: 相手のコライダー
    // [出力] なし
    // [副作用] 自機または自機弾との衝突を検知した場合にダメージ処理を呼び出す
    virtual void OnTrigger(Collider* collider, Collider* check) override;
};