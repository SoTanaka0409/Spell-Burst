#include "FadeScene.h"
#include "Master.h"
#include "Utility.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <utility>

/// @brief FadeScene を生成する
/// @param target_scene フェード完了後に遷移するシーン種別
/// @param previous_scene フェード中に背景として描画する遷移前シーン
FadeScene::FadeScene(SceneManager::SceneType target_scene, std::unique_ptr<Scene> previous_scene)
    : target_scene_(target_scene)
    , previous_scene_(std::move(previous_scene))
    , fade_timer_(0)
    , fade_duration_(45)
{
}

/// @brief 初期化処理を行う
void FadeScene::Initialize()
{
    fade_timer_ = 0;
}

/// @brief 毎フレームの更新処理を行う
void FadeScene::Update()
{
    fade_timer_++;
    if (fade_timer_ >= fade_duration_)
    {
        Master::sceneManager->SetNextSceneImmediately(target_scene_);
    }
}

/// @brief 描画処理を行う
void FadeScene::Draw()
{
    if (previous_scene_ != nullptr)
    {
        previous_scene_->Draw();
    }

    int alpha = fade_timer_ * 255 / fade_duration_;
    if (alpha > 255)
    {
        alpha = 255;
    }

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    DrawBox(0, 0, Utility::kScreenWidth, Utility::kScreenHeight, GetColor(0, 0, 0), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

/// @brief 終了処理を行う
void FadeScene::Finalize()
{
    if (previous_scene_ != nullptr)
    {
        previous_scene_->Finalize();
        previous_scene_.reset();
    }
}