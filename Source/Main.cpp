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

float Utility::TimeScale = 1.0f;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    if (GetFileAttributesA("Resource") == INVALID_FILE_ATTRIBUTES)
    {
        if (GetFileAttributesA("..\\..\\Resource") != INVALID_FILE_ATTRIBUTES)
        {
            SetCurrentDirectoryA("..\\..");
        }
    }

    // 襍ｷ蜍墓ｯ弱↓譛譁ｰ縺ｮ繝ｭ繧ｰ繧貞・蜉帙☆繧九◆繧√∵里蟄倥・繝ｭ繧ｰ繝輔ぃ繧､繝ｫ繧堤ｴ譽・＠縺ｦ蛻晄悄蛹・
    FILE* fpLog = nullptr;
    fopen_s(&fpLog, "debug.log", "w");
    if (fpLog) fclose(fpLog);

    // 髢狗匱荳ｭ縺ｮ蜍穂ｽ懃｢ｺ隱阪♀繧医・繧ｨ繝ｩ繝ｼ隱ｿ譟ｻ繧貞ｮｹ譏薙↓縺吶ｋ縺溘ａ繧ｳ繝ｳ繧ｽ繝ｼ繝ｫ繧貞牡繧雁ｽ薙※
    AllocConsole();
    FILE* fp = nullptr;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
    printf("Debug Console Started!\n");

    // DxLib縺ｮ蝓ｺ譛ｬ險ｭ螳壹♀繧医・蛻晄悄蛹厄ｼ医Ο繧ｰ繝輔ぃ繧､繝ｫ蜃ｺ蜉帙ｒ辟｡蜉ｹ蛹厄ｼ・
    SetOutApplicationLogValidFlag(FALSE);
    ChangeWindowMode(TRUE);
    SetGraphMode(Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, 32);
    SetMainWindowText("Shooting Action Game");

    if (DxLib_Init() == -1)
    {
        return -1;
    }

    // 謠冗判蜈医ｒ陬冗判髱｢縺ｫ險ｭ螳壹＠縲√メ繝ｩ縺､縺阪・縺ｪ縺・ム繝悶Ν繝舌ャ繝輔ぃ繝ｪ繝ｳ繧ｰ繧貞ｮ溽樟`r`n    SetDrawScreen(DX_SCREEN_BACK);

    Master::sceneManager = std::make_unique<SceneManager>();
    InputBinding::Initialize();
    Master::sceneManager->Initialize();

    LONGLONG lastTime = GetNowHiPerformanceCount();

    // OS縺ｮ繝｡繝・そ繝ｼ繧ｸ蜃ｦ逅・→ESC繧ｭ繝ｼ縺ｫ繧医ｋ螳牙・縺ｪ邨ゆｺ・ｒ菫晁ｨｼ縺吶ｋ縺溘ａ縺ｮ繝｡繧､繝ｳ繝ｫ繝ｼ繝・
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && Master::sceneManager->GetCurrentScene() != nullptr)
    {
        ClearDrawScreen();

        LONGLONG currentTime = GetNowHiPerformanceCount();
        Utility::TimeScale = (float)(currentTime - lastTime) / (1000000.0f / 60.0f);
        if (Utility::TimeScale > 3.0f) Utility::TimeScale = 3.0f;
        lastTime = currentTime;

        Master::sceneManager->Update();
        Master::sceneManager->Draw();

        ScreenFlip();
    }

    

    DxLib_End();

    return 0;
}
