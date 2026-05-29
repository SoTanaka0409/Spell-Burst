#pragma once

class Player;
class Boss;
class EnemyManager;

// UI情報の描画管理クラス
// HUD要素のアニメーション補間(イージング)を行うため、静的変数を保持する
class HUD {
public:
    // [入力] なし
    // [出力] なし
    // [副作用] イージング用変数などの静的状態をリセットする
    static void Initialize();

    // [入力] player: 自機, enemyManager: 敵管理, boss: ボス
    // [出力] なし
    // [副作用] 現在のHP等に基づき、表示用の補間比率（イージング）を計算・更新する
    static void Update(Player* player, EnemyManager* enemyManager, Boss* boss);

    // [入力] player, enemyManager, boss, cutinTimer: 演出時間, cutinImageHandle: 演出画像
    // [出力] なし
    // [副作用] 画面上の最前面に各UIコンポーネント（ゲージ、カットイン等）を描画する
    static void Draw(Player* player, EnemyManager* enemyManager, Boss* boss, int cutinTimer, int cutinImageHandle);

private:
    static float s_displayHpRatio; // アニメーション補間用のHP表示比率
    static float s_displayXpRatio; // アニメーション補間用の経験値表示比率
    static float s_displaySpellRatio; // アニメーション補間用のスペルゲージ表示比率
    static float s_displayBarrierRatio; // アニメーション補間用のバリアゲージ表示比率
    static float s_bossHpRatio; // アニメーション補間用のボスHP表示比率
};