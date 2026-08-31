#pragma once
#include <list>

class Collider;

/// @brief 生成された全コライダーを管理し、衝突判定と削除を行うクラス
class ColliderManager
{
public:
    /// @brief コライダー管理クラスを生成する
    ColliderManager();

    /// @brief コライダー管理クラスを破棄する
    ~ColliderManager();

    /// @brief 管理している全コライダーの衝突判定を行う
    void Update();

    /// @brief 管理している全コライダーをデバッグ描画する
    void Draw();

    /// @brief コライダー管理クラスのインスタンスを取得する
    /// @return ColliderManager* シングルトンインスタンス
    static ColliderManager* Getinstance_()
    {
        if (instance_ == nullptr)
        {
            instance_ = new ColliderManager();
        }

        return instance_;
    }

    /// @brief コライダー管理クラスのインスタンスを解放する
    static void Finalize()
    {
        if (instance_ != nullptr)
        {
            delete instance_;
            instance_ = nullptr;
        }
    }

public:
    /// @brief 新しいコライダーを管理リストに追加する
    /// @param collider 追加するコライダー
    void AddCollider(Collider* collider);

    /// @brief 全てのコライダーをリストから削除し、メモリを解放する
    void DeleteAllCollider();

    /// @brief 削除フラグが立っているコライダーをリストから除外し、破棄する
    void DeleteAllColliderIfNeeded();

    /// @brief 指定されたコライダーを管理リストから除外する
    /// @param collider 除外するコライダー
    void RemoveCollider(Collider* collider);

    /// @brief 管理中のコライダーリストを取得する
    /// @return std::list<Collider*>& コライダーリスト
    std::list<Collider*>& GetColliderList();

private:
    std::list<Collider*> collider_list_; ///< 管理中のコライダーリスト
    static ColliderManager* instance_;   ///< シングルトンインスタンス
};