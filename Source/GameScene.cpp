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
#include <algorithm>
#include "Utility.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "HUD.h"

int GameScene::current_stage_ = 1;
int GameScene::play_frame_count_ = 0;
bool GameScene::is_time_attack_active_ = false;

/// @brief GameScene を生成する
GameScene::GameScene()
	: enemy_manager_(nullptr)
	, cutin_timer_(0)
	, cutin_image_handle_(-1)
	, screen_handle_(-1)
	, shake_timer_(0)
	, shake_magnitude_(0.0f)
	, hit_stop_timer_(0)
	, damage_flash_timer_(0)
	, damage_flash_color_(0)
{
}

/// @brief 破棄処理を行う
GameScene::~GameScene()
{
	if (enemy_manager_ != nullptr)
	{
		enemy_manager_.reset();
	}

	if (screen_handle_ != -1)
	{
		DeleteGraph(screen_handle_);
		screen_handle_ = -1;
	}
}

/// @brief 初期化処理を行う
void GameScene::Initialize()
{
	play_frame_count_ = 0;
	is_time_attack_active_ = true;
	DebugLog("GameScene::Initialize() called!\n");
	srand(static_cast<unsigned int>(GetNowCount()));
	HUD::Initialize();

	enemy_manager_ = std::make_unique<EnemyManager>();
	enemy_manager_->Initialize();

	cutin_timer_ = 0;

	int charType = Player::kSelectedCharacterType;
	if (charType == 1)
	{
		cutin_image_handle_ = ResourceManager::GetInstance()->GetGraph("IMG_CUTIN_NORMAL");
	}
	else if (charType == 2)
	{
		cutin_image_handle_ = ResourceManager::GetInstance()->GetGraph("IMG_CUTIN_GIRL");
	}
	else
	{
		cutin_image_handle_ = ResourceManager::GetInstance()->GetGraph("IMG_CUTIN_OLD");
	}

	screen_handle_ = MakeScreen(Utility::kScreenWidth, Utility::kScreenHeight, TRUE);
	shake_timer_ = 0;
	shake_magnitude_ = 0.0f;
	hit_stop_timer_ = 0;

	ObjectManager::Instantiate<Player>();

	enemy_manager_->SpawnEnemy(1330.0f, 150.0f);
	enemy_manager_->SpawnEnemy(1330.0f, 350.0f);
	enemy_manager_->SpawnEnemy(1330.0f, 550.0f);
	SoundManager::GetInstance()->PlayBGM("BGM_170");
}

/// @brief 毎フレームの更新処理を行う
void GameScene::Update()
{
	if (is_time_attack_active_) play_frame_count_++;

	if (hit_stop_timer_ > 0)
	{
		hit_stop_timer_--;
		return;
	}

	if (shake_timer_ > 0)
	{
		shake_timer_--;
	}

	if (damage_flash_timer_ > 0)
	{
		damage_flash_timer_--;
	}

	if (cutin_timer_ > 0)
	{
		cutin_timer_--;
		return;
	}

	Scene::Update();

	if (enemy_manager_ != nullptr)
	{
		enemy_manager_->Update();
	}

	Player* player = dynamic_cast<Player*>(GetObjectManager()->GetObject2DByTag(Object2D::kTag2dPlayer).get());
	Boss* boss = nullptr;
	for (auto obj : GetObjectManager()->GetObjectList())
	{
		Boss* b = dynamic_cast<Boss*>(obj.get());
		if (b != nullptr)
		{
			boss = b;
			break;
		}
	}
	HUD::Update(player, enemy_manager_.get(), boss);

	if (DebugOn && InputManager::CheckDownKey(KEY_INPUT_RETURN))
	{
		Master::sceneManager->SetNextScene(SceneManager::kSceneResult);
	}
}

