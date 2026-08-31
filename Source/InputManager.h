#pragma once
#include "InputAction.h"

/// @brief キーボードとマウス入力を扱いやすい形にまとめるクラス
class InputManager
{
public:
	/// @brief 入力管理クラスを生成する
	InputManager();

	/// @brief 入力管理クラスを破棄する
	~InputManager();

    /// @brief キーが押された瞬間かを判定する
    /// @param keyCode 確認するキーコード
    /// @return int 押された瞬間なら1、それ以外は0
    static int CheckDownKey(int keyCode);

    /// @brief キーが離された瞬間かを判定する
    /// @param keyCode 確認するキーコード
    /// @return int 離された瞬間なら1、それ以外は0
    static int CheckUpKey(int keyCode);

    /// @brief キーが押され続けているかを判定する
    /// @param keyCode 確認するキーコード
    /// @return int 押されている間は1、それ以外は0
    static int CheckPressKey(int keyCode);

    /// @brief アクションが押された瞬間かを判定する
    /// @param action 確認する入力アクション
    /// @return int 押された瞬間なら1
    static int ActionDown(InputAction action);

    /// @brief アクションが押され続けているかを判定する
    /// @param action 確認する入力アクション
    /// @return int 押されている間は1
    static int ActionPress(InputAction action);

    /// @brief アクションが離された瞬間かを判定する
    /// @param action 確認する入力アクション
    /// @return int 離された瞬間なら1
    static int ActionUp(InputAction action);

    /// @brief マウスボタンが押された瞬間かを判定する
    /// @param button 確認するマウスボタン
    /// @return int 押された瞬間なら1
    static int CheckMouseDown(int button);

    /// @brief マウスボタンが押され続けているかを判定する
    /// @param button 確認するマウスボタン
    /// @return int 押されている間は1
    static int CheckMousePress(int button);

    /// @brief マウスボタンが離された瞬間かを判定する
    /// @param button 確認するマウスボタン
    /// @return int 離された瞬間なら1
    static int CheckMouseUp(int button);

    /// @brief マウス座標を取得する
    /// @param x X座標の出力先
    /// @param y Y座標の出力先
    static void GetMousePosition(int* x, int* y);

private:
    static int mouse_down_buffer_; ///< マウス押下状態の前フレームバッファ
	static int down_buffer_[256];   ///< キー押下状態の前フレームバッファ
	static int up_buffer_[256];     ///< キー解放状態の前フレームバッファ
};