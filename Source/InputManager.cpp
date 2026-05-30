#include "InputManager.h"
#include "DxLib.h"

int InputManager::mDownBuffer[256] = { 0 };
int InputManager::mUpBuffer[256] = { 0 };

InputManager::InputManager()
{

}

InputManager::~InputManager()
{

}

int InputManager::CheckDownKey(int KeyCode)
{
	// ・Suweku sosu l・sp・sufu change sauce・su・sp・su・su wwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	int result = 0;

	// ・Sw・S・SL・S
	int keyState = CheckHitKey(KeyCode);
	
	// ・S O ・ S L ・ S
	if (mDownBuffer[KeyCode] == 0 && keyState == 1)
	{
		result = 1;
	}

	// ・Su・su・sun's kiss
	mDownBuffer[KeyCode] = keyState;
	return result;
}
int InputManager::CheckPressKey(int KeyCode)
{
	return CheckHitKey(KeyCode);
}