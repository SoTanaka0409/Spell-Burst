#pragma once
#ifndef NOMINMAX
#define NOMINMAX // Windows.hのmin/maxマクロ衝突を避ける
#endif
#include <memory>
#include "DxLib.h"

class ObjectManager;
class ColliderManager;

/// @brief 各ゲーム画面の共通基底クラス
class Scene
{
public:
    /// @brief シーンを生成する
    Scene();

    /// @brief シーンを破棄する
    virtual ~Scene();

    /// @brief シーン開始時の初期化を行う
    virtual void Initialize() = 0;

    /// @brief シーンを毎フレーム更新する
    virtual void Update();

    /// @brief シーンを描画する
    virtual void Draw();

    /// @brief シーン終了時の解放処理を行う
    virtual void Finalize() = 0;

    /// @brief シーン内のオブジェクト管理クラスを取得する
    /// @return ObjectManager* オブジェクト管理クラス
    ObjectManager* GetObjectManager();

    /// @brief シーン内のコライダー管理クラスを取得する
    /// @return ColliderManager* コライダー管理クラス
    ColliderManager* GetCollisionManager();

private:
    std::unique_ptr<ObjectManager> object_manager_;     ///< シーン内オブジェクトの管理
    std::unique_ptr<ColliderManager> collider_manager_; ///< シーン内コライダーの管理
};