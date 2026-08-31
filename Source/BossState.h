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

    /// @brief 次の状態へ遷移すべきかを判定する
    /// @param boss 判定対象のボス
    /// @return bool 遷移すべきならtrue
    virtual bool ShouldTransition(Boss* boss) const { return false; }

    /// @brief 次の状態オブジェクトを取得する
    /// @param boss 遷移元のボス
    /// @return BossState* 次の状態。遷移しない場合はnullptr
    virtual BossState* GetNextState(Boss* boss) const { return nullptr; }
};