#pragma once
#ifndef NOMINMAX
#define NOMINMAX // Windows.hのmin/maxマクロ衝突を避ける
#endif
#include <memory>
#include "DxLib.h"

class ObjectManager;
class ColliderManager;

// 各ゲーム画面の共通基底クラス
class Scene
{
public:
    Scene();
    virtual ~Scene();

    virtual void Initialize() = 0;

    virtual void Update();

    virtual void Draw();

    virtual void Finalize() = 0;

    ObjectManager* GetObjectManager();
    ColliderManager* GetCollisionManager();

private:
    std::unique_ptr<ObjectManager> object_manager_;     // シーン内オブジェクトの管理
    std::unique_ptr<ColliderManager> collider_manager_; // シーン内コライダーの管理
};