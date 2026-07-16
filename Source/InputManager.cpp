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

int InputManager::CheckDownKey(int keyCode)//???????????????1????
{
	int result = 0;
	int keyState = CheckHitKey(keyCode);
	
	if (down_buffer_[keyCode] == 0 && keyState == 1)
	{
		result = 1;
	}

	down_buffer_[keyCode] = keyState;
	return result;
}

int InputManager::CheckUpKey(int keyCode)
{
	int result = 0;
	int keyState = CheckHitKey(keyCode);
	
	if (up_buffer_[keyCode] == 1 && keyState == 0)
	{
		result = 1;
	}

	up_buffer_[keyCode] = keyState;
	return result;
}

int InputManager::CheckPressKey(int keyCode)
{
	return CheckHitKey(keyCode);
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
