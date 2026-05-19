#include "TitleScene.h"
#include "../Input/InputManager.h"
#include <DxLib.h>

void TitleScene::Initialize() {
    // 初期化処理（画像の読み込みなど）
}

SceneType TitleScene::Update() {
    // Zキーまたはエンターキーが押された瞬間だけステージ選択画面へ遷移
    if (InputManager::IsKeyPush(KEY_INPUT_RETURN) || InputManager::IsKeyPush(KEY_INPUT_Z)) {
        return SceneType::StageSelect;
    }
    return SceneType::Title; // 遷移しない場合はそのまま
}

void TitleScene::Draw() {
    DrawString(100, 100, "TITLE SCENE (Press ENTER to Start)", GetColor(255, 255, 255));
}
