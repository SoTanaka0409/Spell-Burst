#include <memory>
#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"

class ObjectManager;
class ColliderManager;

// 全てのシーンの基底クラス
// オブジェクト管理と衝突判定管理のマネージャを標準で保持する
class Scene
{
public:
	Scene();
	virtual ~Scene();

    // [入力] なし
    // [出力] なし
    // [副作用] シーン開始時に必要なリソース読み込みやオブジェクト生成を行う（派生先で実装）
	virtual void Initialize() = 0;

    // [入力] なし
    // [出力] なし
    // [副作用] オブジェクトマネージャおよび衝突判定マネージャの更新処理を呼ぶ
	virtual void Update();

    // [入力] なし
    // [出力] なし
    // [副作用] オブジェクトマネージャの描画処理を呼ぶ
	virtual void Draw();

    // [入力] なし
    // [出力] なし
    // [副作用] シーン終了時に画像や音などのリソース解放を行う（派生先で実装）
	virtual void Finalize() = 0;

	ObjectManager* GetObjectManager() { return objectManager.get(); }
	ColliderManager* GetCollisionManager() { return colliderManager.get(); }
	
private:
	std::unique_ptr<ObjectManager> objectManager;
	std::unique_ptr<ColliderManager> colliderManager;
};