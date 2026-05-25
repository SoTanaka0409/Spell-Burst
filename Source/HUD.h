#pragma once

class Player;
class Boss;
class EnemyManager;

class HUD {
public:
    static void Initialize();
    static void Update(Player* player, EnemyManager* enemyManager, Boss* boss);
    static void Draw(Player* player, EnemyManager* enemyManager, Boss* boss, int cutinTimer, int cutinImageHandle);

private:
    // Easing state variables for smooth animation
    static float s_displayHpRatio;
    static float s_displayXpRatio;
    static float s_displaySpellRatio;
    static float s_bossHpRatio;
};
