#include "BulletManager.h"
#include "ObjectManager.h"
#include "Bullet.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <algorithm>

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
    bullets.clear();
}

void BulletManager::Initialize()
{
    bullets.clear();
}

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

void BulletManager::Draw()
{

}

void BulletManager::SpawnBullet(float x, float y)
{
    bullets.push_back(ObjectManager::Instantiate<Bullet>(x, y, 1));
}





