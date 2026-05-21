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
	// �߂�l�p�̕ϐ���p��wwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	int result = 0;

	// �w��L�[�̌��݂̏�Ԃ�擾
	int keyState = CheckHitKey(KeyCode);
	
	//�O��L�[��������Ă��炸�A���݃L�[��������Ă�����
	if (mDownBuffer[KeyCode] == 0 && keyState == 1)
	{
		result = 1;
	}

	//���݂̃L�[�̏�Ԃ�o�b�t�@�Ɋi�[
	mDownBuffer[KeyCode] = keyState;
	return result;
}
int InputManager::CheckPressKey(int KeyCode)
{
	return CheckHitKey(KeyCode);
}