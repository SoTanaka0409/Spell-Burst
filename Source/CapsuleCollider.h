#include "Vector2.h"
#pragma once
#include "Collider.h"
#include "Object2D.h"

// 2点間の線分と半径で表すカプセル型コライダー
class CapsuleCollider : public Collider
{
public:
    /*
     * カプセルコライダーを初期化する。
     * [入力] parent: 親オブジェクト, pos1: 始点, pos2: 終点, radius: 半径
     * [出力] なし
     * [副作用] コライダーのパラメータを設定する
     */
    CapsuleCollider(Object2D* parent, Vector2 pos1, Vector2 pos2, float radius);
	virtual ~CapsuleCollider();

    /*
     * 他のコライダーとのカプセル衝突判定を行う。
     * [入力] check: 判定対象のコライダー
     * [出力] なし
     * [副作用] 衝突時にHitCheckを呼び出す
     */
    void Update(Collider* check) override;

    /*
     * カプセル形状をデバッグ描画する。
     * [入力] なし
     * [出力] なし
     * [副作用] 画面に判定形状が描画される
     */
    void Draw() override;
};