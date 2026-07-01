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
<<<<<<< HEAD


    for (auto it = bullets.begin(); it != bullets.end(); ) {
        if (!(*it)->IsActive()) {
            delete *it;
            it = bullets.erase(it);
        } else {
            it++;
        }
    }
=======
    // Erase-Remove イディオムを使用して、アクティブでない弾を安全に一括削除
    m_bullets.erase(
        std::remove_if(m_bullets.begin(), m_bullets.end(),
            [](Bullet* bullet) {
                if (!bullet->IsActive()) {
                    delete bullet;
                    return true;
                }
                return false;
            }),
        m_bullets.end());
>>>>>>> main
}

void BulletManager::Draw() {
   
}

void BulletManager::SpawnBullet(float x, float y) {
    bullets.push_back(new Bullet(x, y,1));
}
