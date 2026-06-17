#pragma once

// キーボード等の入力デバイスの状態検知を管理するクラス
class InputManager
{
public:
	InputManager();
	~InputManager();

	// [入力] KeyCode: 検知対象のキー
	// [出力] キーが押された瞬間であれば1、それ以外は0
	// [副作用] 前フレームの状態をバッファに保存する
	static int CheckDownKey(int KeyCode);

	// [入力] KeyCode: 検知対象のキー
	// [出力] キーが離された瞬間であれば1、それ以外は0
	// [副作用] 前フレームの状態をバッファに保存する
	static int CheckUpKey(int KeyCode);

	// [入力] KeyCode: 検知対象のキー
	// [出力] キーが押し続けられている間は1、それ以外は0
	// [副作用] なし
	static int CheckPressKey(int KeyCode);

private:
	static int mDownBuffer[256];
	static int mUpBuffer[256];
};