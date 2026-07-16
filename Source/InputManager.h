#pragma once
#include "InputAction.h"

// キーボード等の入力デバイスの状態確認・管理するクラス
class InputManager
{
public:
	InputManager();
	~InputManager();

    /*
     * キーが押された瞬間かどうかを判定する。
     * [入力] keyCode: 確認対象のキーコード
     * [出力] キーが押された瞬間だけ1、それ以外は0
     * [副作用] 前フレームの状態をバッファに保存する
     */
    static int CheckDownKey(int keyCode);

    /*
     * キーが離された瞬間かどうかを判定する。
     * [入力] keyCode: 確認対象のキーコード
     * [出力] キーが離された瞬間だけ1、それ以外は0
     * [副作用] 前フレームの状態をバッファに保存する
     */
    static int CheckUpKey(int keyCode);

    /*
     * キーが押されている状態かどうかを判定する。
     * [入力] keyCode: 確認対象のキーコード
     * [出力] キーが押されている間は1、それ以外は0
     * [副作用] なし
     */
    static int CheckPressKey(int keyCode);

	// --- アクションベースのラッパー ---
	// InputBinding に登録されたキーを使用してアクション入力を確認する

    /*
     * アクションに対応するキーが押された瞬間か判定する。
     * [入力] action: 確認するゲームアクション
     * [出力] 押された瞬間だけ1
     * [副作用] なし
     */
    static int ActionDown(InputAction action);

    /*
     * アクションに対応するキーが押されているか判定する。
     * [入力] action: 確認するゲームアクション
     * [出力] 押されている間は1
     * [副作用] なし
     */
    static int ActionPress(InputAction action);

    /*
     * アクションに対応するキーが離された瞬間か判定する。
     * [入力] action: 確認するゲームアクション
     * [出力] 離された瞬間だけ1
     * [副作用] なし
     */
    static int ActionUp(InputAction action);

private:
	static int down_buffer_[256];
	static int up_buffer_[256];
};
