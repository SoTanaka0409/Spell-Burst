#pragma once
#include "Collider.h"

/// @brief 中心座標と半径で表す円形コライダー
class SphereCollider : public Collider
{
public:
    /// @brief 円形コライダーを初期化する
    /// @param parent 親オブジェクト
    /// @param center 中心座標
    /// @param radius 半径
    SphereCollider(Object2D* parent, Vector2 center, float radius);

    /// @brief 円形コライダーを破棄する
	virtual ~SphereCollider();

    /// @brief 他のコライダーとの円形衝突判定を行う
    /// @param check 判定対象のコライダー
    void Update(Collider* check) override;

    /// @brief 円形コライダーをデバッグ描画する
    void Draw() override;

	/// @brief 接触開始時の処理を行う
	void OnEnter() override;

	/// @brief 接触中の処理を行う
	void OnTrigger() override;

	/// @brief 接触終了時の処理を行う
	void OnExit() override;
};