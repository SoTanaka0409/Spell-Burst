#include "GameScene.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "Master.h"
#include "Player.h"
#include "Enemy.h"
#include <DxLib.h>

GameScene::GameScene() {
}

GameScene::~GameScene() {
}

void GameScene::Initialize() {
    // プレイヤーの生成（自動的にObjectManagerに追加されます）
    new Player();

    // テスト用の敵の生成
    new Enemy(640.0f, 100.0f);
    new Enemy(440.0f, 150.0f);
    new Enemy(840.0f, 200.0f);
}

void GameScene::Update() {
    // 親クラスのUpdateを呼ぶことで、登録された全Object2Dが更新されます
    Scene::Update();

    if (InputManager::CheckDownKey(KEY_INPUT_RETURN) || InputManager::CheckDownKey(KEY_INPUT_Z)) {
        Master::sceneManager->SetNextScene(SceneManager::SCENE_RESULT);
    }
   // SetBackgroundColor(20, 30, 60);
}

void GameScene::Draw() {
    // 背景色の設定
    

    // 親クラスのDrawを呼ぶことで、登録された全Object2Dが描画されます
    Scene::Draw();

    DrawString(100, 100, "GAME SCENE (Press ENTER to Result)", GetColor(255, 255, 255));
}

void GameScene::Finalize() {
    // シーン遷移時に、このシーンに紐づいていた全オブジェクトを削除します
    GetObjectManager()->DeleteAll2D();
}
