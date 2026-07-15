#pragma once

class Player;
class Boss;
class EnemyManager;

// UI・ｽ・ｽ・ｽﾌ描・ｽ・ｽﾇ暦ｿｽ・ｽN・ｽ・ｽ・ｽX
// HUD・ｽv・ｽf・ｽﾌア・ｽj・ｽ・ｽ・ｽ[・ｽV・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ(・ｽC・ｽ[・ｽW・ｽ・ｽ・ｽO)・ｽ・ｽs・ｽ・ｽ・ｽ・ｽ・ｽﾟ、・ｽﾃ的・ｽﾏ撰ｿｽ・ｽ・ｽﾛ趣ｿｽ・ｽ・ｽ・ｽ・ｽ
class HUD
{
public:
    // [・ｽ・ｽ・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽo・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽ・ｽ・ｽ・ｽp] ・ｽC・ｽ[・ｽW・ｽ・ｽ・ｽO・ｽp・ｽﾏ撰ｿｽ・ｽﾈどの静的・ｽ・ｽﾔゑｿｽ・ｽ・ｽZ・ｽb・ｽg・ｽ・ｽ・ｽ・ｽ
    static void Initialize();

    // [・ｽ・ｽ・ｽ・ｽ] player: ・ｽ・ｽ・ｽ@, enemy_manager_: ・ｽG・ｽﾇ暦ｿｽ, boss: ・ｽ{・ｽX
    // [・ｽo・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽ・ｽ・ｽ・ｽp] ・ｽ・ｽ・ｽﾝゑｿｽHP・ｽ・ｽ・ｽﾉ奇ｿｽﾃゑｿｽ・ｽA・ｽ\・ｽ・ｽ・ｽp・ｽﾌ包ｿｽﾔ比率・ｽi・ｽC・ｽ[・ｽW・ｽ・ｽ・ｽO・ｽj・ｽ・ｽv・ｽZ・ｽE・ｽX・ｽV・ｽ・ｽ・ｽ・ｽ
    static void Update(Player* player, EnemyManager* enemy_manager_, Boss* boss);

    // [] player, enemy_manager_, boss, cutin_timer_: o, cutin_image_handle_: o鞫・
    // [o] ﾈ・
    // [p] ﾊ称最前ﾊに各UIR|[lgiQ[WAJbgCj`謔ｷ
    static void Draw(Player* player, EnemyManager* enemy_manager_, Boss* boss, int cutin_timer_, int cutin_image_handle_);

private:
    static float displayHpRatio; // Aj[Vﾔ用HP\范ｦ
    static float displayXpRatio; // Aj[Vﾔ用ﾌ経l\范ｦ
    static float displaySpellRatio; // Aj[Vﾔ用ﾌスyQ[W\范ｦ
    static float displayBarrierRatio; // Aj[Vﾔ用ﾌバAQ[W\范ｦ
    static float bossHpRatio; // Aj[Vﾔ用ﾌボXHP\范ｦ

    static void DrawPlayerStatus(Player* player);
    static void DrawBossStatus(Boss* boss);
    static void DrawEnemyProgress(EnemyManager* enemy_manager_);
    static void DrawCutin(int cutin_timer_, int cutin_image_handle_);
};
