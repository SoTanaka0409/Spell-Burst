#include "TitleScene.h"
#include "InputManager.h"
#include "Master.h"
#include "Player.h"
#include "ResourceManager.h"
#include <DxLib.h>

TitleScene::TitleScene()
{

}
TitleScene::~TitleScene()
{

}
void TitleScene::Initialize()
{

}

void TitleScene::Update()
{
    // MOUSE_INPUT_LEFT handles mouse clicks
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    
    // We have 3 character boxes around (200, 300), (400, 300), (600, 300) with size approx 100x100
    if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
        if (mouseX >= 150 && mouseX <= 250 && mouseY >= 250 && mouseY <= 350) {
            Player::s_selectedCharacterType = 1;
            Master::sceneManager->SetNextScene(SceneManager::SCENE_LEVEL);
        } else if (mouseX >= 350 && mouseX <= 450 && mouseY >= 250 && mouseY <= 350) {
            Player::s_selectedCharacterType = 2;
            Master::sceneManager->SetNextScene(SceneManager::SCENE_LEVEL);
        } else if (mouseX >= 550 && mouseX <= 650 && mouseY >= 250 && mouseY <= 350) {
            Player::s_selectedCharacterType = 3;
            Master::sceneManager->SetNextScene(SceneManager::SCENE_LEVEL);
        }
    }
    
    Scene::Update();
}

void TitleScene::Draw() {
    // 1. Draw solid background
    DrawBox(0, 0, 800, 600, GetColor(15, 20, 30), TRUE);
    Scene::Draw();
    
    // 2. Draw Title Text (using GetFont)
    int titleFont = ResourceManager::GetInstance()->GetFont(60, 5);
    int subFont = ResourceManager::GetInstance()->GetFont(24, 3);
    
    DrawStringToHandle(120, 80, "AI SUSHI CHEF", GetColor(255, 215, 0), titleFont);
    DrawStringToHandle(220, 150, "- SELECT YOUR CHARACTER -", GetColor(200, 200, 200), subFont);
    
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    
    int tex1 = ResourceManager::GetInstance()->GetGraph("Resource/player.png");
    int tex2 = ResourceManager::GetInstance()->GetGraph("Resource/player2.png");
    int tex3 = ResourceManager::GetInstance()->GetGraph("Resource/player3.png");
    
    // Draw Char 1
    bool hover1 = (mouseX >= 150 && mouseX <= 250 && mouseY >= 250 && mouseY <= 350);
    int s1 = hover1 ? 60 : 45;
    if (hover1) {
        DrawBox(140, 240, 260, 360, GetColor(50, 50, 100), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
        DrawBox(140, 240, 260, 360, GetColor(255, 255, 100), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
    DrawBox(140, 240, 260, 360, GetColor(200, 200, 255), FALSE);
    DrawExtendGraph(200 - s1, 300 - s1, 200 + s1, 300 + s1, tex1, TRUE);
    DrawStringToHandle(145, 380, "NORMAL CHEF", GetColor(200, 200, 255), subFont);
    if (hover1) DrawString(155, 410, "MASTER SPARK", GetColor(255, 255, 0));
    
    // Draw Char 2
    bool hover2 = (mouseX >= 350 && mouseX <= 450 && mouseY >= 250 && mouseY <= 350);
    int s2 = hover2 ? 60 : 45;
    if (hover2) {
        DrawBox(340, 240, 460, 360, GetColor(100, 50, 50), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
        DrawBox(340, 240, 460, 360, GetColor(255, 150, 150), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
    DrawBox(340, 240, 460, 360, GetColor(255, 200, 200), FALSE);
    DrawExtendGraph(400 - s2, 300 - s2, 400 + s2, 300 + s2, tex2, TRUE);
    DrawStringToHandle(355, 380, "GIRL CHEF", GetColor(255, 200, 200), subFont);
    if (hover2) DrawString(355, 410, "RAINBOW WAVE", GetColor(255, 255, 0));
    
    // Draw Char 3
    bool hover3 = (mouseX >= 550 && mouseX <= 650 && mouseY >= 250 && mouseY <= 350);
    int s3 = hover3 ? 60 : 45;
    if (hover3) {
        DrawBox(540, 240, 660, 360, GetColor(50, 100, 50), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
        DrawBox(540, 240, 660, 360, GetColor(150, 255, 150), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
    DrawBox(540, 240, 660, 360, GetColor(200, 255, 200), FALSE);
    DrawExtendGraph(600 - s3, 300 - s3, 600 + s3, 300 + s3, tex3, TRUE);
    DrawStringToHandle(560, 380, "OLD CHEF", GetColor(200, 255, 200), subFont);
    if (hover3) DrawString(545, 410, "CHERRY BLOSSOM", GetColor(255, 255, 0));
}

void TitleScene::Finalize() {
}
