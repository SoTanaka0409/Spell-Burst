#include "DxLib.h"
#include"Scene.h"
#include"SceneManager.h"
#include"Master.h"

// ウィンドウサイズの設定
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

SceneManager* Master::sceneManager = new SceneManager();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // ウィンドウモードで起動（フルスクリーンにしない）
    ChangeWindowMode(TRUE);
    // 画面サイズの設定
    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
    // ウィンドウのタイトル設定
    SetMainWindowText("Shooting Action Game");

    // DXライブラリの初期化
    if (DxLib_Init() == -1) {
        return -1; // エラーが起きたら終了
    }

    // 描画先を裏画面に設定（ちらつき防止）
    SetDrawScreen(DX_SCREEN_BACK);

    // シーン管理クラスの生成
    Master::sceneManager->Initialize();

    // メインループ
    // ProcessMessage: Windowsのメッセージ処理（ウィンドウを閉じたり動かしたりするのに必須）
    // CheckHitKey(KEY_INPUT_ESCAPE) == 0: エスケープキーが押されていない間ループを続ける
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
        
        // 1. 画面をクリア（前のフレームの描画を消す）
        ClearDrawScreen();

      

        // 2. ゲームの更新（計算や入力処理）
        Master::sceneManager->Update();

        // 3. ゲームの描画（画像などを裏画面に描く）
        Master::sceneManager->Draw();

        // 4. 裏画面の内容を表画面に反映
        ScreenFlip();
    }

    // メモリの解放
    delete Master::sceneManager;

    // DXライブラリの終了処理
    DxLib_End();

    return 0;
}