#pragma once
#include "InputAction.h"

// キーボードとマウス入力を扱いやすい形にまとめるクラス
class InputManager
{
public:
	InputManager();
	~InputManager();

    /*
     * キーが押された瞬間かを判定する。
     * [入力] keyCode: 確認するキーコード
     * [出力] 押された瞬間なら1、それ以外は0
     * [副作用] 入力状態のバッファを参照・更新する
     */
    static int CheckDownKey(int keyCode);

    /*
     * キーが離された瞬間かを判定する。
     * [入力] keyCode: 確認するキーコード
     * [出力] 離された瞬間なら1、それ以外は0
     * [副作用] 入力状態のバッファを参照・更新する
     */
    static int CheckUpKey(int keyCode);

    /*
     * キーが押され続けているかを判定する。
     * [入力] keyCode: 確認するキーコード
     * [出力] 押されている間は1、それ以外は0
     * [副作用] なし
     */
    static int CheckPressKey(int keyCode);

    static int ActionDown(InputAction action);
    static int ActionPress(InputAction action);
    static int ActionUp(InputAction action);

    static int CheckMouseDown(int button);
    static int CheckMousePress(int button);
    static int CheckMouseUp(int button);
    static void GetMousePosition(int* x, int* y);

private:
    static int mouse_down_buffer_;
	static int down_buffer_[256];
	static int up_buffer_[256];
};