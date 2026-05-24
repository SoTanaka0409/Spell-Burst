#include "RainbowWaveManager.h"
#include "RainbowBullet.h"
#include "Utility.h"

RainbowWaveManager::RainbowWaveManager(float x, float y)
    : Object2D(VGet(x, y, 0.0f))
    , m_lifeTimer(120) // 3 seconds duration
    , m_spawnInterval(10) // Spawn a row every 5 frames
    , m_spawnTimer(0)
{
    SetTag(Tag2D_PlayerBullet);
}

RainbowWaveManager::~RainbowWaveManager() {
}

void RainbowWaveManager::Update() {
    m_lifeTimer--;
    if (m_lifeTimer <= 0) {
        SetDeleteFlag(true);
        return;
    }

    m_spawnTimer++;
    if (m_spawnTimer >= m_spawnInterval) {
        m_spawnTimer = 0;
        
        // Spawn a horizontal line of colorful bullets at the bottom of the screen
        int numBullets = 10;
        float spacing = static_cast<float>(Utility::SCREEN_WIDTH) / static_cast<float>(numBullets);
        float startX = spacing / 2.0f;
        float yPos = static_cast<float>(Utility::SCREEN_HEIGHT) + 20.0f; // Just below screen

        for (int i = 0; i < numBullets; i++) {
            new RainbowBullet(startX + i * spacing, yPos);
        }
    }
}

void RainbowWaveManager::Draw() {
    // This manager is invisible, it just spawns bullets
}

void RainbowWaveManager::OnTrigger(Collider* collider, Collider* check) {
    // No collision for the manager itself
}
