#include "Vector2.h"
#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <vector>

class Object2D;

// 当たり判定（コライダー）の基底クラス
// 親オブジェクトにアタッチされ、他コライダーとの衝突判定やイベント発火を管理する
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

    /*
     * 他のコライダーと接触した最初のフレームに呼ばれるイベント。
     * [入力] なし
     * [出力] なし
     * [副作用] 派生クラスの接触処理が実行される
     */
    virtual void OnEnter();

    /*
     * 他のコライダーと接触している間呼ばれるイベント。
     * [入力] なし
     * [出力] なし
     * [副作用] 継続的な接触処理が実行される
     */
    virtual void OnTrigger();

    /*
     * 他のコライダーとの接触が離れたフレームに呼ばれるイベント。
     * [入力] なし
     * [出力] なし
     * [副作用] 離脱時の処理が実行される
     */
    virtual void OnExit();

    /*
     * 衝突状態に応じて衝突リストを更新し、各種イベントを呼び出す。
     * [入力] check: 判定対象のコライダー, isHit: 現在衝突しているか
     * [出力] なし
     * [副作用] collision_list_が更新される
     */
    void HitCheck(Collider* check, bool isHit);

    // --- フラグ管理・ゲッター群 ---
    void SetDeleteFlag(bool flag) { delete_flag_ = flag; }

    // 削除フラグの状態を取得する
    bool IsDeleteFlag() { return delete_flag_; }

    // このコライダーを所有している親オブジェクトを取得する
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

    Vector2 position_;                      // コライダーの座標（中心点など）
    Vector2 position2_;
    float radius_;                         // コライダーの半径（円形やカプセル型の太さ）

    bool delete_flag_;                      // 削除フラグ（trueの場合、管理クラスによって破棄される）

protected:
    std::vector<Collider*> collision_list_;  // 現在衝突している（重なっている）他のコライダーのリスト
};
