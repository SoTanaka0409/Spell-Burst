#include "GameScene.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "Master.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Boss.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "DebugLog.h"
#include <cstdlib>
#include "Utility.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "HUD.h"

int GameScene::currentStage = 1;
int GameScene::playFrameCount = 0;
bool GameScene::isTimeAttackActive = false;

GameScene::GameScene() 
    : enemyManager(nullptr)
    , cutinTimer(0)
    , cutinImageHandle(-1)
    , screenHandle(-1)
    , shakeTimer(0)
    , shakeMagnitude(0.0f)
    , hitStopTimer(0)
{
}

GameScene::~GameScene() {
    if (enemyManager != nullptr) {
        enemyManager.reset();
    }
    if (screenHandle != -1) {
        DeleteGraph(screenHandle);
        screenHandle = -1;
    }
}

void GameScene::Initialize() {
    playFrameCount = 0;
    isTimeAttackActive = true;
    DebugLog("GameScene::Initialize() called!\n");
    srand(static_cast<unsigned int>(GetNowCount()));
    HUD::Initialize();

    enemyManager = std::make_unique<EnemyManager>();
    enemyManager->Initialize();

    cutinTimer = 0;
    
    int charType = Player::selectedCharacterType;
    if (charType == 1) {
        cutinImageHandle = ResourceManager::GetInstance()->GetGraph("Resource/cutin_normal.png");
    } else if (charType == 2) {
        cutinImageHandle = ResourceManager::GetInstance()->GetGraph("Resource/cutin_girl.png");
    } else {
        cutinImageHandle = ResourceManager::GetInstance()->GetGraph("Resource/cutin_old.png");
    }

    screenHandle = MakeScreen(Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, TRUE);
    shakeTimer = 0;
    shakeMagnitude = 0.0f;
    hitStopTimer = 0;

    new Player();

    enemyManager->SpawnEnemy(1330.0f, 150.0f);
    enemyManager->SpawnEnemy(1330.0f, 350.0f);
    enemyManager->SpawnEnemy(1330.0f, 550.0f);
    SoundManager::GetInstance()->PlayBGM("Resource/BGM/MusMus-BGM-170.3");
}

void GameScene::Update() {
    if (isTimeAttackActive) playFrameCount++;
    if (hitStopTimer > 0) {
        hitStopTimer--;
        return; 
    }

    if (shakeTimer > 0) {
        shakeTimer--;
    }

    if (cutinTimer > 0) {
        cutinTimer--;
        return; 
    }

    Scene::Update();

    if (enemyManager != nullptr) {
        enemyManager->Update();
    }
    
    Player* player = dynamic_cast<Player*>(GetObjectManager()->GetObject2DByTag(Object2D::Tag2D_Player));
    Boss* boss = nullptr;
    for (auto obj : GetObjectManager()->GetObjectList()) {
        Boss* b = dynamic_cast<Boss*>(obj);
        if (b != nullptr) {
            boss = b;
            break;
        }
    }
    HUD::Update(player, enemyManager.get(), boss);

    if (DebugOn && InputManager::CheckDownKey(KEY_INPUT_RETURN)) {
        Master::sceneManager->SetNextScene(SceneManager::SCENE_RESULT);
    }
}

void GameScene::Draw() {
    if (screenHandle != -1) {
        SetDrawScreen(screenHandle);
        ClearDrawScreen();
    }

    std::string bgPath = "Resource/background.png";
    if (enemyManager) {
        int phase = enemyManager->GetCurrentPhase();
        if (phase == 1) bgPath = "Resource/bg_phase1.png";
        else if (phase == 2) bgPath = "Resource/bg_phase2.png";
        else bgPath = "Resource/bg_phase3.png";
    }
    
    int bgGraphHandle = ResourceManager::GetInstance()->GetGraph(bgPath);
    if (bgGraphHandle == -1) {
        bgGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/background.png");
    }
    
    if (bgGraphHandle != -1) {
        DrawExtendGraph(0, 0, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, bgGraphHandle, FALSE);
    }

    Scene::Draw();

    Player* player = dynamic_cast<Player*>(GetObjectManager()->GetObject2DByTag(Object2D::Tag2D_Player));
    Boss* boss = nullptr;
    for (auto obj : GetObjectManager()->GetObjectList()) {
        Boss* b = dynamic_cast<Boss*>(obj);
        if (b != nullptr) {
            boss = b;
            break;
        }
    }
    HUD::Draw(player, enemyManager.get(), boss, cutinTimer, cutinImageHandle);

    int totalMs = (playFrameCount * 1000) / 60;
    int ms = totalMs % 1000;
    int totalSec = totalMs / 1000;
    int sec = totalSec % 60;
    int min = totalSec / 60;
    char timeStr[64];
    sprintf_s(timeStr, "TIME %02d:%02d.%03d", min, sec, ms);
    DrawStringToHandle(Utility::SCREEN_WIDTH - 300, 20, timeStr, GetColor(255, 255, 255), ResourceManager::GetInstance()->GetFont(32, 2));

    if (screenHandle != -1) {
        SetDrawScreen(DX_SCREEN_BACK);

        int offsetX = 0;
        int offsetY = 0;
        if (shakeTimer > 0) {
            offsetX = (rand() % static_cast<int>(shakeMagnitude * 2)) - static_cast<int>(shakeMagnitude);
            offsetY = (rand() % static_cast<int>(shakeMagnitude * 2)) - static_cast<int>(shakeMagnitude);
        }

        DrawGraph(offsetX, offsetY, screenHandle, TRUE);
    }
}

void GameScene::AddScreenShake(int duration, float magnitude) {
    shakeTimer = duration;
    shakeMagnitude = magnitude;
}

void GameScene::AddHitStop(int duration) {
    hitStopTimer = duration;
}

void GameScene::TriggerCutin() {
    cutinTimer = 90; 
}

void GameScene::Finalize() {
    DebugLog("GameScene::Finalize() called!\n");
    GetObjectManager()->DeleteAll2D();
}
