#pragma once
#include "DxLib.h"

<<<<<<< HEAD
//�v���O������ŋ��ʂ��Ďg�p����萔��`�Ȃǂ�����ɋL�q���Ă���
//�֐��Ȃǂ�L�q���Ă���

class Utility
{
	public://�萔��`
	static const int SCREEN_WIDTH = 1920; //��ʂ̕�

	static const int SCREEN_HEIGHT = 1080; //��ʂ̍���

	static VECTOR StageSize;
=======
//プログラム内で共通して使用する定数定義などをここに記述していく
//関数なども記述していく

class Utility
{
	public://定数定義
	static const int SCREEN_WIDTH = 1600; //画面の幅

	static const int SCREEN_HEIGHT = 900; //画面の高さ

	static VECTOR StageSize;
	static float TimeScale;

>>>>>>> main


	static float DegToRad(float deg)
	{
		return deg * DX_PI_F / 180.0f;
	}


};
//