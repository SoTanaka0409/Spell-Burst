#include "SceneManager.h"
#include "ObjectManager.h"
#include "Scene.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "RuleScene.h"
#include "ConfigScene.h"
#include "FadeScene.h"
#include "DebugLog.h"
#include "Master.h"
#include "SoundManager.h"

std::unique_ptr<SceneManager> Master::sceneManager = nullptr;

/// @brief SceneManager を生成する
SceneManager::SceneManager()
	: scene_type_(SceneType::kSceneNone)
	, next_scene_type_(SceneType::kSceneNone)
	, fade_target_scene_type_(SceneType::kSceneNone)
	, is_scene_hard_(false)
	, is_scene_normal_(false)
{
}

/// @brief 破棄処理を行う
SceneManager::~SceneManager()
{
	if (current_scene_ != nullptr)
	{
		current_scene_.reset();
	}
}

/// @brief 初期化処理を行う
void SceneManager::Initialize()
{
	next_scene_type_ = SceneType::kSceneTitle;
	ChangeSceneIfNeeded();
}

/// @brief 次に遷移するシーンを設定する
/// @param next 次シーン種別
void SceneManager::SetNextScene(SceneType next)
{
	if (scene_type_ == SceneType::kSceneNone || scene_type_ == SceneType::kSceneFade)
	{
		next_scene_type_ = next;
		return;
	}

	if (scene_type_ == next)
	{
		return;
	}

	fade_target_scene_type_ = next;
	next_scene_type_ = SceneType::kSceneFade;
}

/// @brief 毎フレームの更新処理を行う
void SceneManager::Update()
{
	ChangeSceneIfNeeded();
	if (current_scene_ != nullptr)
	{
		current_scene_->Update();
	}
}

/// @brief 描画処理を行う
void SceneManager::Draw()
{
	DebugLog("SceneManager::Draw() called! CurrentScene: %p\n", (void*)current_scene_.get());
	if (current_scene_ != nullptr)
	{
		current_scene_->Draw();
	}
}

/// @brief 終了処理を行う
void SceneManager::Finalize()
{
	if (current_scene_ != nullptr)
	{
		current_scene_->Finalize();
		current_scene_.reset();
	}
}

/// @brief ChangeSceneIfNeeded を実行する
void SceneManager::ChangeSceneIfNeeded()
{
	if (scene_type_ == next_scene_type_)
	{
		return;
	}

	SoundManager::GetInstance()->StopBGM();

	SceneType new_scene_type = next_scene_type_;
	if (new_scene_type == SceneType::kSceneFade)
	{
		scene_type_ = new_scene_type;
		current_scene_ = std::make_unique<FadeScene>(fade_target_scene_type_, std::move(current_scene_));
		if (current_scene_ != nullptr)
		{
			current_scene_->Initialize();
		}
		return;
	}

	if (current_scene_ != nullptr)
	{
		current_scene_->Finalize();
		current_scene_.reset();
	}

	scene_type_ = new_scene_type;
	switch (scene_type_)
	{
	case SceneType::kSceneTitle:
		current_scene_ = std::make_unique<TitleScene>();
		break;
	case SceneType::kSceneLevel:
		current_scene_ = std::make_unique<StageSelectScene>();
		break;
	case SceneType::kSceneGame:
		current_scene_ = std::make_unique<GameScene>();
		break;
	case SceneType::kSceneResult:
		current_scene_ = std::make_unique<ResultScene>();
		break;
	case SceneType::kSceneRule:
		current_scene_ = std::make_unique<RuleScene>();
		break;
	case SceneType::kSceneConfig:
		current_scene_ = std::make_unique<ConfigScene>();
		break;
	case SceneType::kSceneFade:
		current_scene_ = std::make_unique<FadeScene>(fade_target_scene_type_, nullptr);
		break;
	default:
		current_scene_ = nullptr;
		break;
	}

	if (current_scene_ != nullptr)
	{
		current_scene_->Initialize();
	}
}
