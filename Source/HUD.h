#pragma once

class Player;
class Boss;
class EnemyManager;

class HUD
{
public:
	static void Initialize();

	static void Update(Player* player, EnemyManager* enemyManager, Boss* boss);

	static void Draw(Player* player, EnemyManager* enemyManager, Boss* boss, int cutinTimer, int cutinImageHandle);

private:
	static float display_hp_ratio_;
	static float display_xp_ratio_;
	static float display_spell_ratio_;
	static float display_barrier_ratio_;
	static float boss_hp_ratio_;

	static void DrawPlayerStatus(Player* player);

	static void DrawBossStatus(Boss* boss);

	static void DrawEnemyProgress(EnemyManager* enemyManager);

	static void DrawCutin(int cutinTimer, int cutinImageHandle);
};
