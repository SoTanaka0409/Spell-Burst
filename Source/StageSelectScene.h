#pragma once
#include "Scene.h"

/// @brief キャラクター選択とステージ選択を管理するシーン
class StageSelectScene : public Scene
{
public:
    /// @brief ステージ選択シーンを初期化する
    void Initialize() override;

    /// @brief ステージ選択シーンを更新する
    void Update() override;

    /// @brief ステージ選択シーンを描画する
    void Draw() override;

    /// @brief ステージ選択シーンを終了処理する
    void Finalize() override;

private:
    /// @brief キャラクター選択入力を更新する
    /// @param mouseX マウスX座標
    /// @param mouseY マウスY座標
    /// @param isLeftClicked 左クリックされたか
    /// @param cx 画面中心X座標
    /// @param cy 画面中心Y座標
    void UpdateCharacterSelect(int mouseX, int mouseY, bool isLeftClicked, int cx, int cy);

    /// @brief ステージ選択入力を更新する
    /// @param mouseX マウスX座標
    /// @param mouseY マウスY座標
    /// @param isLeftClicked 左クリックされたか
    /// @param cx 画面中心X座標
    /// @param cy 画面中心Y座標
    void UpdateStageSelect(int mouseX, int mouseY, bool isLeftClicked, int cx, int cy);

    /// @brief キャラクター選択画面を描画する
    /// @param cx 画面中心X座標
    /// @param cy 画面中心Y座標
    /// @param mouseX マウスX座標
    /// @param mouseY マウスY座標
    /// @param font24 本文フォントハンドル
    /// @param subFont 補助フォントハンドル
    void DrawCharacterSelect(int cx, int cy, int mouseX, int mouseY, int font24, int subFont);

    /// @brief ステージ選択画面を描画する
    /// @param cx 画面中心X座標
    /// @param cy 画面中心Y座標
    /// @param mouseX マウスX座標
    /// @param mouseY マウスY座標
    /// @param font24 本文フォントハンドル
    /// @param titleFont タイトルフォントハンドル
    void DrawStageSelect(int cx, int cy, int mouseX, int mouseY, int font24, int titleFont);

    /// @brief UIボタンを描画する
    /// @param x X座標
    /// @param y Y座標
    /// @param w 幅
    /// @param h 高さ
    /// @param text 表示文字列
    /// @param hover マウスホバー中か
    /// @param color ボタン色
    /// @param font24 フォントハンドル
    void DrawButton(int x, int y, int w, int h, const char* text, bool hover, int color, int font24);


    int phase_;           ///< 選択画面の現在フェーズ
    int ui_button_graph_; ///< ボタン画像ハンドル
    int wait_count_;      ///< 入力待ちや遷移待ちのカウンター
};