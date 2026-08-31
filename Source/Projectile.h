#pragma once
#include "Object2D.h"
#include "Vector2.h"

class CapsuleCollider;
class Collider;

/// @brief 弾・レーザーなど、移動してダメージを与えるオブジェクトの基底クラス
class Projectile : public Object2D
{
protected:
    Vector2 dir_;               ///< 進行方向
    float speed_;               ///< 速度
    int damage_;                ///< ダメージ
    bool is_active_;            ///< 有効状態を示すフラグ
    CapsuleCollider* collider_; ///< 当たり判定

public:
    /// @brief 弾を初期化する
    /// @param pos 初期座標
    /// @param dir 進行方向
    /// @param speed 速度
    /// @param damage ダメージ
    Projectile(Vector2 pos, Vector2 dir, float speed, int damage);

    /// @brief 弾を破棄する
    virtual ~Projectile() override;

    /// @brief 弾の座標とコライダー位置を更新する
    virtual void Update() override;

    /// @brief 弾を描画する
    virtual void Draw() override;

    /// @brief 他コライダーとの接触処理を行う
    /// @param collider 自身のコライダー
    /// @param check 接触相手のコライダー
    virtual void OnTrigger(Collider* collider, Collider* check) override;

    /// @brief 有効状態を取得する
    /// @return bool 有効ならtrue
    bool IsActive() const { return is_active_; }

    /// @brief ダメージ量を取得する
    /// @return int ダメージ量
    int GetDamage() const { return damage_; }

    /// @brief 進行方向を取得する
    /// @return Vector2 進行方向
    Vector2 GetDir() const { return dir_; }

    /// @brief 進行方向を設定する
    /// @param dir 新しい進行方向
    void SetDir(Vector2 dir) { dir_ = dir; }

    /// @brief 弾を無効化し、削除対象にする
    virtual void Kill();

    /// @brief 弾が画面外に出たかを判定する
    /// @param margin 判定の余白
    /// @return bool 画面外ならtrue
    bool IsOutOfBounds(float margin = 50.0f) const;
};