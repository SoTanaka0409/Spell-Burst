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
    for (auto bullet : m_bullets) {
        delete bullet;
    }
    m_bullets.clear();
}

void BulletManager::Initialize() {
    for (auto bullet : m_bullets) {
        delete bullet;
    }
    m_bullets.clear();
}

void BulletManager::Update() {
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
}

void BulletManager::Draw() {
   
}

void BulletManager::SpawnBullet(float x, float y) {
    m_bullets.push_back(new Bullet(x, y,1));
}
