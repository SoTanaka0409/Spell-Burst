#pragma once
#include "Scene.h"

class StageSelectScene : public Scene
{
public:
    /*
     * キャラクター・ステージ選択UIの初期化を行う。
     * [入力] なし
     * [出力] なし
     * [副作用] UIリソースが確保される
     */
    void Initialize() override;
    /*
     * マウス入力に応じてキャラクター選択とステージ選択フェーズを更新する。
     * [入力] なし
     * [出力] なし
     * [副作用] phase_が変わりシーン遷移が起きる場合がある
     */
    void Update() override;
    /*
     * 現在のphase_に応じてキャラクター選択かステージ選択のUIを描画する。
     * [入力] なし
     * [出力] なし
     * [副作用] 画面に描画される
     */
    void Draw() override;
    /*
     * 読み込んだリソースを解放する。
     * [入力] なし
     * [出力] なし
     * [副作用] メモリが解放される
     */
    void Finalize() override;

private:
    void UpdateCharacterSelect(int mouseX, int mouseY, bool isLeftClicked, int cx, int cy);
    void UpdateStageSelect(int mouseX, int mouseY, bool isLeftClicked, int cx, int cy);

    void DrawCharacterSelect(int cx, int cy, int mouseX, int mouseY, int font24, int subFont);
    void DrawStageSelect(int cx, int cy, int mouseX, int mouseY, int font24, int titleFont);
    /*
     * UIボタンをホバー状態に応じて色を変えて描画するヘルパー関数。
     * [入力] x, y: 位置, w, h: サイズ, text: テキスト, hover: ホバー中か, color: 色, font24: フォント
     * [出力] なし
     * [副作用] 画面に描画される
     */
    void DrawButton(int x, int y, int w, int h, const char* text, bool hover, int color, int font24);

    int phase_;          // 0: キャラクター選択, 1: ステージ選択
    int ui_button_graph_;
    int wait_count_;
};
