#include "BulletManager.h"
#include "ObjectManager.h"
#include "Bullet.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <algorithm>

/// @brief BulletManager を生成する
BulletManager::BulletManager()
{
}

/// @brief 破棄処理を行う
BulletManager::~BulletManager()
{
    bullets.clear();
}

/// @brief 初期化処理を行う
void BulletManager::Initialize()
{
    bullets.clear();
}

/// @brief 毎フレームの更新処理を行う
void BulletManager::Update()
{
    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
            [](const std::weak_ptr<Bullet>& w)
            {
                if (auto bullet = w.lock())
                {
                    if (!bullet->IsActive())
                    {
                        return true;
                    }
                    return false;
                }
                return true; // if expired, remove it
            }),
        bullets.end());
}

/// @brief 描画処理を行う
void BulletManager::Draw()
{

}

/// @brief SpawnBullet を実行する
/// @param x x の値
/// @param y y の値
void BulletManager::SpawnBullet(float x, float y)
{
    bullets.push_back(ObjectManager::Instantiate<Bullet>(x, y, 1));
}





