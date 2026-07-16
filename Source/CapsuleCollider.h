#include "Vector2.h"
#pragma once
#include "Collider.h"
#include"Object2D.h"
class CapsuleCollider : public Collider
{
public:
    /*
     * カプセルコライダーの初期化を行う。
     * [入力] parent: 親オブジェクト, pos1: 始点, pos2: 終点, radius: 半径
     * [出力] なし
     * [副作用] コライダーのパラメータが設定され、管理リストに登録される
     */
    CapsuleCollider(Object2D* parent, Vector2 pos1, Vector2 pos2, float radius);
	virtual ~CapsuleCollider();

    /*
     * 他のコライダーとのカプセル衝突判定を行う。
     * [入力] check: 判定対象のコライダー
     * [出力] なし
     * [副作用] 衝突が検知された場合、親クラスのHitCheckを呼び出す
     */
    void Update(Collider* check) override;
    /*
     * カプセル形状をデバッグ用に描画する。
     * [入力] なし
     * [出力] なし
     * [副作用] 画面に描画される
     */
    void Draw() override;

	

};
