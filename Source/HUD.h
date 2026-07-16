#pragma once

class Player;
class Boss;
class EnemyManager;

class HUD
{
public:
    /*
     * イージング用変数などの静的変数をリセットする。
     * [入力] なし
     * [出力] なし
     * [副作用] 表示比率が初期化される
     */
    static void Initialize();

    /*
     * 現在のHPなどに基づき、表示用の比率（イージング）を計算・更新する。
     * [入力] player: プレイヤー, enemyManager: 敵マネージャー, boss: ボス
     * [出力] なし
     * [副作用] displayHpRatio_等が更新される
     */
    static void Update(Player* player, EnemyManager* enemyManager, Boss* boss);

    /*
     * 画面最前面に各UIコンポーネント（ゲームUI、カットイン等）を描画する。
     * [入力] player: プレイヤー, enemyManager: 敵マネージャー, boss: ボス, cutinTimer: カットインタイマー, cutinImageHandle: 画像ハンドル
     * [出力] なし
     * [副作用] 画面に描画される
     */
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
