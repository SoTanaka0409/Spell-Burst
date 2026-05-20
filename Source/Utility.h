#pragma once
#include "DxLib.h"

//�v���O������ŋ��ʂ��Ďg�p����萔��`�Ȃǂ�����ɋL�q���Ă���
//�֐��Ȃǂ�L�q���Ă���

class Utility
{
	public://�萔��`
	static const int SCREEN_WIDTH = 1920; //��ʂ̕�

	static const int SCREEN_HEIGHT = 1080; //��ʂ̍���

	static VECTOR StageSize;


	static float DegToRad(float deg)
	{
		return deg * DX_PI_F / 180.0f;
	}


};
//