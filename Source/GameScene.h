#include <memory>
#pragma once
#include "Scene.h"

class EnemyManager;

// メインゲーム進行を管理するシーンクラス
// 画面揺れやヒットストップ等の全体エフェクト状態も併せて管理する
class GameScene : public Scene {
private:
    std::unique_ptr<EnemyManager> enemy_manager_;   // 敵の生成や進行フェーズを管理するマネージャーのポインタ

    int cutin_timer_;               // カットイン演出（大技発動時など）の進行度を測るタイマー
    int cutin_image_handle_;         // カットイン用画像のグラフィックハンドル（DxLib用）

    int screen_handle_;             // オフスクリーン描画（画面揺れ等のポストエフェクト用）の画像ハンドル

    int shake_timer_;               // 画面揺れ（スクリーンシェイク）の残りフレーム数
    float shake_magnitude_;         // 画面揺れの強さ（ピクセル幅など）

    int hit_stop_timer_;             // ヒットストップ（一時的な時間停止演出）の残りフレーム数

public:
    // --- 静的（static）メンバ変数 ---
    static int currentStage;         // 現在プレイ中のステージ番号
    static int playFrameCount;       // プレイ開始からの経過フレーム数（スコア計算やタイムアタック用）
    static bool isTimeAttackActive;  // タイムアタックモードが有効かどうかのフラグ

    // コンストラクタ / デストラクタ
    // [入力] なし
    // [出力] なし
    // [副作用] オブジェクトの生成・破棄を行う（実際の初期化処理はInitializeで実行）
    GameScene();
    virtual ~GameScene() override;

    // [入力] なし
    // [出力] なし
    // [副作用] マネージャー類の生成、各種リソース（画像やサウンド）の確保、タイマーの初期化を行う
    void Initialize() override;

    // [入力] なし
    // [出力] なし
    // [副作用] ヒットストップ非適用時は各オブジェクト（自機、敵、弾など）の状態を更新し、衝突判定を処理する
    void Update() override;

    // [入力] なし
    // [出力] なし
    // [副作用] オフスクリーン(screen_handle_)に一度描画した後、画面揺れ(シェイク)のズレを加味してメイン画面へ転送する
    void Draw() override;

    // [入力] なし
    // [出力] なし
    // [副作用] 確保したマネージャーやリソースを破棄し、メモリリークを防ぐ
    void Finalize() override;

    // [入力] なし
    // [出力] なし
    // [副作用] ボスのスペルカード発動時や自機ボム発動時などのカットイン演出タイマーを起動する
    void TriggerCutin();

    // 敵マネージャーのポインタを取得する
    EnemyManager* GetEnemyManager() const { return enemy_manager_.get(); }

    // [入力] duration: 揺らすフレーム数, magnitude: 揺れの強さ
    // [出力] なし
    // [副作用] 画面揺れタイマーを設定し、現在の演出を上書き・適用する（被弾時や爆発時に使用）
    void AddScreenShake(int duration, float magnitude);

    // [入力] duration: 停止フレーム数
    // [出力] なし
    // [副作用] 強い攻撃が当たった際など、ゲーム全体の更新処理を一時停止（ヒットストップ）させ、打撃感を演出する
    void AddHitStop(int duration);
};