#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Master.h"
#include <iostream>
#include "Utility.h"


//SceneManager* Master::sceneManager = new SceneManager();

float Utility::TimeScale = 1.0f;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // 起動毎に最新のログを出力するため、既存のログファイルを破棄して初期化
    FILE* fpLog = nullptr;
    fopen_s(&fpLog, "debug.log", "w");
    if (fpLog) fclose(fpLog);

    // 開発中の動作確認およびエラー調査を容易にするためコンソールを割り当て
    AllocConsole();
    FILE* fp = nullptr;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
    printf("Debug Console Started!\n");

    // DxLibの基本設定および初期化（ログファイル出力を無効化）
    SetOutApplicationLogValidFlag(FALSE);
    ChangeWindowMode(TRUE);
    SetGraphMode(Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, 32);
    SetMainWindowText("Shooting Action Game");

    if (DxLib_Init() == -1) {
        return -1;
    }

    // 描画先を裏画面に設定し、チラつきのないダブルバッファリングを実現`r`n    SetDrawScreen(DX_SCREEN_BACK);

    Master::sceneManager = new SceneManager();
    Master::sceneManager->Initialize();

    LONGLONG lastTime = GetNowHiPerformanceCount();

    // OSのメッセージ処理とESCキーによる安全な終了を保証するためのメインループ
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && Master::sceneManager->GetCurrentScene() != nullptr) {
        ClearDrawScreen();

        LONGLONG currentTime = GetNowHiPerformanceCount();
        Utility::TimeScale = (float)(currentTime - lastTime) / (1000000.0f / 60.0f);
        if (Utility::TimeScale > 3.0f) Utility::TimeScale = 3.0f;
        lastTime = currentTime;

        Master::sceneManager->Update();
        Master::sceneManager->Draw();

        ScreenFlip();
    }

    delete Master::sceneManager;

    DxLib_End();

    return 0;
}