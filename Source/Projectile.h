#pragma once
#include "Object2D.h"
#include "Vector2.h"

class CapsuleCollider;
class Collider;

// 弾・レーザーなど、移動してダメージを与えるオブジェクトの基底クラス
class Projectile : public Object2D
{
protected:
    Vector2 dir_;              // 進行方向
    float speed_;              // 速度
    int damage_;               // ダメージ
    bool is_active_;           // 有効状態
    CapsuleCollider* collider_; // 当たり判定

public:
    /*
     * 弾を初期化する。
     * [入力] pos: 初期座標, dir: 進行方向, speed: 速度, damage: ダメージ
     * [出力] なし
     * [副作用] コライダーが生成される
     */
    Projectile(Vector2 pos, Vector2 dir, float speed, int damage);
    virtual ~Projectile() override;

    /*
     * 弾の座標とコライダー位置を更新する。
     * [入力] なし
     * [出力] なし
     * [副作用] 位置が変化する
     */
    virtual void Update() override;

    virtual void Draw() override;

    virtual void OnTrigger(Collider* collider, Collider* check) override;

    bool IsActive() const { return is_active_; }
    int GetDamage() const { return damage_; }
    Vector2 GetDir() const { return dir_; }
    void SetDir(Vector2 dir) { dir_ = dir; }

    /*
     * 弾を無効化し、削除対象にする。
     * [入力] なし
     * [出力] なし
     * [副作用] is_active_をfalseにし、コライダーにも削除フラグを立てる
     */
    virtual void Kill();

    /*
     * 弾が画面外に出たかを判定する。
     * [入力] margin: 判定の余白
     * [出力] 画面外ならtrue
     * [副作用] なし
     */
    bool IsOutOfBounds(float margin = 50.0f) const;
};