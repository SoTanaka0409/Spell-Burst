#pragma once
#include <vector>
#include <memory>

class Bullet;

// プレイヤーが発射する通常弾をまとめて管理するクラス
class BulletManager
{
private:
	std::vector<std::weak_ptr<Bullet>> bullets; // ObjectManagerが所有する弾を追跡する弱参照リスト

public:
	BulletManager();
	~BulletManager();

	/*
	 * 弾リストを初期化する。
	 * [入力] なし
	 * [出力] なし
	 * [副作用] 追跡用リストをクリアする
	 */
	void Initialize();

	/*
	 * 管理中の弾を更新し、無効になった弾をリストから取り除く。
	 * [入力] なし
	 * [出力] なし
	 * [副作用] 弾の座標更新と追跡リストの整理を行う
	 */
	void Update();

	/*
	 * 管理中の弾を描画する。
	 * [入力] なし
	 * [出力] なし
	 * [副作用] 有効な弾のみ画面に描画する
	 */
	void Draw();

	/*
	 * 指定座標にプレイヤー弾を生成する。
	 * [入力] x, y: 生成する画面座標
	 * [出力] なし
	 * [副作用] 弾を生成し、追跡リストへ追加する
	 */
	void SpawnBullet(float x, float y);

	const std::vector<std::weak_ptr<Bullet>>& GetBullets() const { return bullets; }
};