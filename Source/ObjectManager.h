#pragma once
#include <list>
#include <vector>
#include <memory>
#include "Object2D.h"
#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"

// 2Dオブジェクトの生成、更新、描画、削除をまとめて管理するクラス
class ObjectManager
{
public:
    ObjectManager();
    ~ObjectManager();

    /*
     * 管理中の全オブジェクトを描画する。
     * [入力] なし
     * [出力] なし
     * [副作用] 各オブジェクトのDrawが呼ばれる
     */
    void Draw();

    /*
     * 管理中の全オブジェクトを更新する。
     * [入力] なし
     * [出力] なし
     * [副作用] 各オブジェクトのUpdateが呼ばれる
     */
    void Update();

    /*
     * 2Dオブジェクトを管理リストへ追加する。
     * [入力] object2D: 追加するオブジェクト
     * [出力] なし
     * [副作用] リストへオブジェクトが追加される
     */
    void AddObject(std::shared_ptr<Object2D> object2D);

    /*
     * 全ての2Dオブジェクトを削除する。
     * [入力] なし
     * [出力] なし
     * [副作用] 管理リストが空になる
     */
    void DeleteAll2D();

    /*
     * 削除フラグが立っているオブジェクトを取り除く。
     * [入力] なし
     * [出力] なし
     * [副作用] 対象オブジェクトがリストから除外される
     */
    void DeleteAll2DIfNeeded();

    /*
     * 指定タグのオブジェクトを1つ取得する。
     * [入力] tag: 検索するタグ
     * [出力] 見つかったオブジェクト。なければnullptr
     * [副作用] なし
     */
    std::shared_ptr<Object2D> GetObject2DByTag(Object2D::Tag2D tag);

    /*
     * 指定タグのオブジェクトを全て取得する。
     * [入力] tag: 検索するタグ
     * [出力] 見つかったオブジェクトの配列
     * [副作用] なし
     */
    std::vector<std::shared_ptr<Object2D>> GetObject2DListByTag(Object2D::Tag2D tag);

    size_t GetObjectCount() const { return object_2d_list_.size(); }

    const std::list<std::shared_ptr<Object2D>>& GetObjectList() const { return object_2d_list_; }

private:
    std::list<std::shared_ptr<Object2D>> object_2d_list_; // 管理中の2Dオブジェクト
    std::weak_ptr<Object2D> player_2d_; // プレイヤーへの弱参照

public:
    template<typename T, typename... Args>
    static std::weak_ptr<T> Instantiate(Args&&... args);
};

template<typename T, typename... Args>
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