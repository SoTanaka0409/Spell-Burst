#include <memory>
#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"

class ObjectManager;
class ColliderManager;

class Scene
{
public:
	Scene();
	virtual ~Scene();

    /*
     * シーン開始時に必要なリソース読み込みやオブジェクト生成を行う（派生クラスで実装）。
     * [入力] なし
     * [出力] なし
     * [副作用] シーンのリソースが確保される
     */
    virtual void Initialize() = 0;

    /*
     * オブジェクトのマネージャーおよび衝突判定マネージャーの更新処理を呼ぶ。
     * [入力] なし
     * [出力] なし
     * [副作用] ゲームオブジェクトが更新される
     */
    virtual void Update();

    /*
     * オブジェクトのマネージャーの描画処理を呼ぶ。
     * [入力] なし
     * [出力] なし
     * [副作用] 画面に描画される
     */
    virtual void Draw();

    /*
     * シーン終了時に画像や音などのリソース解放を行う（派生クラスで実装）。
     * [入力] なし
     * [出力] なし
     * [副作用] リソースが解放される
     */
    virtual void Finalize() = 0;

	ObjectManager* GetObjectManager();
	ColliderManager* GetCollisionManager();
	
private:
	std::unique_ptr<ObjectManager> object_manager_;
	std::unique_ptr<ColliderManager> collider_manager_;
};
