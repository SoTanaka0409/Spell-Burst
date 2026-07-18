#include "InputManager.h"
#include "ObjectManager.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"

namespace
{
	bool IsValidKeyCode(int keyCode)
	{
		return keyCode >= 0 && keyCode < 256;
	}
}

int InputManager::down_buffer_[256] = { 0 };
int InputManager::up_buffer_[256] = { 0 };
int InputManager::mouse_down_buffer_ = 0;

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

int InputManager::CheckDownKey(int keyCode)
{
	if (!IsValidKeyCode(keyCode))
	{
		return 0;
	}

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
	if (!IsValidKeyCode(keyCode))
	{
		return 0;
	}

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
	if (!IsValidKeyCode(keyCode))
	{
		return 0;
	}

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
int InputManager::CheckMouseDown(int button)
{
    int state = GetMouseInput() & button;
    int result = 0;
    if ((mouse_down_buffer_ & button) == 0 && state != 0) result = 1;
    if (state != 0) mouse_down_buffer_ |= button;
    else mouse_down_buffer_ &= ~button;
    return result;
}

int InputManager::CheckMousePress(int button)
{
    return (GetMouseInput() & button) != 0 ? 1 : 0;
}

int InputManager::CheckMouseUp(int button)
{
    // Not implemented fully for buffer yet, simplify to down check inverse
    return 0; // Or implement later if needed
}

void InputManager::GetMousePosition(int* x, int* y)
{
    GetMousePoint(x, y);
}
