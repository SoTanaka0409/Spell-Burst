#pragma once

namespace Config {
    // Player
    constexpr int kPlayerMaxHp = 15;
    constexpr float kPlayerSpeed = 5.0f;
    constexpr int kPlayerAttackInterval = 20;
    constexpr int kPlayerSpecialInterval = 60;
    constexpr int kPlayerXpNeeded = 5;

    // Boss Type 1
    constexpr int kBoss1MaxHp = 60;
    constexpr float kBoss1Speed = 1.5f;

    // Boss Type 2
    constexpr int kBoss2MaxHp = 80;
    constexpr float kBoss2Speed = 2.0f;

    // Boss Type 3 (Final)
    constexpr int kBoss3MaxHp = 150;
    constexpr float kBoss3Speed = 2.5f;
    constexpr int kBoss3Lives = 3;

    // Enemy
    constexpr int kEnemyMaxHp = 5;
    constexpr float kEnemySpeed = 2.0f;
    
    // Grid
    constexpr int kGridCellSize = 100;
}
