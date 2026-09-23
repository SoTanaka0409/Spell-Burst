#include "Vector2.h"
#pragma once
#include "Collider.h"
#include "Object2D.h"

/// @brief 2点間の線分と半径で表すカプセル型コライダー
class CapsuleCollider : public Collider
{
public:
    /// @brief カプセルコライダーを初期化する
    /// @param parent 親オブジェクト
    /// @param pos1 始点
    /// @param pos2 終点
    /// @param radius 半径
    CapsuleCollider(Object2D* parent, Vector2 pos1, Vector2 pos2, float radius);

    /// @brief カプセルコライダーを破棄する
	virtual ~CapsuleCollider();

    /// @brief 他のコライダーとのカプセル衝突判定を行う
    /// @param check 判定対象のコライダー
    void Update(Collider* check) override;

    /// @brief カプセル形状をデバッグ描画する
    void Draw() override;
};