#pragma once
#include <list>
#include <vector>
#include <memory>
#include "Object2D.h"
#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"

/// @brief 2Dオブジェクトの生成、更新、描画、削除をまとめて管理するクラス
class ObjectManager
{
public:
    /// @brief オブジェクト管理クラスを生成する
    ObjectManager();

    /// @brief オブジェクト管理クラスを破棄する
    ~ObjectManager();

    /// @brief 管理中の全オブジェクトを描画する
    void Draw();

    /// @brief 管理中の全オブジェクトを更新する
    void Update();

    /// @brief 2Dオブジェクトを管理リストへ追加する
    /// @param object2D 追加するオブジェクト
    void AddObject(std::shared_ptr<Object2D> object2D);

    /// @brief 全ての2Dオブジェクトを削除する
    void DeleteAll2D();

    /// @brief 削除フラグが立っているオブジェクトを取り除く
    void DeleteAll2DIfNeeded();

    /// @brief 指定タグのオブジェクトを1つ取得する
    /// @param tag 検索するタグ
    /// @return std::shared_ptr<Object2D> 見つかったオブジェクト。なければnullptr
    std::shared_ptr<Object2D> GetObject2DByTag(Object2D::Tag2D tag);

    /// @brief 指定タグのオブジェクトを全て取得する
    /// @param tag 検索するタグ
    /// @return std::vector<std::shared_ptr<Object2D>> 見つかったオブジェクトの配列
    std::vector<std::shared_ptr<Object2D>> GetObject2DListByTag(Object2D::Tag2D tag);

    /// @brief 管理中のオブジェクト数を取得する
    /// @return size_t オブジェクト数
    size_t GetObjectCount() const { return object_2d_list_.size(); }

    /// @brief 管理中のオブジェクトリストを取得する
    /// @return const std::list<std::shared_ptr<Object2D>>& オブジェクトリスト
    const std::list<std::shared_ptr<Object2D>>& GetObjectList() const { return object_2d_list_; }

private:
    std::list<std::shared_ptr<Object2D>> object_2d_list_; ///< 管理中の2Dオブジェクト
    std::weak_ptr<Object2D> player_2d_;                  ///< プレイヤーへの弱参照

public:
    /// @brief 現在シーンのObjectManagerへオブジェクトを生成・登録する
    /// @tparam T 生成するオブジェクト型
    /// @tparam Args コンストラクタ引数の型
    /// @param args コンストラクタへ渡す引数
    /// @return std::weak_ptr<T> 生成したオブジェクトへの弱参照。登録できない場合は空
    template<typename T, typename... Args>
    static std::weak_ptr<T> Instantiate(Args&&... args);
};

template<typename T, typename... Args>
/// @brief eの処理を行う
/// @param args 引数
/// @return 戻り値
std::weak_ptr<T> ObjectManager::Instantiate(Args&&... args)
{
    if (!Master::sceneManager)
    {
        return std::weak_ptr<T>();
    }

    Scene* scene = Master::sceneManager->GetCurrentScene();
    if (scene == nullptr || scene->GetObjectManager() == nullptr)
    {
        return std::weak_ptr<T>();
    }

    auto obj = std::make_shared<T>(std::forward<Args>(args)...);
    scene->GetObjectManager()->AddObject(obj);
    return obj;
}
