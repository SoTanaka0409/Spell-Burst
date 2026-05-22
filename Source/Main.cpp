#include "DxLib.h"
#include"Utility.h"
#include <EffekseerForDXLib.h>
// プログラムは WinMain から始まります
/*============================================================================================================================================
ビジュアルスタジオ2022から2026、2026から2022に変更する時のエラーは[プロジェクト->プロパティ->プラットホームツールセットをバージョンに合わせる]
=============================================================================================================================================*/




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{// ウインドウモードで起動
	ChangeWindowMode(true);

	SetGraphMode(Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, 32, 60);
	SetWindowSize(Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT);
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetGlobalAmbientLight(GetColorF(0.4f, 0.4f, 0.4f, 1.0f));
	//描画先設定を裏画面に設定する
	SetDrawScreen(DX_SCREEN_BACK);

	//Zバッファに書き込む準備
	SetUseZBufferFlag(true);
	SetWriteZBufferFlag(true);

	


	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		//画面を初期化する
		ClearDrawScreen();
		int time = GetNowCount();


		
		// 画面全体を少し明るくする
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);

		// 白い四角を画面全体に描画
		//
		DrawBox(0, 0, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, GetColor(255, 255, 255), TRUE);

		// ブレンドを戻す
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		//Master::mpScoreManager->Draw();




		//player->Draw();


		//裏画面の内容を表画面に映すwwwwwwwwwwwwww
		ScreenFlip();

		//１７ミリ秒（秒数間訳６０フレームだったっ場合１フレーム当たりの経過時間
		//経過するまでここで待つ
		while (GetNowCount() - time < 17)
		{
			//待つだけなのでここには何も書かない
		}

		

	}
	//終了処理
	

	Effkseer_End();


	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}