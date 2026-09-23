#pragma once
#include "Scene.h"
#include <vector>

/// @brief タイトル画面とランキング表示を管理するシーン
class TitleScene : public Scene
{
public:
    /// @brief タイトルシーンを生成する
    TitleScene();

    /// @brief タイトルシーンを破棄する
    ~TitleScene();

    /// @brief タイトルシーンを初期化する
    void Initialize() override;

    /// @brief タイトルシーンを更新する
    void Update() override;

    /// @brief タイトルシーンを描画する
    void Draw() override;

    /// @brief タイトルシーンを終了処理する
    void Finalize() override;

private:
    /// @brief ランキングを描画する
    void DrawRankings();

    /// @brief タイトルロゴを描画する
    void DrawTitleLogo();

    /// @brief メニュー用ボタンを描画する
    /// @param mouseX マウスX座標
    /// @param mouseY マウスY座標
    void DrawButtons(int mouseX, int mouseY);

private:
    int bg_graph_;              ///< 背景画像ハンドル
    float bg_scroll_x_;         ///< 背景スクロール位置
    int ui_button_graph_;       ///< ボタン画像ハンドル
    std::vector<int> rankings_; ///< 読み込んだランキング記録
};