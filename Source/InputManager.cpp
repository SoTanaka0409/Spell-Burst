#include "InputManager.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"

int InputManager::downBuffer[256] = { 0 };
int InputManager::upBuffer[256] = { 0 };

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

int InputManager::CheckDownKey(int KeyCode)//�����Ă���Ԃ�����1��Ԃ�
{
	int result = 0;
	int keyState = CheckHitKey(KeyCode);
	
	if (downBuffer[KeyCode] == 0 && keyState == 1)
	{
		result = 1;
	}

	downBuffer[KeyCode] = keyState;
	return result;
}

int InputManager::CheckUpKey(int KeyCode)
{
	int result = 0;
	int keyState = CheckHitKey(KeyCode);
	
	if (upBuffer[KeyCode] == 1 && keyState == 0)
	{
		result = 1;
	}

	upBuffer[KeyCode] = keyState;
	return result;
}

int InputManager::CheckPressKey(int KeyCode)
{
	return CheckHitKey(KeyCode);
}