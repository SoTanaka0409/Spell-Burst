#pragma once
#include "Object2D.h"
#include "Vector2.h"

class CapsuleCollider;
class Collider;

// 全ての弾（Bullet）の基底クラス
class Projectile : public Object2D {
protected:
    Vector2 m_dir;               // 進行方向（正規化ベクトル）または移動ベクトル
    float m_speed;               // 速度
    int m_damage;                // ダメージ
    bool m_isActive;             // 有効フラグ
    CapsuleCollider* mpCollider; // 当たり判定コライダー

public:
    // [入力] pos: 初期座標, dir: 進行方向, speed: 速度, damage: ダメージ
    Projectile(Vector2 pos, Vector2 dir, float speed, int damage);
    virtual ~Projectile() override;

    // [入力] なし
    // [出力] なし
    // [副作用] 基底クラスのUpdate。主にコライダーの座標更新などを行う
    virtual void Update() override;

    // [入力] なし
    // [出力] なし
    // [副作用] 描画処理（派生先で実装）
    virtual void Draw() override;

    // [入力] collider: 自身のコライダー, check: 相手のコライダー
    // [出力] なし
    // [副作用] 衝突時の処理（派生先で実装）
    virtual void OnTrigger(Collider* collider, Collider* check) override;

    // --- ゲッター・セッター ---
    bool IsActive() const { return m_isActive; }
    int GetDamage() const { return m_damage; }
    Vector2 GetDir() const { return m_dir; }
    void SetDir(Vector2 dir) { m_dir = dir; }

    // [入力] なし
    // [出力] なし
    // [副作用] 弾を無効化し、自身とコライダーの削除フラグを立てる
    virtual void Kill();

    // [入力] margin: 画面外判定のゆとりマージン
    // [出力] 画面外に完全に出たかどうか
    // [副作用] なし
    bool IsOutOfBounds(float margin = 50.0f) const;
};