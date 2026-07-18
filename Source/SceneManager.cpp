#include "SceneManager.h"
#include "ObjectManager.h"
#include "Scene.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "RuleScene.h"
#include "DebugLog.h"
#include "Master.h"
#include "SoundManager.h"

std::unique_ptr<SceneManager> Master::sceneManager = nullptr;

SceneManager::SceneManager()
	: scene_type_(SceneType::kSceneNone)
	, next_scene_type_(SceneType::kSceneNone)
	, is_scene_hard_(false)
	, is_scene_normal_(false)
{
}

SceneManager::~SceneManager()
{
	if (current_scene_ != nullptr)
	{
		current_scene_.reset();
	}
}

void SceneManager::Initialize()
{
	next_scene_type_ = SceneType::kSceneTitle;
	ChangeSceneIfNeeded();
}

void SceneManager::Update()
{
	ChangeSceneIfNeeded();
	if (current_scene_ != nullptr)
	{
		current_scene_->Update();
	}
}

void SceneManager::Draw()
{
	DebugLog("SceneManager::Draw() called! CurrentScene: %p\n", (void*)current_scene_.get());
	if (current_scene_ != nullptr)
	{
		current_scene_->Draw();
	}
}

void SceneManager::Finalize()
{
	if (current_scene_ != nullptr)
	{
		current_scene_->Finalize();
		current_scene_.reset();
	}
}

void SceneManager::ChangeSceneIfNeeded()
{
	if (scene_type_ == next_scene_type_)
	{
		return;
	}

	SoundManager::GetInstance()->StopBGM();

	if (current_scene_ != nullptr)
	{
		current_scene_->Finalize();
		current_scene_.reset();
	}

	scene_type_ = next_scene_type_;
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
	default:
		current_scene_ = nullptr;
		break;
	}

	if (current_scene_ != nullptr)
	{
		current_scene_->Initialize();
	}
}
