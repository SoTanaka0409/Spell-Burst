#pragma once
#include "Scene.h"
#include <vector>
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"

// タイトル画面を描画・管理するシーンクラス
class TitleScene : public Scene {
public:
    TitleScene();
    ~TitleScene();

    // [入力] なし
    // [出力] なし
    // [副作用] タイトル背景画像やUIボタン画像をメモリに読み込む
    void Initialize() override;

    // [入力] なし
    // [出力] なし
    // [副作用] キー入力を監視し、ZキーでStageSelectSceneへ遷移させる。背景スクロール更新も行う
    void Update() override;

    // [入力] なし
    // [出力] なし
    // [副作用] タイトルロゴ、背景、UIボタン等を画面に描画する
    void Draw() override;

    // [入力] なし
    // [出力] なし
    // [副作用] 読み込んだ画像リソースを破棄する
    void Finalize() override;

private:
    int m_bgGraph; // タイトル背景画像のハンドル
    float m_bgScrollX; // 背景スクロール演出のためのX座標オフセット
    int m_uiButtonGraph; // 選択ボタンUIの画像ハンドル
    std::vector<int> m_rankings; // クリアタイムなどのランキングデータ保持
};