#pragma once
#include <unordered_map>

/// @brief ゲーム内の入力アクション種別
enum class InputAction
{
    kMoveUp,      ///< 上移動
    kMoveDown,    ///< 下移動
    kMoveLeft,    ///< 左移動
    kMoveRight,   ///< 右移動
    kFocus,       ///< 低速移動
    kAttack,      ///< 通常攻撃
    kSwitchMode,  ///< 攻撃モード切り替え
    kPause,       ///< ポーズ
    kConfirm,     ///< 決定
    kCancel,      ///< キャンセル
};

/// @brief 入力アクションとキーコードの対応を管理するクラス
class InputBinding
{
public:
    /// @brief デフォルトのキー割り当てで初期化する
    static void Initialize();

    /// @brief 指定アクションに対応するキーコードを取得する
    /// @param action 確認する入力アクション
    /// @return int キーコード
    static int GetKey(InputAction action);

    /// @brief 指定アクションに新しいキーコードを割り当てる
    /// @param action 変更する入力アクション
    /// @param keyCode 新しいキーコード
    static void Rebind(InputAction action, int keyCode);

private:
    static std::unordered_map<int, int> bindings_; ///< 入力アクションとキーコードの対応表
};