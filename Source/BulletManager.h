#pragma once
#include <vector>

class Bullet;

class BulletManager {
private:
    std::vector<Bullet*> m_bullets; // Bullet list

public:
    BulletManager();
    ~BulletManager();

    void Initialize();
    void Update();
    void Draw();

    void SpawnBullet(float x, float y);

    const std::vector<Bullet*>& GetBullets() const { return m_bullets; }
};
