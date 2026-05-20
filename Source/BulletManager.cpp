#include "BulletManager.h"
#include "Bullet.h"
#include <DxLib.h>

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
   

    for (auto it = m_bullets.begin(); it != m_bullets.end(); ) {
        if (!(*it)->IsActive()) {
            delete *it;
            it = m_bullets.erase(it);
        } else {
            it++;
        }
    }
}

void BulletManager::Draw() {
   
}

void BulletManager::SpawnBullet(float x, float y) {
    m_bullets.push_back(new Bullet(x, y,1));
}
