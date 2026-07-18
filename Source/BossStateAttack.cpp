#include "BossStateAttack.h"
#include "Boss.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "ObjectManager.h"
#include "Enemy.h"
#include "GameScene.h"
#include "Master.h"
#include "SceneManager.h"
#include "ResultScene.h"

// 入力：boss = 状態を更新する対象のボスインスタンスポインタ
// 出力：なし
// 副作用：攻撃タイマーの進行、および規定フレーム到達時の直線弾幕（ShootSimpleBarrage）の発射トリガー
void BossStateSimple::Update(Boss* boss)
{
	attack_timer_++;
	if (attack_timer_ >= 60)
	{
		attack_timer_ = 0;
		boss->ShootSimpleBarrage();
	}
}

// 入力：boss = 状態を更新する対象のボスインスタンスポインタ
// 出力：なし
// 副作用：攻撃タイマーの進行、および規定フレーム到達時の反射弾幕（ShootBouncingBarrage）の発射トリガー
void BossStateBouncing::Update(Boss* boss)
{
	attack_timer_++;
	if (attack_timer_ >= 120)
	{
		attack_timer_ = 0;
		boss->ShootBouncingBarrage();
	}
}

// 入力：boss = 状態を更新する対象のボスインスタンスポインタ
// 出力：なし
// 副作用：無敵フラグの管理、護衛ザコ敵（Enemy）の動的生成、ランダム確率によるスペルカード発動、または3種弾幕のローテーション駆動
void BossStateFinal::Update(Boss* boss)
{
	invincible_cycle_timer_++;

	// ゲームバランス調整：ボスへのゴリ押し撃破を防ぎ、召喚された取り巻きを優先処理させる戦術的メリハリを生み出すための5秒（300f）周期無敵サイクル
	if (invincible_cycle_timer_ >= 300)
	{
		boss->SetInvincibleTimer(120);
		invincible_cycle_timer_ = 0;
		ObjectManager::Instantiate<Enemy>(boss->GetX() - 60.0f, boss->GetY() + 60.0f, 1);
		ObjectManager::Instantiate<Enemy>(boss->GetX() + 60.0f, boss->GetY() + 60.0f, 1);
	}

	attack_timer_++;
	if (attack_timer_ >= 100)
	{
		attack_timer_ = 0;

		bool used_spell_card = false;
		// レベルデザイン：最終ステージ（Stage 3）にふさわしい極限状態の緊迫感を演出するため、予期せぬタイミングで大技を繰り出す確率分岐
		if (GameScene::current_stage_ == 3)
		{
			if ((rand() % 100) < 20)
			{
				boss->ShootSpellCardBarrage();
				used_spell_card = true;
			}
		}

		if (!used_spell_card)
		{
			// UX仕様：ボスの攻撃行動パターンに明確な周期性（全方位→扇形→狙撃）を持たせ、プレイヤーが安地や回避ルートを学習しやすくするためのローテーション
			if (pattern_index_ == 0)
			{
				boss->ShootRadialBarrage();
			}
			else if (pattern_index_ == 1)
			{
				boss->ShootFanBarrage();
			}
			else
			{
				boss->ShootTargetedBarrage();
			}
			pattern_index_ = (pattern_index_ + 1) % 3;
		}
	}
}

// 入力：boss = 状態を更新する対象のボスインスタンスポインタ
// 出力：なし
// 副作用：死亡アニメーションタイマーの減算、およびタイマー終了時におけるボスアクターの完全消滅（Kill）処理
void BossStateDying::Update(Boss* boss)
{
	death_timer_--;
	if (death_timer_ <= 0)
	{
		// 演出仕様：撃破直後の大爆発パーティクルやフラッシュ効果が画面内で完了するのを待ってから、安全に実体をメモリ解放するための遅延Kill呼び出し
		boss->Kill();
	}
}