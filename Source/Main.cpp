#include "DxLib.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Master.h"
#include <iostream>
#include "Utility.h"


//SceneManager* Master::sceneManager = new SceneManager();

float Utility::TimeScale = 1.0f;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Truncate log file
    FILE* fpLog = nullptr;
    fopen_s(&fpLog, "debug.log", "w");
    if (fpLog) fclose(fpLog);

    // Start debug console
    AllocConsole();
    FILE* fp = nullptr;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
    printf("Debug Console Started!\n");

    // Init DX Library
    SetOutApplicationLogValidFlag(FALSE);
    ChangeWindowMode(TRUE);
    SetGraphMode(Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, 32);
    SetMainWindowText("Shooting Action Game");

    if (DxLib_Init() == -1) {
        return -1;
    }

    SetDrawScreen(DX_SCREEN_BACK);

    Master::sceneManager = new SceneManager();
    Master::sceneManager->Initialize();

    LONGLONG lastTime = GetNowHiPerformanceCount();

    // Main loop
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
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