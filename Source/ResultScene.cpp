#include "ResultScene.h"
#include "../Input/InputManager.h"
#include <DxLib.h>

void ResultScene::Initialize() {
    // 初期化処理（スコアの計算や結果の表示準備など）
}

SceneType ResultScene::Update() {
    // Zキーまたはエンターキーが押された瞬間にタイトル画面へ戻る
    if (InputManager::IsKeyPush(KEY_INPUT_RETURN) || InputManager::IsKeyPush(KEY_INPUT_Z)) {
        return SceneType::Title;
    }
    return SceneType::Result; // 遷移しない場合はそのまま
}

void ResultScene::Draw() {
    DrawString(100, 100, "RESULT SCENE (Press ENTER to Title)", GetColor(255, 255, 255));
}
