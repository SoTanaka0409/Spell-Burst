#pragma once
#include "Scene.h"

// キャラクター選択および難易度（ステージ）選択を管理するシーンクラス
class StageSelectScene : public Scene {
public:
    // [入力] なし
    // [出力] なし
    // [副作用] 選択UI画像などを読み込む
    void Initialize() override;

    // [入力] なし
    // [出力] なし
    // [副作用] 矢印キー入力で選択項目を更新し、決定(Z)でフェーズ進行やゲーム開始(GameScene遷移)を行う
    void Update() override;

    // [入力] なし
    // [出力] なし
    // [副作用] 現在のフェーズ(キャラ選択/難易度選択)に応じたメニュー画面を描画する
    void Draw() override;

    // [入力] なし
    // [出力] なし
    // [副作用] 読み込んだ画像リソースを破棄する
    void Finalize() override;
private:
    int m_phase; // 0: Character, 1: Stage
    int m_uiButtonGraph;
    int m_WaitCount;
};