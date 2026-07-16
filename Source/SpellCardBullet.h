#pragma once
#include "Projectile.h"

class CapsuleCollider;

// 設計ルール：プレイヤーの必殺技（スペルカード）発動時に生成され、時間差での自己分裂や広範囲爆発などの特殊挙動を持つ大型弾丸クラス
class SpellCardBullet : public Projectile
{
private:
	int life_timer_;                 // 画面外への逸脱に関わらず、発生から一定時間後に強制的に自己爆発・消滅させるための生存期間タイマー
	int state_;                      // 「直進」「静止・チャージ」「バースト（分裂拡散）」などのフェーズ進行を制御する、内部の挙動分岐ステート
	int burst_count_;                // 必殺技の爽快感を高めるため、大爆発の瞬間に周囲にまき散らす子弾の残り発射数（分裂回数）
	int burst_timer_;                // 子弾を一度にすべて射出せず、わずかに時間差（ディレイ）をつけて流れるように散布するための連射間隔カウンター

	// 副作用：当たり判定の瞬間的な超巨大化、および画面揺れ（AddScreenShake）と大爆発エフェクト（ExplosionParticle）のトリガー
	void Explode();

public:
	// 入力：x, y = 魔法陣や自機（Player）の手前から発射するための初期出現座標
	// 副作用：スペルカード弾専用の衝突判定（CapsuleCollider）の生成、および直進ベクトルの初期設定
	SpellCardBullet(float x, float y);
	virtual ~SpellCardBullet() override;

	// 入力：なし
	// 出力：なし
	// 副作用：一定時間直進した後に急停止し、チャージを経て周囲に小弾を連射（Explode/burst_timer_）する独自の物理・ステート更新
	virtual void Update() override;

	// 入力：なし
	// 出力：なし
	// 副作用：チャージ中のエネルギー収縮を表現する、サイン波を用いた弾頭モデルの拡縮スケーリングおよび極彩色ブレンド描画
	virtual void Draw() override;

	virtual void OnTrigger(Collider* collider, Collider* check) override;
};