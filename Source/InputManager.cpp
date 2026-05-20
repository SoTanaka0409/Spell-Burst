#include"InputManager.h"
#include"DxLib.h"

int InputManager::mDownBuffer[256] = { 0 };
int InputManager::mUpBuffer[256] = { 0 };

InputManager::InputManager()
{

}

InputManager::~InputManager()
{

}

// 指定されたキーが押された瞬間だけ 1 を返す関数
int InputManager::CheckDownKey(int KeyCode)
{
	int result = 0;

	// 指定キーの現在の状態を取得
	int keyState = CheckHitKey(KeyCode);

	// 前回キーを押していなくて、現在キーを押していれば「押した瞬間」
	if (mDownBuffer[KeyCode] == 0 && keyState == 1)
	{
		result = 1;
	}

	// 現在のキーの状態をバッファに格納
	mDownBuffer[KeyCode] = keyState;
	return result;
}

// 指定されたキーが離された瞬間だけ 1 を返す関数
int InputManager::CheckUpKey(int KeyCode)
{
	int result = 0;

	// 指定キーの現在の状態を取得
	int keyState = CheckHitKey(KeyCode);

	// 前回キーを押していて、現在キーを押していなければ「離した瞬間」
	if (mUpBuffer[KeyCode] == 1 && keyState == 0)
	{
		result = 1;
	}

	// 現在のキーの状態をバッファに格納
	mUpBuffer[KeyCode] = keyState;
	return result;
}

// 指定されたキーを押し続けている間 1 を返す関数
int InputManager::CheckPressKey(int KeyCode)
{
	return CheckHitKey(KeyCode);
}
