#pragma once
#include "Scene.h"

/// @brief ゲームのルールや操作方法をスライド形式で説明するシーン
class RuleScene : public Scene
{
public:
    /// @brief ルールシーンを初期化する
    void Initialize() override;

    /// @brief ルールシーンを更新する
    void Update() override;

    /// @brief ルールシーンを描画する
    void Draw() override;

    /// @brief ルールシーンを終了処理する
    void Finalize() override;

private:
    /// @brief ルール説明テキストを描画する
    /// @param titleFont タイトル用フォントハンドル
    /// @param font24 本文用フォントハンドル
    void DrawRuleText(int titleFont, int font24);

    /// @brief ページ移動ボタンを描画する
    /// @param mouseX マウスX座標
    /// @param mouseY マウスY座標
    /// @param font24 ボタン用フォントハンドル
    void DrawNavigationButtons(int mouseX, int mouseY, int font24);

    int rule_graphs_[6]; ///< 各ページのルール画像ハンドル
    int current_slide_;  ///< 現在表示中のページ番号
};