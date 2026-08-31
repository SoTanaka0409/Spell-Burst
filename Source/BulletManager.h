#pragma once
#include <vector>
#include <memory>

class Bullet;

/// @brief プレイヤーが発射する通常弾をまとめて管理するクラス
class BulletManager
{
private:
	std::vector<std::weak_ptr<Bullet>> bullets; ///< ObjectManagerが所有する弾を追跡する弱参照リスト

public:
	/// @brief 弾管理クラスを生成する
	BulletManager();

	/// @brief 弾管理クラスを破棄する
	~BulletManager();

	/// @brief 弾リストを初期化する
	void Initialize();

	/// @brief 管理中の弾を更新し、無効になった弾をリストから取り除く
	void Update();

	/// @brief 管理中の弾を描画する
	void Draw();

	/// @brief 指定座標にプレイヤー弾を生成する
	/// @param x 生成X座標
	/// @param y 生成Y座標
	void SpawnBullet(float x, float y);

	/// @brief 管理中の弾リストを取得する
	/// @return const std::vector<std::weak_ptr<Bullet>>& 弾の弱参照リスト
	const std::vector<std::weak_ptr<Bullet>>& GetBullets() const { return bullets; }
};