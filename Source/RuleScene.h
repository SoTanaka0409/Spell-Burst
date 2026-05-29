#pragma once
#include "Scene.h"

// 操作説明やルール（チュートリアル）をスライド形式で表示するシーンクラス
class RuleScene : public Scene {
public:
    // [入力] なし
    // [出力] なし
    // [副作用] 各スライド（画像）を読み込み配列に格納する
    void Initialize() override;

    // [入力] なし
    // [出力] なし
    // [副作用] 左右キーでスライドを切り替え、Zキーまたは最終スライド次ページでStageSelectSceneへ遷移する
    void Update() override;

    // [入力] なし
    // [出力] なし
    // [副作用] 現在選択されているルールのスライド画像および、下部のナビゲーションテキストを描画する
    void Draw() override;

    // [入力] なし
    // [出力] なし
    // [副作用] 読み込んだ全てのスライド画像を破棄する
    void Finalize() override;
private:
    int m_ruleGraphs[6];
    int m_currentSlide;
};