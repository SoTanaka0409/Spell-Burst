#include "StageSelectScene.h"
#include "../Input/InputManager.h"
#include <DxLib.h>

void StageSelectScene::Initialize() {
    // 初期化処理（画像の読み込みなど）
}

SceneType StageSelectScene::Update() {
    // Zキーまたはエンターキーが押された瞬間にゲーム画面へ遷移
    if (InputManager::IsKeyPush(KEY_INPUT_RETURN) || InputManager::IsKeyPush(KEY_INPUT_Z)) {
        return SceneType::Game;
    }
    return SceneType::StageSelect; // 遷移しない場合はそのまま
}

void StageSelectScene::Draw() {
    DrawString(100, 100, "STAGE SELECT SCENE (Press ENTER to Game)", GetColor(255, 255, 255));
}
