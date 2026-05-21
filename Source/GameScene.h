#pragma once
#include "Scene.h"

class EnemyManager;

// ゲームのメインプレイ画面を管理するシーンクラス
class GameScene : public Scene {
private:
    // 敵の出現やWAVEの進行を管理するマネージャー
    EnemyManager* mpEnemyManager;

public:
    GameScene();
    virtual ~GameScene() override;

    // シーン遷移時に呼ばれ、プレイヤーやマネージャーの生成・初期化を行う
    void Initialize() override;

    // 毎フレーム呼ばれ、ゲーム全体のロジック（ポーズ、オブジェクト更新、当たり判定）を処理する
    void Update() override;

    // 毎フレーム呼ばれ、背景や各オブジェクト、HUD（HPや経験値）を描画する
    void Draw() override;

    // シーン終了時に呼ばれ、確保したメモリを解放する
    void Finalize() override;
};
