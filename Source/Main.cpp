#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Master.h"
#include <iostream>
#include "Utility.h"
#include "InputAction.h"

//SceneManager* Master::sceneManager = std::make_unique<SceneManager>();

float Utility::time_scale_ = 1.0f;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    if (GetFileAttributesA("Resource") == INVALID_FILE_ATTRIBUTES)
    {
        if (GetFileAttributesA("..\\..\\Resource") != INVALID_FILE_ATTRIBUTES)
        {
            SetCurrentDirectoryA("..\\..");
        }
    }

    FILE* fpLog = nullptr;
    fopen_s(&fpLog, "debug.log", "w");
    if (fpLog) fclose(fpLog);

    AllocConsole();
    FILE* fp = nullptr;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
    printf("Debug Console Started!\n");

    SetOutApplicationLogValidFlag(FALSE);
    ChangeWindowMode(TRUE);
    SetGraphMode(Utility::kScreenWidth, Utility::kScreenHeight, 32);
    SetMainWindowText("Shooting Action Game");

    if (DxLib_Init() == -1)
    {
        return -1;
    }

    // 描画先を裏画面に設定し、チラつき�EなぁE��ブルバッファリングを実現`r`n    SetDrawScreen(DX_SCREEN_BACK);

    Master::sceneManager = std::make_unique<SceneManager>();
    InputBinding::Initialize();
    Master::sceneManager->Initialize();

    LONGLONG lastTime = GetNowHiPerformanceCount();

    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && Master::sceneManager->GetCurrentScene() != nullptr)
    {
        ClearDrawScreen();

        LONGLONG currentTime = GetNowHiPerformanceCount();
        Utility::time_scale_ = (float)(currentTime - lastTime) / (1000000.0f / 60.0f);
        if (Utility::time_scale_ > 3.0f) Utility::time_scale_ = 3.0f;
        lastTime = currentTime;

        Master::sceneManager->Update();
        Master::sceneManager->Draw();

        ScreenFlip();
    }

    

    DxLib_End();

    return 0;
}
