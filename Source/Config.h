#pragma once

/// @brief ゲームバランス調整用の設定値
namespace Config
{
    constexpr int kPlayerMaxHp = 15;             ///< プレイヤー最大HP
    constexpr float kPlayerSpeed = 5.0f;         ///< プレイヤー移動速度
    constexpr int kPlayerAttackInterval = 20;    ///< プレイヤー通常攻撃間隔
    constexpr int kPlayerSpecialInterval = 60;   ///< プレイヤー特殊攻撃間隔
    constexpr int kPlayerXpNeeded = 5;           ///< 初期レベルアップ必要経験値

    constexpr int kBoss1MaxHp = 60;              ///< ボス1最大HP
    constexpr float kBoss1Speed = 1.5f;          ///< ボス1移動速度

    constexpr int kBoss2MaxHp = 80;              ///< ボス2最大HP
    constexpr float kBoss2Speed = 2.0f;          ///< ボス2移動速度

    constexpr int kBoss3MaxHp = 150;             ///< ボス3最大HP
    constexpr float kBoss3Speed = 2.5f;          ///< ボス3移動速度
    constexpr int kBoss3Lives = 3;               ///< ボス3のHP段階数

    constexpr int kEnemyMaxHp = 5;               ///< 通常敵最大HP
    constexpr float kEnemySpeed = 2.0f;          ///< 通常敵移動速度

    constexpr int kGridCellSize = 100;           ///< 衝突判定グリッドのセルサイズ
}