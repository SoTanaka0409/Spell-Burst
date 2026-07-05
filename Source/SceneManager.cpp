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
	: scene_type_(SCENE_TYPE::SCENE_NONE)
	, next_scene_type_(SCENE_TYPE::SCENE_NONE)
	, kSceneHard(false)
	, kSceneNormal(false)
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
	next_scene_type_ = SCENE_TYPE::SCENE_TITLE;
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
	case SCENE_TYPE::SCENE_TITLE:
		current_scene_ = std::make_unique<TitleScene>();
		break;
	case SCENE_TYPE::SCENE_LEVEL:
		current_scene_ = std::make_unique<StageSelectScene>();
		break;
	case SCENE_TYPE::SCENE_GAME:
		current_scene_ = std::make_unique<GameScene>();
		break;
	case SCENE_TYPE::SCENE_RESULT:
		current_scene_ = std::make_unique<ResultScene>();
		break;
	case SCENE_TYPE::SCENE_RULE:
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
