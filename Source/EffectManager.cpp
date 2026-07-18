#include "EffectManager.h"
#include "ObjectManager.h"
#include "ExplosionParticle.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <cstdlib>

// 入力：position=爆発の中心座標, count=生成するパーティクル総数, color=描画色, size=基準サイズ, speed=基準初速
// 出力：なし
// 副作用：ObjectManagerを介した、ランダムなベクトルと寿命を持つ爆発パーティクル（ExplosionParticle）の動的一括生成
void EffectManager::SpawnExplosion(Vector2 position, int count, int color, float size, float speed)
{
	for (int i = 0; i < count; i++)
	{
		float angle = static_cast<float>(rand() % 360) * DX_PI_F / 180.0f;

		// 演出仕様：すべての粒子が一斉に同じ速度で広がると不自然な「真円の輪」になってしまうため、初速にゆらぎを与えて泥臭い爆発の質感を表現
		float currentSpeed = speed * (0.5f + (rand() % 50) / 100.0f);

		// パフォーマンス理由：撃破ラッシュ時に数千個の粒子が画面内に滞留して処理落ち（描画ドローコール爆発）を起こさないよう、約0.5秒（20〜40f）の短命に設定
		int life = 20 + rand() % 20;

		// 演出仕様：破片の大小に個体差を設けることで、大粒の火花から火の粉までが混ざり合った視覚的な密度感と立体感をシミュレート
		float currentSize = size * (0.5f + (rand() % 50) / 100.0f);

		ObjectManager::Instantiate<ExplosionParticle>(position.x, position.y, currentSpeed, angle, color, life, currentSize);
	}
}