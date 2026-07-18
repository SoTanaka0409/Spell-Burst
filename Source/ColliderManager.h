#pragma once
#include <list>

class Collider;

// 生成された全コライダーを管理し、衝突判定と削除を行うクラス
class ColliderManager
{
public:
    ColliderManager();
    ~ColliderManager();

    /*
     * 管理している全コライダーの衝突判定を行う。
     * [入力] なし
     * [出力] なし
     * [副作用] 衝突が発生した場合、各コライダーのイベントが発火する
     */
    void Update();

    /*
     * 管理している全コライダーをデバッグ描画する。
     * [入力] なし
     * [出力] なし
     * [副作用] 画面にコライダー形状が描画される
     */
    void Draw();

    static ColliderManager* Getinstance_()
    {
        if (instance_ == nullptr)
        {
            instance_ = new ColliderManager();
        }//

        return instance_;
    }

    static void Finalize()
    {
        if (instance_ != nullptr)
        {
            delete instance_;
            instance_ = nullptr;
        }
    }

public:
    /*
     * 新しいコライダーを管理リストに追加する。
     * [入力] collider: 追加するコライダー
     * [出力] なし
     * [副作用] collider_list_に追加される
     */
    void AddCollider(Collider* collider);

    /*
     * 全てのコライダーをリストから削除し、メモリを解放する。
     * [入力] なし
     * [出力] なし
     * [副作用] collider_list_が空になる
     */
    void DeleteAllCollider();

    /*
     * 削除フラグが立っているコライダーをリストから除外し、破棄する。
     * [入力] なし
     * [出力] なし
     * [副作用] 対象コライダーが解放される
     */
    void DeleteAllColliderIfNeeded();

    /*
     * 指定されたコライダーを管理リストから除外する。メモリ解放は行わない。
     * [入力] collider: 除外するコライダー
     * [出力] なし
     * [副作用] collider_list_から要素が削除される
     */
    void RemoveCollider(Collider* collider);

    std::list<Collider*>& GetColliderList();

private:
    std::list<Collider*> collider_list_;

    static ColliderManager* instance_;
};