#pragma once

// �L�[�{�[�h���̓��̓f�o�C�X�̏�Ԍ��m��Ǘ�����N���X
class InputManager
{
public:
	InputManager();
	~InputManager();

	// [����] KeyCode: ���m�Ώۂ̃L�[
	// [�o��] �L�[�������ꂽ�u�Ԃł����1�A����ȊO��0
	// [����p] �O�t���[���̏�Ԃ�o�b�t�@�ɕۑ�����
	static int CheckDownKey(int KeyCode);

	// [����] KeyCode: ���m�Ώۂ̃L�[
	// [�o��] �L�[�������ꂽ�u�Ԃł����1�A����ȊO��0
	// [����p] �O�t���[���̏�Ԃ�o�b�t�@�ɕۑ�����
	static int CheckUpKey(int KeyCode);

	// [����] KeyCode: ���m�Ώۂ̃L�[
	// [�o��] �L�[�������������Ă���Ԃ�1�A����ȊO��0
	// [����p] �Ȃ�
	static int CheckPressKey(int KeyCode);

private:
	static int downBuffer[256];
	static int upBuffer[256];
};