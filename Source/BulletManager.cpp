#include "BulletManager.h"
#include "Bullet.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <algorithm>

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager() {
    for (auto bullet : bullets) {
        delete bullet;
    }
    bullets.clear();
}

void BulletManager::Initialize() {
    for (auto bullet : bullets) {
        delete bullet;
    }
    bullets.clear();
}

void BulletManager::Update() {
    // Erase-Remove イディオムを使用して、アクティブでない弾を安全に一括削除
    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
            [](Bullet* bullet) {
                if (!bullet->IsActive()) {
                    delete bullet;
                    return true;
                }
                return false;
            }),
        bullets.end());
}

void BulletManager::Draw() {
   
}

void BulletManager::SpawnBullet(float x, float y) {
    bullets.push_back(new Bullet(x, y, 1));
}
