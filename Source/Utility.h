#pragma once
#include "DxLib.h"

//プログラム内で共通して使用する定数定義などをここに記述していく
//関数なども記述していく

class Utility
{
	public://定数定義
	static const int SCREEN_WIDTH = 1600; //画面の幅

	static const int SCREEN_HEIGHT = 900; //画面の高さ

	static VECTOR StageSize;


	static float DegToRad(float deg)
	{
		return deg * DX_PI_F / 180.0f;
	}


};
//