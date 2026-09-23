#pragma once
#include "Character.h"

class CapsuleCollider;

/// @brief 通常敵・中ボス敵の移動、攻撃、死亡処理を管理するクラス
class Enemy : public Character
{
private:
	int enemy_type_;  ///< 敵タイプ。ステータスや攻撃パターンを切り替える
	int attack_timer_; ///< 攻撃間隔を管理するタイマー
	float target_x_;  ///< 移動目標のX座標
	float target_y_;  ///< 移動目標のY座標

	/// @brief 新しい移動目標を選ぶ
	void SelectNewTarget();

public:
	/// @brief 敵を生成する
	/// @param x 初期X座標
	/// @param y 初期Y座標
	/// @param enemyType 敵タイプ
	Enemy(float x, float y, int enemyType = 1);

	/// @brief 敵を破棄する
	virtual ~Enemy() override;

	/// @brief 敵の状態を毎フレーム更新する
	void Update() override;

	/// @brief 敵を描画する
	void Draw() override;

	/// @brief 敵タイプを取得する
	/// @return int 敵タイプ
	int GetEnemyType() const { return enemy_type_; }

	/// @brief 敵を削除対象にする
	virtual void Kill() override;

	/// @brief 敵の当たり判定半径を取得する
	/// @return float 当たり判定半径
	float GetRadius() const
	{
		// 敵タイプ4は中ボス扱いなので、通常敵より大きい当たり判定にする。
		if (enemy_type_ == 4) return 45.0f;
		return 15.0f;
	}

	/// @brief 他コライダーとの接触中処理を行う
	/// @param collider 自身のコライダー
	/// @param check 接触相手のコライダー
	virtual void OnTrigger(Collider* collider, Collider* check) override;

	/// @brief 敵の死亡処理を行う
	/// @details 削除フラグを立て、スコア・経験値・演出を発生させる。
	virtual void OnDeath() override;

	/// @brief 敵タイプに応じた攻撃パターンを更新する
	/// @details タイマーに応じて弾を生成する。
	void UpdateAttackPattern();

	/// @brief 敵スプライトを描画する
	void DrawEnemySprite();

	/// @brief 敵HPバーを描画する
	void DrawHpBar();
};