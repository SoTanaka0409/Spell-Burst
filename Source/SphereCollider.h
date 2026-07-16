#pragma once
#include "Collider.h"

class SphereCollider : public Collider
{
public:
    /*
     * 球形コライダーの初期化を行う。
     * [入力] parent: 親オブジェクト, center: 中心座標, radius: 半径
     * [出力] なし
     * [副作用] コライダーのパラメータが設定され、管理リストに登録される
     */
    SphereCollider(Object2D* parent, Vector2 center, float radius);
	virtual ~SphereCollider();

    /*
     * 他のコライダーとの球形衝突判定を行う。
     * [入力] check: 判定対象のコライダー
     * [出力] なし
     * [副作用] 衝突が検知された場合、親クラスのHitCheckを呼び出す
     */
    void Update(Collider* check) override;
    /*
     * 円形をデバッグ用に描画する。
     * [入力] なし
     * [出力] なし
     * [副作用] 画面に描画される
     */
    void Draw() override;

	void OnEnter() override;
	void OnTrigger() override;
	void OnExit() override;

};
