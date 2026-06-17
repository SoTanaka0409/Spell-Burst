#include <memory>
#pragma once
#include "Scene.h"

class EnemyManager;

// メインゲーム進行を管理するシーンクラス
// 画面揺れやヒットストップ等の全体エフェクト状態も併せて管理する
class GameScene : public Scene {
private:
    std::unique_ptr<EnemyManager> mpEnemyManager;   // 敵の生成や進行フェーズを管理するマネージャーのポインタ

    int m_cutinTimer;               // カットイン演出（大技発動時など）の進行度を測るタイマー
    int m_cutinImageHandle;         // カットイン用画像のグラフィックハンドル（DxLib用）

    int m_screenHandle;             // オフスクリーン描画（画面揺れ等のポストエフェクト用）の画像ハンドル

    int m_shakeTimer;               // 画面揺れ（スクリーンシェイク）の残りフレーム数
    float m_shakeMagnitude;         // 画面揺れの強さ（ピクセル幅など）

    int m_hitStopTimer;             // ヒットストップ（一時的な時間停止演出）の残りフレーム数

public:
    // --- 静的（static）メンバ変数 ---
    static int s_currentStage;         // 現在プレイ中のステージ番号
    static int s_playFrameCount;       // プレイ開始からの経過フレーム数（スコア計算やタイムアタック用）
    static bool s_isTimeAttackActive;  // タイムアタックモードが有効かどうかのフラグ

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
    // [副作用] オフスクリーン(m_screenHandle)に一度描画した後、画面揺れ(シェイク)のズレを加味してメイン画面へ転送する
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
    EnemyManager* GetEnemyManager() const { return mpEnemyManager.get(); }

    // [入力] duration: 揺らすフレーム数, magnitude: 揺れの強さ
    // [出力] なし
    // [副作用] 画面揺れタイマーを設定し、現在の演出を上書き・適用する（被弾時や爆発時に使用）
    void AddScreenShake(int duration, float magnitude);

    // [入力] duration: 停止フレーム数
    // [出力] なし
    // [副作用] 強い攻撃が当たった際など、ゲーム全体の更新処理を一時停止（ヒットストップ）させ、打撃感を演出する
    void AddHitStop(int duration);
};