/// @brief 描画処理を行う
void GameScene::Draw()
{
	if (screen_handle_ != -1)
	{
		SetDrawScreen(screen_handle_);
		ClearDrawScreen();
	}

	DrawBackground();
	Scene::Draw();

	Player* player = dynamic_cast<Player*>(GetObjectManager()->GetObject2DByTag(Object2D::kTag2dPlayer).get());
	Boss* boss = nullptr;
	for (auto obj : GetObjectManager()->GetObjectList())
	{
		Boss* b = dynamic_cast<Boss*>(obj.get());
		if (b != nullptr)
		{
			boss = b;
			break;
		}
	}
	HUD::Draw(player, enemy_manager_.get(), boss, cutin_timer_, cutin_image_handle_);

	DrawTimeAttackTimer();
	DrawEffects();
}

/// @brief DrawBackground を実行する
void GameScene::DrawBackground()
{
	std::string bgPath = "IMG_BG_TITLE";
	if (enemy_manager_)
	{
		int phase_ = enemy_manager_->GetCurrentPhase();
		if (phase_ == 1) bgPath = "IMG_BG_PHASE1";
		else if (phase_ == 2) bgPath = "IMG_BG_PHASE2";
		else bgPath = "IMG_BG_PHASE3";
	}

	int bgGraphHandle = ResourceManager::GetInstance()->GetGraph(bgPath);
	if (bgGraphHandle == -1)
	{
		bgGraphHandle = ResourceManager::GetInstance()->GetGraph("IMG_BG_TITLE");
	}

	if (bgGraphHandle != -1)
	{
		DrawExtendGraph(0, 0, Utility::kScreenWidth, Utility::kScreenHeight, bgGraphHandle, FALSE);
	}
}

/// @brief DrawTimeAttackTimer を実行する
void GameScene::DrawTimeAttackTimer()
{
	int totalMs = (play_frame_count_ * 1000) / 60;
	int ms = totalMs % 1000;
	int totalSec = totalMs / 1000;
	int sec = totalSec % 60;
	int min = totalSec / 60;
	char timeStr[64];
	sprintf_s(timeStr, "経過 %02d:%02d.%03d", min, sec, ms);
	DrawStringToHandle(Utility::kScreenWidth - 320, 70, timeStr, GetColor(255, 255, 255), ResourceManager::GetInstance()->GetFont(32, 2));
}

/// @brief DrawEffects を実行する
void GameScene::DrawEffects()
{
	if (screen_handle_ != -1)
	{
		SetDrawScreen(DX_SCREEN_BACK);

		int offsetX = 0;
		int offsetY = 0;
		int shakeRange = static_cast<int>(shake_magnitude_ * 2);
		if (shake_timer_ > 0 && shakeRange > 0)
		{
			offsetX = (rand() % shakeRange) - static_cast<int>(shake_magnitude_);
			offsetY = (rand() % shakeRange) - static_cast<int>(shake_magnitude_);
		}

		DrawGraph(offsetX, offsetY, screen_handle_, TRUE);

		if (damage_flash_timer_ > 0)
		{
			int max_flash = 15;
			int alpha = static_cast<int>(200.0f * (static_cast<float>(damage_flash_timer_) / max_flash));
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			DrawBox(0, 0, Utility::kScreenWidth, Utility::kScreenHeight, damage_flash_color_, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
}

/// @brief AddScreenShake を実行する
/// @param duration duration の値
/// @param magnitude magnitude の値
void GameScene::AddScreenShake(int duration, float magnitude)
{
	shake_timer_ = std::max(0, duration);
	shake_magnitude_ = std::max(0.0f, magnitude);
}

/// @brief AddHitStop を実行する
/// @param duration duration の値
void GameScene::AddHitStop(int duration)
{
	hit_stop_timer_ = duration;
}

/// @brief AddDamageFlash を実行する
/// @param duration duration の値
/// @param color color の値
void GameScene::AddDamageFlash(int duration, unsigned int color)
{
	damage_flash_timer_ = duration;
	damage_flash_color_ = color;
}

/// @brief TriggerCutin を実行する
void GameScene::TriggerCutin()
{
	cutin_timer_ = 90;
}

/// @brief 終了処理を行う
void GameScene::Finalize()
{
	DebugLog("GameScene::Finalize() called!\n");
	GetObjectManager()->DeleteAll2D();
}
