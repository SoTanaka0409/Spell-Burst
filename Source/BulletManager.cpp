#include "BulletManager.h"
#include "Bullet.h"
#include <DxLib.h>

BulletManager::BulletManager()
{

}

BulletManager::~BulletManager() {
    // メモリの解放
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
    // 全ての弾を更新
    

    // 画面外に出て不要になった弾（isActive が false になったもの）をリストから削除する
    auto it = m_bullets.begin();
    while (it != m_bullets.end()) {
        if (!(*it)->IsActive()) {
            delete (*it);           // メモリを解放
            it = m_bullets.erase(it); // リストから除外
        } else {
            ++it;
        }
    }
}

void BulletManager::Draw() {
    // 全ての弾を描画
   
}

void BulletManager::SpawnBullet(float x, float y) {
    // 新しい弾を作ってリストに追加する
    Bullet* newBullet = new Bullet(x, y);
    m_bullets.push_back(newBullet);
}
