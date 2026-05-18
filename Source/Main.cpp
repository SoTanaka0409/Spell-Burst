#include "DxLib.h"
#include"Master.h"
#include"Camera.h"
#include"SceneManager.h"
#include"ObjectManager.h"
#include"ResourceManager.h"
#include"SoundManager.h"
#include"ColliderManager.h"
#include "Utility.h"
#include"Score.h"

#include"EffectManager.h"
#include"Fever.h"
#include <EffekseerForDXLib.h>
// プログラムは WinMain から始まります
/*============================================================================================================================================
ビジュアルスタジオ2022から2026、2026から2022に変更する時のエラーは[プロジェクト->プロパティ->プラットホームツールセットをバージョンに合わせる]
=============================================================================================================================================*/


SceneManager* Master::mpSceneManager = new SceneManager();
Camera* Master::mpCamera = new Camera();
ResourceManager* Master::mpResourceManager = new ResourceManager();
SoundManager* Master::mpSoundManager = new SoundManager();

EffectManager* Master::mpEffectManager = new EffectManager();

Score* Master::mpScore = new Score();
bool Master::SelectSkill = false;
int Master::mnTutorialcount = 0;
bool Master::GameFinishFlag = false;
bool Master::TutrialVacumFlag = false;

VECTOR Utility::StageSize= VGet(8000, 0, 8000);//stageサイズの取得

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

	Master::mpSoundManager->Initialize();//すべてのサウンドが読み込まれru----

	//シーンマネージャーの生成と初期化
	Master::mpSceneManager->Initialize();
	
	//カメラの更新
	Master::mpCamera->Initialize();

	Master::mpEffectManager->Initalize();


	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		//画面を初期化する
		ClearDrawScreen();
		int time = GetNowCount();


		Master::mpCamera->Update();

		Master::mpEffectManager->Update();

		//更新
		Master::mpSceneManager->Update();
		

		//player->Update();
		//描画
		Master::mpSceneManager->Draw();
		
		Master::mpEffectManager->Draw();

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

		//削除する必要のあるオブジェクトがあれば削除する
		Master::mpSceneManager->GetCurrentScene()->GetCollisionManager()->DeleteAllColliderIfNeeded();
		Master::mpSceneManager->GetCurrentScene()->GetObjectManager()->DeleteAll3DIfNeeded();


		//ループする直前にシーン遷移チェックを入れておく
		Master::mpSceneManager->ChangeSceneIfNeeded();


	}
	//終了処理
	Master::mpSceneManager->Finalize();
	delete Master::mpSceneManager;
	Master::mpSoundManager->Finalize();
	delete Master::mpSoundManager;
	Master::mpCamera->Finalize();
	delete Master::mpCamera;
	delete Master::mpResourceManager;

	ColliderManager::GetInstance()->Finalize();
	


	Effkseer_End();


	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}