#include "Vector2.h"
#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <vector>

class Object2D;

// 当たり判定（コライダー）の基底クラス
// 各オブジェクトに取り付けられ、他コライダーとの接触状態とイベントを管理する。
class Collider
{
public:
    /*
     * コライダーの初期化と親オブジェクトの登録を行う。
     * [入力] parent: このコライダーを所有する親オブジェクト
     * [出力] なし
     * [副作用] 親オブジェクトのポインタを保持する
     */
    Collider(Object2D* parent);
    virtual ~Collider();

    /*
     * 他のコライダーとの具体的な衝突計算を行う。
     * [入力] check: 判定対象となる他のコライダー
     * [出力] なし
     * [副作用] 衝突が検知された場合、HitCheckを呼び出す
     */
    virtual void Update(Collider* check);

    /*
     * コライダーの形状をデバッグ用に描画する。
     * [入力] なし
     * [出力] なし
     * [副作用] 画面に描画される
     */
    virtual void Draw();

    // 他のコライダーと接触した最初のフレームに呼ばれる。
    virtual void OnEnter();

    // 他のコライダーと接触している間、毎フレーム呼ばれる。
    virtual void OnTrigger();

    // 他のコライダーとの接触が離れたフレームに呼ばれる。
    virtual void OnExit();

    /*
     * 衝突状態に応じて衝突リストを更新し、各種イベントを呼び出す。
     * [入力] check: 判定対象のコライダー, isHit: 現在衝突しているか
     * [出力] なし
     * [副作用] collision_list_が更新される
     */
    void HitCheck(Collider* check, bool isHit);

    void SetDeleteFlag(bool flag) { delete_flag_ = flag; }

    bool IsDeleteFlag() { return delete_flag_; }

    Object2D* GetParentObject()
    {
        return parent_object_;
    }

    void InvalidateParent()
    {
        parent_object_ = nullptr;
    }

    /*
     * 衝突リストから指定されたコライダーを取り除く。
     * [入力] collider: 削除するコライダー
     * [出力] なし
     * [副作用] collision_list_から要素が削除される
     */
    void RemoveCollision(Collider* collider);

    const std::vector<Collider*>& GetCollisionList() const { return collision_list_; }

public:
    Object2D* parent_object_;

    Vector2 position_;   // コライダーの中心座標など
    Vector2 position2_;  // カプセルなどで使う2点目の座標
    float radius_;       // 円・カプセルなどの半径

    bool delete_flag_;   // 管理クラスから削除するためのフラグ

protected:
    std::vector<Collider*> collision_list_; // 現在接触しているコライダーのリスト
};