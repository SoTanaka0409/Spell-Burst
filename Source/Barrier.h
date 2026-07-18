#pragma once
#include "Object2D.h"

class Collider;

class Barrier : public Object2D
{
public:
	// アーキテクチャ設計：動的なメモリ確保（New）に伴うフラグメンテーションやリークを防止するため、コライダーの生成・破棄ライフサイクルは本クラスが完全にカプセル化して管理する。
	Barrier(float x, float y, float radius, Object2D::Tag2D obj);
	virtual ~Barrier();

	// レベルデザイン：一定時間ごとに「自動展開 ⇄ 消失」を繰り返す周期的なギミック（またはパッシブスキル）を制御するため、内部タイマーの進捗とコライダーの有効・無効状態を同期させる。
	virtual void Update() override;

	// UX仕様：バリアの視覚的な判定サイズと物理的な衝突判定（コライダーの半径）の不一致による「見た目は当たっていないのに防げた（またはその逆）」というプレイヤーの理不尽感を防ぐため、展開フラグと連動した厳密なエフェクト描画を行う。
	virtual void Draw() override;

	// バグ回避：多段ヒット判定を持つ高密度な弾幕オブジェクトと衝突した際、1フレーム内で処理が重複して耐久値が瞬時に削り切られる現象を防ぐため、コライダーの相互参照を検証して1オブジェクト1ヒットの制約を担保する。
	virtual void OnTrigger(Collider* collider, Collider* check) override;

	int GetHitCount() const { return hit_count_; }
	bool IsDeployed() const { return is_deployed_; }
	void SetDeployInterval(float v) { deploy_interval_ = v; }
	void SetActiveDuration(float v) { active_duration_ = v; }
	void SetPosition(Vector2 pos) { position_ = pos; }

private:
	float deploy_interval_; // レベルデザイン：再展開までの「危険な空白時間」を調整する猶予値
	float active_duration_; // レベルデザイン：敵の攻撃持続（レーザー等）に対抗する防衛時間
	float timer_;           // バグ回避：処理落ちによる展開周期のズレを抑止する蓄積カウンター
	float radius_;          // UX仕様：見た目のエフェクト半径と物理判定を完全一致させる基準値
	bool is_deployed_;      // アーキテクチャ設計：ロジック更新と描画システムを一元制御するマスターフラグ
	Collider* collider_;    // メモリ管理：Barrierの生存期と同期させリークを防ぐ動的ポインタ
	int hit_count_;         // レベルデザイン：バリア破壊トリガーやリザルト評価に用いる被弾カウンタ
};