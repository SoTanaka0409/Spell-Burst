#pragma once
#include "InputAction.h"

// キーボード等の入力デバイスの状態確認・管理するクラス
class InputManager
{
public:
	InputManager();
	~InputManager();

	// [入力] KeyCode: 確認対象のキー
	// [出力] キーが押された瞬間だけ1、それ以外は0
	// [副作用] 前フレームの状態をバッファに保存する
	static int CheckDownKey(int KeyCode);

	// [入力] KeyCode: 確認対象のキー
	// [出力] キーが離された瞬間だけ1、それ以外は0
	// [副作用] 前フレームの状態をバッファに保存する
	static int CheckUpKey(int KeyCode);

	// [入力] KeyCode: 確認対象のキー
	// [出力] キーが押されている間は1、それ以外は0
	// [副作用] なし
	static int CheckPressKey(int KeyCode);

	// --- アクションベースのラッパー ---
	// InputBinding に登録されたキーを使用してアクション入力を確認する

	// [入力] action: 確認するゲームアクション
	// [出力] アクションに対応するキーが押された瞬間だけ1
	static int ActionDown(InputAction action);

	// [入力] action: 確認するゲームアクション
	// [出力] アクションに対応するキーが押されている間は1
	static int ActionPress(InputAction action);

	// [入力] action: 確認するゲームアクション
	// [出力] アクションに対応するキーが離された瞬間だけ1
	static int ActionUp(InputAction action);

private:
	static int down_buffer_[256];
	static int up_buffer_[256];
};