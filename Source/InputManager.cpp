#include "InputManager.h"
#include "ObjectManager.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"

namespace
{
/// @brief IsValidKeyCode を実行する
/// @param keyCode keyCode の値
/// @return bool 戻り値
	bool IsValidKeyCode(int keyCode)
	{
		return keyCode >= 0 && keyCode < 256;
	}
}

int InputManager::down_buffer_[256] = { 0 };
int InputManager::up_buffer_[256] = { 0 };
int InputManager::mouse_down_buffer_ = 0;

/// @brief InputManager を生成する
InputManager::InputManager()
{
}

/// @brief 破棄処理を行う
InputManager::~InputManager()
{
}

/// @brief CheckDownKey を実行する
/// @param keyCode keyCode の値
/// @return int 戻り値
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

/// @brief CheckUpKey を実行する
/// @param keyCode keyCode の値
/// @return int 戻り値
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

/// @brief CheckPressKey を実行する
/// @param keyCode keyCode の値
/// @return int 戻り値
int InputManager::CheckPressKey(int keyCode)
{
	if (!IsValidKeyCode(keyCode))
	{
		return 0;
	}

	return CheckHitKey(keyCode);
}

/// @brief ActionDown を実行する
/// @param action action の値
/// @return int 戻り値
int InputManager::ActionDown(InputAction action)
{
	return CheckDownKey(InputBinding::GetKey(action));
}

/// @brief ActionPress を実行する
/// @param action action の値
/// @return int 戻り値
int InputManager::ActionPress(InputAction action)
{
	return CheckPressKey(InputBinding::GetKey(action));
}

/// @brief ActionUp を実行する
/// @param action action の値
/// @return int 戻り値
int InputManager::ActionUp(InputAction action)
{
	return CheckUpKey(InputBinding::GetKey(action));
}
/// @brief CheckMouseDown を実行する
/// @param button button の値
/// @return int 戻り値
int InputManager::CheckMouseDown(int button)
{
    int state = GetMouseInput() & button;
    int result = 0;
    if ((mouse_down_buffer_ & button) == 0 && state != 0) result = 1;
    if (state != 0) mouse_down_buffer_ |= button;
    else mouse_down_buffer_ &= ~button;
    return result;
}

/// @brief CheckMousePress を実行する
/// @param button button の値
/// @return int 戻り値
int InputManager::CheckMousePress(int button)
{
    return (GetMouseInput() & button) != 0 ? 1 : 0;
}

/// @brief CheckMouseUp を実行する
/// @param button button の値
/// @return int 戻り値
int InputManager::CheckMouseUp(int button)
{
    // Not implemented fully for buffer yet, simplify to down check inverse
    return 0; // Or implement later if needed
}

/// @brief GetMousePosition を実行する
/// @param x x の値
/// @param y y の値
void InputManager::GetMousePosition(int* x, int* y)
{
    GetMousePoint(x, y);
}
