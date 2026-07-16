#pragma once
#include <vector>
#include <memory>

class Bullet;

// 設計ルール：ゲーム中に発射される無数の弾オブジェクトの生存期間を安全に監視し、更新・描画を一括制御するマネージャークラス
class BulletManager
{
private:
	// メモリ管理：弾の実体はObjectManagerが管理するため、参照先の消滅によるダングリングポインタ（不正アクセス）を防ぐ弱参照リスト
	std::vector<std::weak_ptr<Bullet>> bullets;

public:
	BulletManager();
	~BulletManager();

	// 入力：なし
	// 出力：なし
	// 副作用：前ウェーブなどの残弾の追跡をすべて解除し、追跡用配列をクリーンアップ
	void Initialize();

	// 入力：なし
	// 出力：なし
	// 副作用：生存中の弾の座標更新、およびすでに実体が消滅（expired）した弾のポインタをリストから除外
	void Update();

	// 入力：なし
	// 出力：なし
	// 副作用：生存している（ロックに成功した）弾のみを走査し、バックバッファへの描画関数を呼び出す
	void Draw();

	// 入力：x, y=弾を生成する初期の画面座標
	// 副作用：弾インスタンスの生成トリガーを引く（生成された実体の weak_ptr を追跡リストに追加する）
	void SpawnBullet(float x, float y);

	const std::vector<std::weak_ptr<Bullet>>& GetBullets() const { return bullets; }
};