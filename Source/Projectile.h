#pragma once
#include "Object2D.h"
#include "Vector2.h"

class CapsuleCollider;
class Collider;

// 全ての弾（Bullet）の基底クラス
class Projectile : public Object2D
{
protected:
    Vector2 dir_;              // 進行方向（正規化ベクトル）または移動ベクトル
    float speed_;               // 速度
    int damage_;                // ダメージ
    bool is_active_;             // 有効フラグ
    CapsuleCollider* collider_; // 当たり判定コライダー

public:
    /*
     * 弾の初期化を行う。
     * [入力] pos: 初期座標, dir: 進行方向, speed: 速度, damage: ダメージ
     * [出力] なし
     * [副作用] コライダーが生成される
     */
    Projectile(Vector2 pos, Vector2 dir, float speed, int damage);
    virtual ~Projectile() override;

    /*
     * 弾の座標やコライダーの位置を毎フレーム更新する。
     * [入力] なし
     * [出力] なし
     * [副作用] コライダーの座標が更新される
     */
    virtual void Update() override;

    virtual void Draw() override;

    virtual void OnTrigger(Collider* collider, Collider* check) override;

    // --- ゲッター・セッター ---
    bool IsActive() const { return is_active_; }
    int GetDamage() const { return damage_; }
    Vector2 GetDir() const { return dir_; }
    void SetDir(Vector2 dir) { dir_ = dir; }

    /*
     * 弾を無効化し、自身とコライダーの削除フラグを立てる。
     * [入力] なし
     * [出力] なし
     * [副作用] is_active_がfalseになり削除される
     */
    virtual void Kill();

    /*
     * 弾が画面外に出たかを判定する。
     * [入力] margin: 判定のゆとりマージン
     * [出力] 画面外に出たかどうか
     * [副作用] なし
     */
    bool IsOutOfBounds(float margin = 50.0f) const;
};
