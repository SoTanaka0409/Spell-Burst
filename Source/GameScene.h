#include <memory>
#pragma once
#include "Scene.h"

class EnemyManager;

class GameScene : public Scene
{
private:
    void DrawBackground();
    void DrawTimeAttackTimer();
    void DrawEffects();

    std::unique_ptr<EnemyManager> enemy_manager_;   // 謨ｵ縺ｮ逕滓・繧・ｲ陦後ヵ繧ｧ繝ｼ繧ｺ繧堤ｮ｡逅・☆繧九・繝阪・繧ｸ繝｣繝ｼ縺ｮ繝昴う繝ｳ繧ｿ

    int cutin_timer_;               // 繧ｫ繝・ヨ繧､繝ｳ貍泌・・亥､ｧ謚逋ｺ蜍墓凾縺ｪ縺ｩ・峨・騾ｲ陦悟ｺｦ繧呈ｸｬ繧九ち繧､繝槭・
    int cutin_image_handle_;         // 繧ｫ繝・ヨ繧､繝ｳ逕ｨ逕ｻ蜒上・繧ｰ繝ｩ繝輔ぅ繝・け繝上Φ繝峨Ν・・xLib逕ｨ・・

    int screen_handle_;             // 繧ｪ繝輔せ繧ｯ繝ｪ繝ｼ繝ｳ謠冗判・育判髱｢謠ｺ繧檎ｭ峨・繝昴せ繝医お繝輔ぉ繧ｯ繝育畑・峨・逕ｻ蜒上ワ繝ｳ繝峨Ν

    int shake_timer_;               // 逕ｻ髱｢謠ｺ繧鯉ｼ医せ繧ｯ繝ｪ繝ｼ繝ｳ繧ｷ繧ｧ繧､繧ｯ・峨・谿九ｊ繝輔Ξ繝ｼ繝謨ｰ
    float shake_magnitude_;         // 逕ｻ髱｢謠ｺ繧後・蠑ｷ縺包ｼ医ヴ繧ｯ繧ｻ繝ｫ蟷・↑縺ｩ・・

    int hit_stop_timer_;             // 繝偵ャ繝医せ繝医ャ繝暦ｼ井ｸ譎ら噪縺ｪ譎る俣蛛懈ｭ｢貍泌・・峨・谿九ｊ繝輔Ξ繝ｼ繝謨ｰ

    int damage_flash_timer_;         // 繝繝｡繝ｼ繧ｸ繝輔Λ繝・す繝･縺ｮ谿九ｊ繝輔Ξ繝ｼ繝謨ｰ
    unsigned int damage_flash_color_; // 繝繝｡繝ｼ繧ｸ繝輔Λ繝・す繝･縺ｮ濶ｲ

public:
    static int current_stage_;          // 現在プレイ中のステージ番号
    static int play_frame_count_;        // プレイ開始からの経過フレーム数（スコアやタイムアタック用）
    static bool is_time_attack_active_;  // タイムアタックモードが有効かどうかのフラグ

    /*
     * オブジェクトの生成・破棄を行う（実際の初期化処理はInitializeで実行）。
     * [入力] なし
     * [出力] なし
     * [副作用] メンバーが初期化される
     */
    GameScene();
    virtual ~GameScene() override;

    /*
     * マネージャーの生成、各種リソース（画像やサウンド）の確保、タイマーの初期化を行う。
     * [入力] なし
     * [出力] なし
     * [副作用] ゲーム開始に必要なリソースが確保される
     */
    void Initialize() override;

    /*
     * ヒットストップ適用時は各オブジェクト（敵、弾、壁など）の状態を更新し、遷移条件を処理する。
     * [入力] なし
     * [出力] なし
     * [副作用] ゲーム全体の状態が進行する
     */
    void Update() override;

    /*
     * オフスクリーン(screen_handle_)に一度描画した後、画面揺れのズレを加算してメイン画面へ転送する。
     * [入力] なし
     * [出力] なし
     * [副作用] 画面に描画される
     */
    void Draw() override;

    /*
     * 確保したマネージャーやリソースを解放し、メモリリークを防ぐ。
     * [入力] なし
     * [出力] なし
     * [副作用] リソースが解放される
     */
    void Finalize() override;

    /*
     * ボスのスペルカード発動時やボス出現時などのカットイン演出タイマーを起動する。
     * [入力] なし
     * [出力] なし
     * [副作用] cutin_timer_が設定される
     */
    void TriggerCutin();

    EnemyManager* GetEnemyManager() const { return enemy_manager_.get(); }

    /*
     * 画面揺れタイマーを設定し、現在の残量を上書き適用する（強烈な衝突や大爆発時に使用）。
     * [入力] duration: 揺らすフレーム数, magnitude: 揺れの強さ
     * [出力] なし
     * [副作用] shake_timer_とshake_magnitude_が更新される
     */
    void AddScreenShake(int duration, float magnitude);

    /*
     * 強い爆発が起きたなど、ゲーム全体の更新処理を一時停止（ヒットストップ）させ、臨場感を演出する。
     * [入力] duration: 停止フレーム数
     * [出力] なし
     * [副作用] hit_stop_timer_が設定される
     */
    void AddHitStop(int duration);

    /*
     * 画面を指定色でフラッシュさせ、ダメージや爆発の視覚的フィードバックを演出する。
     * [入力] duration: フラッシュするフレーム数, color: フラッシュ色
     * [出力] なし
     * [副作用] damage_flash_timer_とdamage_flash_color_が設定される
     */
    void AddDamageFlash(int duration, unsigned int color);
};
