#include "DxLib.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Master.h"
#include <iostream>
#include "Utility.h"


//SceneManager* Master::sceneManager = new SceneManager();

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
    ChangeWindowMode(TRUE);
    SetGraphMode(Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, 32);
    SetMainWindowText("Shooting Action Game");

    if (DxLib_Init() == -1) {
        return -1;
    }

    SetDrawScreen(DX_SCREEN_BACK);

    Master::sceneManager->Initialize();

    // Main loop
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
        ClearDrawScreen();

        Master::sceneManager->Update();
        Master::sceneManager->Draw();

        ScreenFlip();
    }

    delete Master::sceneManager;

    DxLib_End();

    return 0;
}