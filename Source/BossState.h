#pragma once

class Boss;

/// @brief ボスの状態処理を表す抽象基底クラス
class BossState
{
public:
    /// @brief ボス状態を破棄する
    virtual ~BossState() = default;

    /// @brief 状態が有効な間、毎フレーム処理を行う
    /// @param boss 更新対象のボス
    virtual void Update(Boss* boss) = 0;
};