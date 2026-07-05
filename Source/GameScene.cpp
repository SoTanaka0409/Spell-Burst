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
    : enemy_manager_(nullptr)
    , cutin_timer_(0)
    , cutin_image_handle_(-1)
    , screen_handle_(-1)
    , shake_timer_(0)
    , shake_magnitude_(0.0f)
    , hit_stop_timer_(0)
{
}

GameScene::~GameScene() {
    if (enemy_manager_ != nullptr) {
        enemy_manager_.reset();
    }
    if (screen_handle_ != -1) {
        DeleteGraph(screen_handle_);
        screen_handle_ = -1;
    }
}

void GameScene::Initialize() {
    playFrameCount = 0;
    isTimeAttackActive = true;
    DebugLog("GameScene::Initialize() called!\n");
    srand(static_cast<unsigned int>(GetNowCount()));
    HUD::Initialize();

    enemy_manager_ = std::make_unique<EnemyManager>();
    enemy_manager_->Initialize();

    cutin_timer_ = 0;
    
    int charType = Player::kSelectedCharacterType;
    if (charType == 1) {
        cutin_image_handle_ = ResourceManager::GetInstance()->GetGraph("Resource/cutin_normal.png");
    } else if (charType == 2) {
        cutin_image_handle_ = ResourceManager::GetInstance()->GetGraph("Resource/cutin_girl.png");
    } else {
        cutin_image_handle_ = ResourceManager::GetInstance()->GetGraph("Resource/cutin_old.png");
    }

    screen_handle_ = MakeScreen(Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, TRUE);
    shake_timer_ = 0;
    shake_magnitude_ = 0.0f;
    hit_stop_timer_ = 0;

    new Player();

    enemy_manager_->SpawnEnemy(1330.0f, 150.0f);
    enemy_manager_->SpawnEnemy(1330.0f, 350.0f);
    enemy_manager_->SpawnEnemy(1330.0f, 550.0f);
    SoundManager::GetInstance()->PlayBGM("Resource/BGM/MusMus-BGM-170.3");
}

void GameScene::Update() {
    if (isTimeAttackActive) playFrameCount++;
    if (hit_stop_timer_ > 0) {
        hit_stop_timer_--;
        return; 
    }

    if (shake_timer_ > 0) {
        shake_timer_--;
    }

    if (cutin_timer_ > 0) {
        cutin_timer_--;
        return; 
    }

    Scene::Update();

    if (enemy_manager_ != nullptr) {
        enemy_manager_->Update();
    }
    
    Player* player = dynamic_cast<Player*>(GetObjectManager()->GetObject2DByTag(Object2D::kTag2dPlayer));
    Boss* boss = nullptr;
    for (auto obj : GetObjectManager()->GetObjectList()) {
        Boss* b = dynamic_cast<Boss*>(obj);
        if (b != nullptr) {
            boss = b;
            break;
        }
    }
    HUD::Update(player, enemy_manager_.get(), boss);

    if (DebugOn && InputManager::CheckDownKey(KEY_INPUT_RETURN)) {
        Master::sceneManager->SetNextScene(SceneManager::SCENE_RESULT);
    }
}

void GameScene::Draw() {
    if (screen_handle_ != -1) {
        SetDrawScreen(screen_handle_);
        ClearDrawScreen();
    }

    std::string bgPath = "Resource/background.png";
    if (enemy_manager_) {
        int phase_ = enemy_manager_->GetCurrentPhase();
        if (phase_ == 1) bgPath = "Resource/bg_phase1.png";
        else if (phase_ == 2) bgPath = "Resource/bg_phase2.png";
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

    Player* player = dynamic_cast<Player*>(GetObjectManager()->GetObject2DByTag(Object2D::kTag2dPlayer));
    Boss* boss = nullptr;
    for (auto obj : GetObjectManager()->GetObjectList()) {
        Boss* b = dynamic_cast<Boss*>(obj);
        if (b != nullptr) {
            boss = b;
            break;
        }
    }
    HUD::Draw(player, enemy_manager_.get(), boss, cutin_timer_, cutin_image_handle_);

    int totalMs = (playFrameCount * 1000) / 60;
    int ms = totalMs % 1000;
    int totalSec = totalMs / 1000;
    int sec = totalSec % 60;
    int min = totalSec / 60;
    char timeStr[64];
    sprintf_s(timeStr, "TIME %02d:%02d.%03d", min, sec, ms);
    DrawStringToHandle(Utility::SCREEN_WIDTH - 300, 20, timeStr, GetColor(255, 255, 255), ResourceManager::GetInstance()->GetFont(32, 2));

    if (screen_handle_ != -1) {
        SetDrawScreen(DX_SCREEN_BACK);

        int offsetX = 0;
        int offsetY = 0;
        if (shake_timer_ > 0) {
            offsetX = (rand() % static_cast<int>(shake_magnitude_ * 2)) - static_cast<int>(shake_magnitude_);
            offsetY = (rand() % static_cast<int>(shake_magnitude_ * 2)) - static_cast<int>(shake_magnitude_);
        }

        DrawGraph(offsetX, offsetY, screen_handle_, TRUE);
    }
}

void GameScene::AddScreenShake(int duration, float magnitude) {
    shake_timer_ = duration;
    shake_magnitude_ = magnitude;
}

void GameScene::AddHitStop(int duration) {
    hit_stop_timer_ = duration;
}

void GameScene::TriggerCutin() {
    cutin_timer_ = 90; 
}

void GameScene::Finalize() {
    DebugLog("GameScene::Finalize() called!\n");
    GetObjectManager()->DeleteAll2D();
}
