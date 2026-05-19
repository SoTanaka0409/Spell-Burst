#include "GameScene.h"
#include "../Object/ObjectManager.h"
#include "../Input/InputManager.h"
#include <DxLib.h>

GameScene::GameScene() {
    m_objectManager = new ObjectManager();
}

GameScene::~GameScene() {
    delete m_objectManager;
}

void GameScene::Initialize() {
    // 全オブジェクトの初期化
    m_objectManager->Initialize();
}

SceneType GameScene::Update() {
    // 全オブジェクトの更新
    m_objectManager->Update();

    // 実際のゲームでは、プレイヤーが死んだりクリアしたときに遷移します
    // ここでは仮で、Zキーまたはエンターキーが押されたらリザルト画面へ遷移とします
    if (InputManager::IsKeyPush(KEY_INPUT_RETURN) || InputManager::IsKeyPush(KEY_INPUT_Z)) {
        return SceneType::Result;
    }
    return SceneType::Game; // 遷移しない場合はそのまま
}

void GameScene::Draw() {
    // 背景色を少し明るいネイビーブルーなどに設定して見やすくする
    SetBackgroundColor(20, 30, 60);

    // 全オブジェクトの描画
    m_objectManager->Draw();

    DrawString(100, 100, "GAME SCENE (Press ENTER to Result)", GetColor(255, 255, 255));
}
