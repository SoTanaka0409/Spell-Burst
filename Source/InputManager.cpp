#include "InputManager.h"
#include "ObjectManager.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"

int InputManager::down_buffer_[256] = { 0 };
int InputManager::up_buffer_[256] = { 0 };

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
	
	if (down_buffer_[KeyCode] == 0 && keyState == 1)
	{
		result = 1;
	}

	down_buffer_[KeyCode] = keyState;
	return result;
}

int InputManager::CheckUpKey(int KeyCode)
{
	int result = 0;
	int keyState = CheckHitKey(KeyCode);
	
	if (up_buffer_[KeyCode] == 1 && keyState == 0)
	{
		result = 1;
	}

	up_buffer_[KeyCode] = keyState;
	return result;
}

int InputManager::CheckPressKey(int KeyCode)
{
	return CheckHitKey(KeyCode);
}

int InputManager::ActionDown(InputAction action)
{
    return CheckDownKey(InputBinding::GetKey(action));
}

int InputManager::ActionPress(InputAction action)
{
    return CheckPressKey(InputBinding::GetKey(action));
}

int InputManager::ActionUp(InputAction action)
{
    return CheckUpKey(InputBinding::GetKey(action));
}
