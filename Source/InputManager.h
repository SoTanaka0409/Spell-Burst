#pragma once
class InputManager
{
public:
	InputManager();

	~InputManager();

	// ・SW・SUYU・SUSUSU・SU・SU [・SU・SU・SU・SU・SU・SU・SUSUSUSU・SU・SUYASUSUSU・SU・SU 1
	static int CheckDownKey(int KeyCode);

	// ・SW・SUYU・SUSUSU・SU・SU [・SU・SU・SU・SU・SU・SU・SUSUSUSU・SU・SUYASUSUSU・SU・SU 1
	static int CheckUpKey(int KeyCode);

	// ・｜｜ｧｧｲｽｽｽｽｲｽｽｽｽｽ
	static int CheckPressKey(int KeyCode);

private:
	static int mDownBuffer[256];
	static int mUpBuffer[256];
};//