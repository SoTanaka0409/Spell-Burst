#pragma once
class InputManager
{
public:
	InputManager();

	~InputManager();

	// �w�肳�ꂽ�L�[�������ꂽ�u�Ԃ��� 1 ��Ԃ��֐�
	static int CheckDownKey(int KeyCode);

	// �w�肳�ꂽ�L�[�������ꂽ�u�Ԃ��� 1 ��Ԃ��֐�
	static int CheckUpKey(int KeyCode);

	// �w�肳�ꂽ�L�[����������Ă���ԂP��Ԃ��֐�
	static int CheckPressKey(int KeyCode);

private:
	static int mDownBuffer[256];
	static int mUpBuffer[256];
};//