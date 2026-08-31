#include "Vector2.h"
#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <vector>

class Object2D;

/// @brief 当たり判定（コライダー）の基底クラス
/// @details 各オブジェクトに取り付けられ、他コライダーとの接触状態とイベントを管理する。
class Collider
{
public:
    /// @brief コライダーを初期化する
    /// @param parent このコライダーを所有する親オブジェクト
    Collider(Object2D* parent);

    /// @brief コライダーを破棄する
    virtual ~Collider();

    /// @brief 他のコライダーとの具体的な衝突計算を行う
    /// @param check 判定対象となる他のコライダー
    virtual void Update(Collider* check);

    /// @brief コライダーの形状をデバッグ用に描画する
    virtual void Draw();

    /// @brief 他のコライダーと接触した最初のフレームに呼ばれる
    virtual void OnEnter();

    /// @brief 他のコライダーと接触している間、毎フレーム呼ばれる
    virtual void OnTrigger();

    /// @brief 他のコライダーとの接触が離れたフレームに呼ばれる
    virtual void OnExit();

    /// @brief 衝突状態に応じて衝突リストを更新し、各種イベントを呼び出す
    /// @param check 判定対象のコライダー
    /// @param isHit 現在衝突しているか
    void HitCheck(Collider* check, bool isHit);

    /// @brief 削除フラグを設定する
    /// @param flag 削除対象ならtrue
    void SetDeleteFlag(bool flag) { delete_flag_ = flag; }

    /// @brief 削除フラグを取得する
    /// @return bool 削除対象ならtrue
    bool IsDeleteFlag() { return delete_flag_; }

    /// @brief 親オブジェクトを取得する
    /// @return Object2D* 親オブジェクト
    Object2D* GetParentObject()
    {
        return parent_object_;
    }

    /// @brief 親オブジェクト参照を無効化する
    void InvalidateParent()
    {
        parent_object_ = nullptr;
    }

    /// @brief 衝突リストから指定されたコライダーを取り除く
    /// @param collider 削除するコライダー
    void RemoveCollision(Collider* collider);

    /// @brief 現在接触しているコライダーリストを取得する
    /// @return const std::vector<Collider*>& 接触中コライダーリスト
    const std::vector<Collider*>& GetCollisionList() const { return collision_list_; }

public:
    Object2D* parent_object_; ///< 親オブジェクト
    Vector2 position_;        ///< コライダーの中心座標など
    Vector2 position2_;       ///< カプセルなどで使う2点目の座標
    float radius_;            ///< 円・カプセルなどの半径
    bool delete_flag_;        ///< 管理クラスから削除するためのフラグ

protected:
    std::vector<Collider*> collision_list_; ///< 現在接触しているコライダーのリスト
};