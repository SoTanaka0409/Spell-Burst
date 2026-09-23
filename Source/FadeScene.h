#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include <memory>

/// @brief シーン遷移時のフェードアウトを管理するシーン
class FadeScene : public Scene
{
public:
    /// @brief フェードシーンを生成する
    /// @param target_scene フェード完了後に遷移するシーン種別
    /// @param previous_scene フェード中に背景として描画する遷移前シーン
    FadeScene(SceneManager::SceneType target_scene, std::unique_ptr<Scene> previous_scene);

    /// @brief フェードシーンを初期化する
    void Initialize() override;

    /// @brief フェードシーンを更新する
    void Update() override;

    /// @brief フェードシーンを描画する
    void Draw() override;

    /// @brief フェードシーンを終了処理する
    void Finalize() override;

private:
    SceneManager::SceneType target_scene_; ///< フェード完了後に遷移するシーン種別
    std::unique_ptr<Scene> previous_scene_; ///< フェード中に背景として描画する遷移前シーン
    int fade_timer_;                       ///< フェード経過フレーム
    int fade_duration_;                    ///< フェードにかける総フレーム数
};