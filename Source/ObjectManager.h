#pragma once
#include <list>
#include <vector>
#include <memory>
#include "Object2D.h"

class ObjectManager
{
public:
    ObjectManager();
    ~ObjectManager();

    /*
     * 管理リストの全オブジェクトの描画処理を行う。
     * [入力] なし
     * [出力] なし
     * [副作用] 各オブジェクトが画面に描画される
     */
    void Draw();

    /*
     * 管理リストの全オブジェクトの更新処理を行う。
     * [入力] なし
     * [出力] なし
     * [副作用] 各オブジェクトの状態が更新される
     */
    void Update();

    /*
     * 2Dオブジェクトを管理リストに追加する。
     * [入力] object2D: 追加するオブジェクトのポインタ
     * [出力] なし
     * [副作用] リストにオブジェクトが追加される
     */
    void AddObject(std::shared_ptr<Object2D> object2D);

    /*
     * 全ての2Dオブジェクトを破棄する。
     * [入力] なし
     * [出力] なし
     * [副作用] 管理リストが空になる
     */
    void DeleteAll2D();

    /*
     * 削除フラグが立っているオブジェクトを破棄する。
     * [入力] なし
     * [出力] なし
     * [副作用] 該当するオブジェクトがリストから削除される
     */
    void DeleteAll2DIfNeeded();

    /*
     * 指定されたタグのオブジェクトを1つ検索して返す。
     * [入力] tag: 検索するタグ
     * [出力] 該当するオブジェクトのポインタ（なければnullptr）
     * [副作用] なし
     */
    std::shared_ptr<Object2D> GetObject2DByTag(Object2D::Tag2D tag);

    /*
     * 指定されたタグのオブジェクトを全て検索して返す。
     * [入力] tag: 検索するタグ
     * [出力] 該当する全オブジェクトのポインタ配列
     * [副作用] なし
     */
    std::vector<std::shared_ptr<Object2D>> GetObject2DListByTag(Object2D::Tag2D tag);

    // 管理しているオブジェクトの総数を取得する
    size_t GetObjectCount() const { return object_2d_list_.size(); }

    // IuWFNg?XgS???Q?擾i???????gpj
    // 全オブジェクトのリストを取得する
    const std::list<std::shared_ptr<Object2D>>& GetObjectList() const { return object_2d_list_; }

private:
    std::list<std::shared_ptr<Object2D>> object_2d_list_; // 2Dオブジェクトのリスト
    std::weak_ptr<Object2D> player_2d_; // プレイヤーのポインタ

public:
    template<typename T, typename... Args>
    static std::weak_ptr<T> Instantiate(Args&&... args);
};

#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"

template<typename T, typename... Args>
std::weak_ptr<T> ObjectManager::Instantiate(Args&&... args)
{
    auto obj = std::make_shared<T>(std::forward<Args>(args)...);
    Master::sceneManager->GetCurrentScene()->GetObjectManager()->AddObject(obj);
    return obj;
}
