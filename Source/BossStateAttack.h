#pragma once
#include "BossState.h"

/// @brief ボス1用の直線弾幕状態
class BossStateSimple : public BossState
{
public:
    /// @brief 攻撃タイマーを初期化する
    BossStateSimple() : attack_timer_(0) {}

    /// @brief 直線弾幕の攻撃処理を更新する
    /// @param boss 更新対象のボス
    void Update(Boss* boss) override;

private:
    int attack_timer_; ///< 攻撃間隔を管理するタイマー
};

/// @brief ボス2用の反射弾幕状態
class BossStateBouncing : public BossState
{
public:
    /// @brief 攻撃タイマーを初期化する
    BossStateBouncing() : attack_timer_(0) {}

    /// @brief 反射弾幕の攻撃処理を更新する
    /// @param boss 更新対象のボス
    void Update(Boss* boss) override;

private:
    int attack_timer_; ///< 攻撃間隔を管理するタイマー
};

/// @brief ボス3用の複合弾幕状態
class BossStateFinal : public BossState
{
public:
    /// @brief 攻撃タイマーとパターン状態を初期化する
    BossStateFinal() : attack_timer_(0), pattern_index_(0),
        invincible_cycle_timer_(0) {}

    /// @brief 複合弾幕と無敵サイクルを更新する
    /// @param boss 更新対象のボス
    void Update(Boss* boss) override;

private:
    int attack_timer_;           ///< 攻撃間隔を管理するタイマー
    int pattern_index_;          ///< 現在の攻撃パターン番号
    int invincible_cycle_timer_; ///< 無敵サイクルを管理するタイマー
};

/// @brief ボス死亡演出状態
class BossStateDying : public BossState
{
public:
    /// @brief 死亡演出タイマーを初期化する
    BossStateDying() : death_timer_(180) {}

    /// @brief 死亡演出を更新する
    /// @param boss 更新対象のボス
    void Update(Boss* boss) override;

private:
    int death_timer_; ///< 死亡演出の残りフレーム数
};