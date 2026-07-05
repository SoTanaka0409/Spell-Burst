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
    // [入力] parent: このコライダーを所有する親オブジェクト（Object2D）
    // [出力] なし
    // [副作用] 親オブジェクトのポインタを保持し、初期化を行う
    Collider(Object2D* parent);
    virtual ~Collider();

    // [入力] check: 判定対象となる他のコライダー
    // [出力] なし
    // [副作用] 派生クラスにて実装。自身の座標更新や、対象コライダーとの具体的な衝突計算を行う
    virtual void Update(Collider* check);

    // [入力] なし
    // [出力] なし
    // [副作用] デバッグ用。コライダーの形状（円や線分など）を画面に描画する
    virtual void Draw();

    // [入力] なし
    // [出力] なし
    // [副作用] 他のコライダーと接触した最初のフレームに呼ばれる（OnCollisionEnter相当）
    virtual void OnEnter();

    // [入力] なし
    // [出力] なし
    // [副作用] 他のコライダーと接触している間、毎フレーム呼ばれる（OnCollisionStay/Trigger相当）
    virtual void OnTrigger();

    // [入力] なし
    // [出力] なし
    // [副作用] 他のコライダーとの接触が離れたフレームに呼ばれる（OnCollisionExit相当）
    virtual void OnExit();

    // [入力] check: 判定対象のコライダー, isHit: 現在衝突しているかどうか
    // [出力] なし
    // [副作用] 衝突状態に応じてmCollisionListを更新し、OnEnter / OnTrigger / OnExit を呼び出す
    void HitCheck(Collider* check, bool isHit);

    // --- フラグ管理・ゲッター群 ---
    // [入力] flag: 削除フラグ（trueで削除予定）
    // [出力] なし
    // [副作用] コライダーの削除フラグを更新する
    void SetDeleteFlag(bool flag) { delete_flag_ = flag; }

    // 削除フラグの状態を取得する
    bool IsDeleteFlag() { return delete_flag_; }

    // このコライダーを所有している親オブジェクトを取得する
    Object2D* GetParentObject()
    {
        return parentObject;
    }

    // [入力] なし
    // [出力] なし
    // [副作用] 親オブジェクトへのポインタを無効化する（親が破棄された際などに使用）
    void InvalidateParent()
    {
        parentObject = nullptr;
    }

    // [入力] collider_: 衝突リストから削除するコライダー
    // [出力] なし
    // [副作用] mCollisionListから指定されたコライダーを検索し、取り除く
    void RemoveCollision(Collider* collider_);

public:
    Object2D* parentObject;               // このコライダーを所有する親オブジェクト

    Vector2 position_;                      // コライダーの座標（中心点など）
    Vector2 position2;                     // コライダーの座標2（カプセル型の終点など、形状に応じて使用）
    float radius_;                         // コライダーの半径（円形やカプセル型の太さ）

    bool delete_flag_;                      // 削除フラグ（trueの場合、管理クラスによって破棄される）

protected:
    std::vector<Collider*> collision_list_;  // 現在衝突している（重なっている）他のコライダーのリスト
};