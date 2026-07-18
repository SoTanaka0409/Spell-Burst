#include "PlayerSpellParticle.h"
#include "ObjectManager.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Utility.h"
#include <cmath>
#include "Character.h"
#include "CapsuleCollider.h"

// 入力：pos = 発生初期座標, dir = 射出方向ベクトル, speed_ = 弾速
// 副作用：自機弾タグの付与、各種ステータス・3秒（180f）の生存寿命のセット、および専用コライダー（CapsuleCollider）の動的生成
PlayerSpellParticle::PlayerSpellParticle(Vector2 pos, Vector2 dir, float speed_)
	: Object2D(pos)
{
	SetTag(kTag2dPlayerBullet);
	this->position_ = pos;
	this->dir = dir.Normalized();
	this->speed_ = speed_;
	this->is_active_ = true;
	this->life_timer_ = 180;
	this->damage_ = 5;
	this->collider_ = new CapsuleCollider(this, this->position_, this->position_, 15.0f);
}

PlayerSpellParticle::~PlayerSpellParticle()
{
	if (collider_)
	{
		delete collider_;
		collider_ = nullptr;
	}
}

// 副作用：アクティブフラグの取り下げ、およびガベージクリーンアップ用の削除フラグの即時セット
void PlayerSpellParticle::Kill()
{
	is_active_ = false;
	SetDeleteFlag(true);
}

// 入力：なし
// 出力：なし
// 副作用：タイムスケールに同期した等速直線運動、寿命カウントダウン、および可動域逸脱時におけるオブジェクトの自動消滅フラグセット
void PlayerSpellParticle::Update()
{
	if (!is_active_) return;

	life_timer_--;
	if (life_timer_ <= 0)
	{
		is_active_ = false;
		SetDeleteFlag(true);
		return;
	}

	position_ += dir * (speed_ * Utility::time_scale_);

	if (position_.x < -50.0f || position_.x > Utility::kScreenWidth + 50.0f || position_.y < -50.0f || position_.y > Utility::kScreenHeight + 50.0f)
	{
		is_active_ = false;
		SetDeleteFlag(true);
		return;
	}

	if (collider_)
	{
		collider_->position_ = position_;
		collider_->position2_ = position_;
	}
}

// 入力：なし
// 出力：なし
// 副作用：残存寿命に応じた線形フェードアウト計算、および加算ブレンド（ADD）によるコア付き多重エネルギー球のバックバッファ描画
void PlayerSpellParticle::Draw()
{
	if (!is_active_) return;

	// 演出仕様：必殺技を構成する魔法の粒子としての儚さとエネルギー減衰を表現するため、寿命の減少（180fからゼロまで）に同期して光が滑らかにフェードアウトする輝度制御
	int alpha = (life_timer_ * 255) / 180;
	if (alpha > 255) alpha = 255;
	SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);

	// 視覚的フィードバック：外縁部をシアン（150, 255, 255）、中心を純白（255, 255, 255）の多重真円で加算合成することで、画面の暗い宇宙背景などでも埋もれない強いプラズマ発光感を演出
	DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 15, GetColor(150, 255, 255), TRUE);
	DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 8, GetColor(255, 255, 255), TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// 入力：collider = 自身を規定する当たり判定, check = 衝突検証の相手となるコライダー
// 出力：なし
// 副作用：敵（Enemy）に対する即時ダメージの適用、および接触した敵の通常弾（EnemyBullet）の強制消去処理
void PlayerSpellParticle::OnTrigger(Collider* collider, Collider* check)
{
	if (check != nullptr && check->GetParentObject() != nullptr)
	{
		if (check->GetParentObject()->GetTag() == kTag2dEnemy)
		{
			Character* enemy = dynamic_cast<Character*>(check->GetParentObject());
			if (enemy != nullptr)
			{
				enemy->TakeDamage(damage_);
			}
			Kill();
		}
		else if (check->GetParentObject()->GetTag() == kTag2dEnemyBullet)
		{
			// UX仕様：スペルカード（必殺技）の副次的効果。画面を埋め尽くす不快な敵弾をプレイヤーの放った粒子が物理的に「相殺・かき消す」ことで、火力を出しつつ安全地帯を切り開くボムとしての役割を保証
			check->GetParentObject()->SetDeleteFlag(true);
		}
	}
}