#pragma once
#include "Character.h"

class CapsuleCollider;

// 通常敵・中ボス敵の移動、攻撃、死亡処理を管理するクラス
class Enemy : public Character
{
private:
	int enemy_type_;   // 敵タイプ。ステータスや攻撃パターンを切り替える
	int attack_timer_; // 攻撃間隔を管理するタイマー

	float target_x_;   // 移動目標のX座標
	float target_y_;   // 移動目標のY座標

	void SelectNewTarget();

public:
	Enemy(float x, float y, int enemyType = 1);
	virtual ~Enemy() override;

	void Update() override;
	void Draw() override;

	int GetEnemyType() const { return enemy_type_; }

	virtual void Kill() override;

	float GetRadius() const
	{
		// 敵タイプ4は中ボス扱いなので、通常敵より大きい当たり判定にする。
		if (enemy_type_ == 4) return 45.0f;
		return 15.0f;
	}

	virtual void OnTrigger(Collider* collider, Collider* check) override;

	/*
	 * 敵の死亡処理を行う。
	 * [入力] なし
	 * [出力] なし
	 * [副作用] 削除フラグを立て、スコア・経験値・演出を発生させる
	 */
	virtual void OnDeath() override;

	/*
	 * 敵タイプに応じた攻撃パターンを更新する。
	 * [入力] なし
	 * [出力] なし
	 * [副作用] タイマーに応じて弾を生成する
	 */
	void UpdateAttackPattern();

	void DrawEnemySprite();

	void DrawHpBar();
};