#pragma once
#include "Scene.h"
#include <vector>

/// @brief リザルト画面の背景演出に使う粒子情報
struct ResultParticle
{
    float x, y;       ///< 座標
    float vx_;        ///< X方向の速度
    float vy_;        ///< Y方向の速度
    float size_;      ///< サイズ
    float angle_;     ///< 回転角
    float rot_speed_; ///< 回転速度
    int color_;       ///< 描画色
    int life_;        ///< 残り寿命フレーム数
};

/// @brief 勝利・敗北のリザルト画面を表示するシーン
class ResultScene : public Scene
{
public:
    static bool kIsVictory; ///< 勝利リザルトかどうかを示すフラグ

public:
    /// @brief リザルトシーンを初期化する
    void Initialize() override;

    /// @brief リザルトシーンを更新する
    void Update() override;

    /// @brief リザルトシーンを描画する
    void Draw() override;

    /// @brief リザルトシーンを終了処理する
    void Finalize() override;

private:
    /// @brief 勝利リザルトの更新を行う
    void UpdateVictory();

    /// @brief 敗北リザルトの更新を行う
    void UpdateGameOver();

    /// @brief 勝利リザルトを描画する
    void DrawVictory();

    /// @brief 敗北リザルトを描画する
    void DrawGameOver();

private:
    std::vector<ResultParticle> particles_; ///< 背景演出用パーティクル
    int state_timer_;                       ///< リザルト画面の経過タイマー
    int bg_graph_;                          ///< 背景画像ハンドル
    int player_graph_;                      ///< プレイヤー画像ハンドル

    /// @brief 縁取り付き文字列を描画する
    /// @param x 描画X座標
    /// @param y 描画Y座標
    /// @param str 描画文字列
    /// @param color 文字色
    /// @param outlineColor 縁取り色
    /// @param fontHandle フォントハンドル
    void DrawOutlinedString(int x, int y, const char* str, unsigned int color, unsigned int outlineColor, int fontHandle);
};