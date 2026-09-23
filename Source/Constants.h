#pragma once

/// @brief 画面やUIなどの固定値
namespace Constants
{
    constexpr int kScreenWidth = 1600;       ///< 画面幅
    constexpr int kScreenHeight = 900;       ///< 画面高さ

    constexpr float PLAYER_START_X = 800.0f; ///< プレイヤー初期X座標
    constexpr float PLAYER_START_Y = 800.0f; ///< プレイヤー初期Y座標
    constexpr float PLAYER_SPEED = 5.0f;     ///< プレイヤー移動速度
    constexpr int PLAYER_MAX_HP = 10;        ///< プレイヤー最大HP
    constexpr float PLAYER_RADIUS = 5.0f;    ///< プレイヤー当たり判定半径

    constexpr int ENEMY_SCORE = 100;         ///< 敵撃破時のスコア

    constexpr int HP_BAR_X = 160;            ///< HPバーX座標
    constexpr int HP_BAR_Y = 22;             ///< HPバーY座標
    constexpr int HP_BAR_WIDTH = 140;        ///< HPバー幅
    constexpr int HP_BAR_HEIGHT = 10;        ///< HPバー高さ
}