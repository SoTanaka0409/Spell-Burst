#include <memory>
#pragma once
#include "Scene.h"

// 現在のシーンと次に遷移するシーンを管理するクラス
class SceneManager
{
public:
    enum SceneType
    {
        kSceneNone = 0,
        kSceneReset,
        kSceneName,
        kSceneTitle,
        kSceneOperation,
        kSceneRule,
        kSceneTutorial,
        kSceneLevel,
        kSceneGame,
        kScene3dHard,
        kSceneResult,
        kSceneResultWin,
        kSceneNormalResultScene,
        kScene3d
    };

public:
    SceneManager();
    ~SceneManager();

    void Initialize();

    void Draw();

    void Update();

    void Finalize();

    void ChangeSceneIfNeeded();

    void SetNextScene(SceneType next) { next_scene_type_ = next; }

    void SetSceneHard(bool isHard) { is_scene_hard_ = isHard; }
    bool GetSceneHard() { return is_scene_hard_; }

    void SetSceneNormal(bool isNormal) { is_scene_normal_ = isNormal; }
    bool GetSceneNormal() { return is_scene_normal_; }

    Scene* GetCurrentScene() { return current_scene_.get(); }

private:
    SceneType scene_type_;           // 現在実行中のシーン
    SceneType next_scene_type_;      // 次に遷移するシーン
    std::unique_ptr<Scene> current_scene_; // 現在のシーンの所有ポインタ

    bool is_scene_hard_;             // HARD選択状態を保持するフラグ
    bool is_scene_normal_;           // NORMAL選択状態を保持するフラグ
};