#pragma once
#include <vector>

// 前方宣言
class Bullet;

class BulletManager {
private:
    std::vector<Bullet*> m_bullets; // 弾のリスト

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
};
