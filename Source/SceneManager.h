#include <memory>
#pragma once
#include "Scene.h"

/// @brief 現在のシーンと次に遷移するシーンを管理するクラス
class SceneManager
{
public:
    /// @brief シーン種別
    enum SceneType
    {
        kSceneNone = 0,          ///< シーンなし
        kSceneReset,             ///< リセットシーン
        kSceneName,              ///< 名前入力シーン
        kSceneTitle,             ///< タイトルシーン
        kSceneOperation,         ///< 操作説明シーン
        kSceneRule,              ///< ルール説明シーン
        kSceneTutorial,          ///< チュートリアルシーン
        kSceneLevel,             ///< レベル選択シーン
        kSceneGame,              ///< ゲーム本編シーン
        kScene3dHard,            ///< 3Dハードシーン
        kSceneResult,            ///< リザルトシーン
        kSceneResultWin,         ///< 勝利リザルトシーン
        kSceneNormalResultScene, ///< 通常リザルトシーン
        kScene3d,                ///< 3Dシーン
        kSceneConfig,            ///< 設定シーン
        kSceneFade               ///< シーン遷移用フェードシーン
    };

public:
    /// @brief シーン管理クラスを生成する
    SceneManager();

    /// @brief シーン管理クラスを破棄する
    ~SceneManager();

    /// @brief 初期シーンを準備する
    void Initialize();

    /// @brief 現在シーンを描画する
    void Draw();

    /// @brief 現在シーンを更新する
    void Update();

    /// @brief 現在シーンを終了処理する
    void Finalize();

    /// @brief 予約されている次シーンへ必要に応じて切り替える
    void ChangeSceneIfNeeded();

    /// @brief 次に遷移するシーンを設定する
    /// @param next 次シーン種別
    void SetNextScene(SceneType next);

    /// @brief フェードを挟まずに次に遷移するシーンを設定する
    /// @param next 次シーン種別
    void SetNextSceneImmediately(SceneType next) { next_scene_type_ = next; }

    /// @brief HARD選択状態を設定する
    /// @param isHard HARDならtrue
    void SetSceneHard(bool isHard) { is_scene_hard_ = isHard; }

    /// @brief HARD選択状態を取得する
    /// @return bool HARDならtrue
    bool GetSceneHard() { return is_scene_hard_; }

    /// @brief NORMAL選択状態を設定する
    /// @param isNormal NORMALならtrue
    void SetSceneNormal(bool isNormal) { is_scene_normal_ = isNormal; }

    /// @brief NORMAL選択状態を取得する
    /// @return bool NORMALならtrue
    bool GetSceneNormal() { return is_scene_normal_; }

    /// @brief 現在のシーンを取得する
    /// @return Scene* 現在シーン
    Scene* GetCurrentScene() { return current_scene_.get(); }

private:
    SceneType scene_type_;                  ///< 現在実行中のシーン
    SceneType next_scene_type_;             ///< 次に遷移するシーン
    SceneType fade_target_scene_type_;      ///< フェード完了後に遷移するシーン
    std::unique_ptr<Scene> current_scene_;  ///< 現在のシーンの所有ポインタ
    bool is_scene_hard_;                    ///< HARD選択状態を保持するフラグ
    bool is_scene_normal_;                  ///< NORMAL選択状態を保持するフラグ
};