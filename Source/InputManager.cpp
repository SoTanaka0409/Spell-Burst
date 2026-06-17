#include "InputManager.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"

int InputManager::mDownBuffer[256] = { 0 };
int InputManager::mUpBuffer[256] = { 0 };

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

int InputManager::CheckDownKey(int KeyCode)//‰Ÿ‚µ‚Ä‚¢‚éŠÔ‚¸‚Á‚Æ1‚ð•Ô‚·
{
	int result = 0;
	int keyState = CheckHitKey(KeyCode);
	
	if (mDownBuffer[KeyCode] == 0 && keyState == 1)
	{
		result = 1;
	}

	mDownBuffer[KeyCode] = keyState;
	return result;
}

int InputManager::CheckUpKey(int KeyCode)
{
	int result = 0;
	int keyState = CheckHitKey(KeyCode);
	
	if (mUpBuffer[KeyCode] == 1 && keyState == 0)
	{
		result = 1;
	}

	mUpBuffer[KeyCode] = keyState;
	return result;
}

int InputManager::CheckPressKey(int KeyCode)
{
	return CheckHitKey(KeyCode);
}