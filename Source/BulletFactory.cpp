#include "BulletFactory.h"
#include "ObjectManager.h"
#include "EnemyBullet.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"

// 入力：position=発射起点, baseAngle=基準回転角, count=放射総数, speed=初速, canReflect=壁反射フラグ, isStun=スタン属性付与フラグ, homingFrames=誘導持続時間, homingDelay=誘導開始遅延
// 出力：なし
// 副作用：ObjectManagerを介した、等間隔に配置された全方位弾（EnemyBullet）の大量一括生成
/// @brief SpawnCircleBullets を実行する
/// @param position position の値
/// @param baseAngle baseAngle の値
/// @param count count の値
/// @param speed speed の値
/// @param canReflect canReflect の値
/// @param isStun isStun の値
/// @param homingFrames homingFrames の値
/// @param homingDelay homingDelay の値
void BulletFactory::SpawnCircleBullets(Vector2 position, float baseAngle, int count, float speed, bool canReflect, bool isStun, int homingFrames, int homingDelay)
{
	if (count <= 0) return;

	// レベルデザイン：ボス戦の全方位波状攻撃において、配置の粗密による安地の偏りを防ぎ、完全な幾何学的均等性を持たせるための360度ステップ分割
	float step = (2.0f * DX_PI_F) / count;
	for (int i = 0; i < count; i++)
	{
		float angle = baseAngle + i * step;
		ObjectManager::Instantiate<EnemyBullet>(position, Vector2::FromAngle(angle), speed, canReflect, isStun, homingFrames, homingDelay);
	}
}

// 入力：position=発射起点, baseAngle=射撃中心基準角, count=ウェイ数（弾数）, spreadAngle=全体の最大拡散総角度（ラジアン）, speed=初速, 各種弾質フラグ群
// 出力：なし
// 副作用：ObjectManagerを介した、自機方向または指定方向を中心とする扇形拡散弾（EnemyBullet）の生成
/// @brief SpawnNWayBullets を実行する
/// @param position position の値
/// @param baseAngle baseAngle の値
/// @param count count の値
/// @param spreadAngle spreadAngle の値
/// @param speed speed の値
/// @param canReflect canReflect の値
/// @param isStun isStun の値
/// @param homingFrames homingFrames の値
/// @param homingDelay homingDelay の値
void BulletFactory::SpawnNWayBullets(Vector2 position, float baseAngle, int count, float spreadAngle, float speed, bool canReflect, bool isStun, int homingFrames, int homingDelay)
{
	if (count <= 0) return;
	if (count == 1)
	{
		ObjectManager::Instantiate<EnemyBullet>(position, Vector2::FromAngle(baseAngle), speed, canReflect, isStun, homingFrames, homingDelay);
		return;
	}

	// アルゴリズム設計：狙った方向（ターゲットベクトル）を完全にど真ん中に据え、奇数・偶数ウェイに関わらず左右対称な美しい扇形弾道を計算するための開始角オフセット
	float step = spreadAngle / (count - 1);
	float startAngle = baseAngle - spreadAngle / 2.0f;
	for (int i = 0; i < count; i++)
	{
		float angle = startAngle + i * step;
		ObjectManager::Instantiate<EnemyBullet>(position, Vector2::FromAngle(angle), speed, canReflect, isStun, homingFrames, homingDelay);
	}
}
