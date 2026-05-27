#include "GameScene.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "Master.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Boss.h"
#include <DxLib.h>
#include "DebugLog.h"
#include <cstdlib>
#include "Utility.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "HUD.h"

int GameScene::s_currentStage = 1;

GameScene::GameScene() 
    : mpEnemyManager(nullptr)
    , m_cutinTimer(0)
    , m_cutinImageHandle(-1)
    , m_screenHandle(-1)
    , m_shakeTimer(0)
    , m_shakeMagnitude(0.0f)
    , m_hitStopTimer(0)
{
}

GameScene::~GameScene() {
    if (mpEnemyManager != nullptr) {
        delete mpEnemyManager;
        mpEnemyManager = nullptr;
    }
    if (m_screenHandle != -1) {
        DeleteGraph(m_screenHandle);
        m_screenHandle = -1;
    }
}

void GameScene::Initialize() {
    DebugLog("GameScene::Initialize() called!\n");
    srand(static_cast<unsigned int>(GetNowCount()));
    HUD::Initialize();

    mpEnemyManager = new EnemyManager();
    mpEnemyManager->Initialize();

    m_cutinTimer = 0;
    
    int charType = Player::s_selectedCharacterType;
    if (charType == 1) {
        m_cutinImageHandle = ResourceManager::GetInstance()->GetGraph("Resource/cutin_normal.png");
    } else if (charType == 2) {
        m_cutinImageHandle = ResourceManager::GetInstance()->GetGraph("Resource/cutin_girl.png");
    } else {
        m_cutinImageHandle = ResourceManager::GetInstance()->GetGraph("Resource/cutin_old.png");
    }

    m_screenHandle = MakeScreen(Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, TRUE);
    m_shakeTimer = 0;
    m_shakeMagnitude = 0.0f;
    m_hitStopTimer = 0;

    new Player();

    mpEnemyManager->SpawnEnemy(1330.0f, 150.0f);
    mpEnemyManager->SpawnEnemy(1330.0f, 350.0f);
    mpEnemyManager->SpawnEnemy(1330.0f, 550.0f);
    SoundManager::GetInstance()->PlayBGM("Resource/BGM/MusMus-BGM-170.mp3");
}

void GameScene::Update() {
    if (m_hitStopTimer > 0) {
        m_hitStopTimer--;
        return; 
    }

    if (m_shakeTimer > 0) {
        m_shakeTimer--;
    }

    if (m_cutinTimer > 0) {
        m_cutinTimer--;
        return; 
    }

    Scene::Update();

    if (mpEnemyManager != nullptr) {
        mpEnemyManager->Update();
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
    HUD::Update(player, mpEnemyManager, boss);

    if (InputManager::CheckDownKey(KEY_INPUT_RETURN)) {
        Master::sceneManager->SetNextScene(SceneManager::SCENE_RESULT);
    }
}

void GameScene::Draw() {
    if (m_screenHandle != -1) {
        SetDrawScreen(m_screenHandle);
        ClearDrawScreen();
    }

    std::string bgPath = "Resource/background.png";
    if (mpEnemyManager) {
        int phase = mpEnemyManager->GetCurrentPhase();
        if (phase == 1) bgPath = "Resource/bg_phase1.png";
        else if (phase == 2) bgPath = "Resource/bg_phase2.png";
        else bgPath = "Resource/bg_phase3.png";
    }
    
    int s_bgGraphHandle = ResourceManager::GetInstance()->GetGraph(bgPath);
    // 指定の背景が見つからない場合はデフォルトのbackground.pngを使用
    if (s_bgGraphHandle == -1) {
        s_bgGraphHandle = ResourceManager::GetInstance()->GetGraph("Resource/background.png");
    }
    
    if (s_bgGraphHandle != -1) {
        DrawExtendGraph(0, 0, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, s_bgGraphHandle, FALSE);
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
    HUD::Draw(player, mpEnemyManager, boss, m_cutinTimer, m_cutinImageHandle);

    if (m_screenHandle != -1) {
        SetDrawScreen(DX_SCREEN_BACK);

        int offsetX = 0;
        int offsetY = 0;
        if (m_shakeTimer > 0) {
            offsetX = (rand() % static_cast<int>(m_shakeMagnitude * 2)) - static_cast<int>(m_shakeMagnitude);
            offsetY = (rand() % static_cast<int>(m_shakeMagnitude * 2)) - static_cast<int>(m_shakeMagnitude);
        }

        DrawGraph(offsetX, offsetY, m_screenHandle, TRUE);
    }
}

void GameScene::AddScreenShake(int duration, float magnitude) {
    m_shakeTimer = duration;
    m_shakeMagnitude = magnitude;
}

void GameScene::AddHitStop(int duration) {
    m_hitStopTimer = duration;
}

void GameScene::TriggerCutin() {
    m_cutinTimer = 90; 
}

void GameScene::Finalize() {
    DebugLog("GameScene::Finalize() called!\n");
    GetObjectManager()->DeleteAll2D();
}
