#pragma once
#include "Scene.h"
#include <vector>

// リザルト画面の演出（紙吹雪など）に使用されるパーティクルの構造体
struct ResultParticle {
    float x, y;         // パーティクルの現在座標
    float vx, vy;       // X方向・Y方向の移動速度ベクトル
    float size;         // パーティクルの描画サイズ
    float angle;        // 現在の描画角度（回転状態）
    float rotSpeed;     // 回転速度（毎フレーム加算される角度）
    int color;          // パーティクルの色（DxLibのカラーコードなど）
    int life;           // パーティクルの残り寿命（フレーム数）
};

// リザルト（ゲームクリア/ゲームオーバー）画面を描画・管理するシーンクラス
class ResultScene : public Scene {
public:
    // ゲームの勝敗結果を保持する静的フラグ（true: クリア/勝利, false: ゲームオーバー/敗北）
    // Scene移行前にGameScene等から書き換えて結果を渡すために使用する
    static bool s_isVictory;

    // [入力] なし
    // [出力] なし
    // [副作用] 勝利時は紙吹雪パーティクルの初期化、背景や自機画像の読み込みを行う
    void Initialize() override;

    // [入力] なし
    // [出力] なし
    // [副作用] パーティクルの更新および、キー入力（Zキー）によるタイトルへの遷移処理を行う
    void Update() override;

    // [入力] なし
    // [出力] なし
    // [副作用] 勝敗に応じた背景色、テキスト、自機画像（敗北時は暗転等）、パーティクルを描画する
    void Draw() override;

    // [入力] なし
    // [出力] なし
    // [副作用] 読み込んだ画像リソースを破棄する
    void Finalize() override;

private:
    std::vector<ResultParticle> m_particles; // 紙吹雪などの演出用パーティクルを管理する配列
    int m_stateTimer;                        // シーン開始からの経過時間を計るタイマー（文字のフェードインや入力受付の遅延に使用）
    int m_bgGraph;                           // 背景画像のグラフィックハンドル（DxLib用）
    int m_playerGraph;                       // 自機（プレイヤー）画像のグラフィックハンドル

    // [入力] x, y: 描画座標, str: 文字列, color: 文字色, outlineColor: 縁色, fontHandle: フォント
    // [出力] なし
    // [副作用] 指定された座標に縁取り付きの文字列を描画する（視認性向上のためのヘルパー関数）
    void DrawOutlinedString(int x, int y, const char* str, unsigned int color, unsigned int outlineColor, int fontHandle);
};