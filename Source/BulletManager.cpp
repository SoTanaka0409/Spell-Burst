#include "BulletManager.h"
#include "Bullet.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"

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


    for (auto it = bullets.begin(); it != bullets.end(); ) {
        if (!(*it)->IsActive()) {
            delete *it;
            it = bullets.erase(it);
        } else {
            it++;
        }
    }
}

void BulletManager::Draw() {
   
}

void BulletManager::SpawnBullet(float x, float y) {
    bullets.push_back(new Bullet(x, y,1));
}
