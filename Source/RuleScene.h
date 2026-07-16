#pragma once
#include "Scene.h"

class RuleScene : public Scene
{
public:
    /*
     * 各スライド（画像）を読み込み配列に格納する。
     * [入力] なし
     * [出力] なし
     * [副作用] rule_graphs_に画像が読み込まれる
     */
    void Initialize() override;

    /*
     * 左右キーでスライドを切り替え、ZキーまたはE最終スライドでStageSelectSceneへ遷移する。
     * [入力] なし
     * [出力] なし
     * [副作用] current_slide_が更新され、シーン遷移が起きる場合がある
     */
    void Update() override;

    /*
     * 現在選択されているルールのスライド画像と、ナビゲーションテキストを描画する。
     * [入力] なし
     * [出力] なし
     * [副作用] 画面に描画される
     */
    void Draw() override;

    /*
     * 読み込んだ全てのスライド画像を解放する。
     * [入力] なし
     * [出力] なし
     * [副作用] メモリが解放される
     */
    void Finalize() override;
private:
    void DrawRuleText(int titleFont, int font24);
    void DrawNavigationButtons(int mouseX, int mouseY, int font24);

    int rule_graphs_[6];
    int current_slide_;
};
