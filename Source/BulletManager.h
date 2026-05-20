#pragma once
#include <vector>
#include"Bullet.h"


class BulletManager {

public:
    BulletManager();
    ~BulletManager();

    void Initialize();
    void Update();
    void Draw();

    // 弾を発射する（生成する）関数
    void SpawnBullet(float x, float y);

    // 当たり判定用に弾のリストを取得する関数
    const std::vector<Bullet*>& GetBullets() const { return m_bullets; }
private:
    std::vector<Bullet*> m_bullets; // 弾のリスト

};
