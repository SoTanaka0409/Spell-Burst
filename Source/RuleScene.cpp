#include "RuleScene.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "Master.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "Utility.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <algorithm>

void RuleScene::Initialize() {
    rule_graphs_[0] = ResourceManager::GetInstance()->GetGraph("Resource/rule1.png");
    rule_graphs_[1] = ResourceManager::GetInstance()->GetGraph("Resource/rule2.png");
    rule_graphs_[2] = ResourceManager::GetInstance()->GetGraph("Resource/rule3.png");
    rule_graphs_[3] = ResourceManager::GetInstance()->GetGraph("Resource/rule4.png");
    rule_graphs_[4] = -1; // �����I�ȃX���C�h�ǉ��ɔ����Ă��炩���ߘg��m�ۂ�������
    rule_graphs_[5] = -1;
    current_slide_ = 0;
    SoundManager::GetInstance()->PlayBGM("Resource/BGM/MusMus-BGM-146.mp3");
}

void RuleScene::Update() {
    static int prevMouseInput = 0;
    int currentMouseInput = GetMouseInput();
    bool isLeftClicked = (currentMouseInput & MOUSE_INPUT_LEFT) != 0 && (prevMouseInput & MOUSE_INPUT_LEFT) == 0;
    prevMouseInput = currentMouseInput;

    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    
    if (isLeftClicked) {
        // �v���C���[���^�C�g���֖߂鑀���s�����ۂ̑J�ڏ���
        if (mouseX >= 600 && mouseX <= 700 && mouseY >= 840 && mouseY <= 890) {
            SoundManager::GetInstance()->PlaySE("Resource/se_click.wav");
            Master::sceneManager->SetNextScene(SceneManager::SCENE_TITLE);
            return;
        }
        
        // ���̃y�[�W�֐i�ޏ����i�ŏI�y�[�W�̏ꍇ�̓^�C�g���֖߂�j
        if (mouseX >= 900 && mouseX <= 1000 && mouseY >= 840 && mouseY <= 890) {
            SoundManager::GetInstance()->PlaySE("Resource/se_click.wav");
            if (current_slide_ < 5) {
                current_slide_++;
            } else {
                Master::sceneManager->SetNextScene(SceneManager::SCENE_TITLE);
                return;
            }
        }
        
        // �O�̃y�[�W�֖߂鏈���i�ŏ��̃y�[�W�ł͖����j
        if (mouseX >= 750 && mouseX <= 850 && mouseY >= 840 && mouseY <= 890) {
            SoundManager::GetInstance()->PlaySE("Resource/se_click.wav");
            if (current_slide_ > 0) {
                current_slide_--;
            }
        }
    }
}

void RuleScene::Draw() {
    DrawBox(0, 0, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, GetColor(0, 0, 0), TRUE);
    
    if (current_slide_ >= 0 && current_slide_ < 6 && rule_graphs_[current_slide_] != -1) {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
        int imgW = 1, imgH = 1;
        GetGraphSize(rule_graphs_[current_slide_], &imgW, &imgH);
        
        if (imgW > 0 && imgH > 0) {
            float maxWidth = 1400.0f;
            float maxHeight = 650.0f; // ����摜�����₷���Ȃ�悤�`��̈��傫�߂ɐݒ�
            float scaleX = maxWidth / imgW;
            float scaleY = maxHeight / imgH;
            float scale = ((scaleX < scaleY) ? scaleX : scaleY) * 0.95f;
            
            int drawW = (int)(imgW * scale);
            int drawH = (int)(imgH * scale);
            int drawX = (Utility::SCREEN_WIDTH - drawW) / 2;
            int drawY = 20 + (650 - drawH) / 2;
            
            DrawExtendGraph(drawX, drawY, drawX + drawW, drawY + drawH, rule_graphs_[current_slide_], FALSE);
        }
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
    
    int titleFont = ResourceManager::GetInstance()->GetFont(32, 4);
    int font24 = ResourceManager::GetInstance()->GetFont(24, 3);
    
    const char* titles[] = {
        "1. �L�����N�^�[�̑I��",
        "2. ��Փx�̑I��",
        "3. �G��|���ă��x����グ�ă{�X��|�����I",
        "4. UI�̐��",
        "5. �o���A�̎g����",
        "6. �{�X��|����HP���񕜁I"
    };
    const char* descs1[] = {
        "�^�C�g����ʂ���GAME START������A���L���ȃV�F�t��I�ڂ��B",
        "�����ɂ�������Փx��I�ڂ��BNORMAL, HARD, VERY HARD�����邼�B",
        "�G��|���Čo���l��҂����I�{��̓E�F�[�u���ŁA",
        "����͎�����HP�⃌�x���A",
        "�o���A�W�J���ɓG�̒e��󂯂�Ɨ͂����܂�A",
        "�{�X��|����HP��3�񕜂��邼�I"
    };
    const char* descs2[] = {
        "",
        "",
        "��萔�|���ƃ{�X���o�邼�I",
        "�K�E�Z�̃Q�[�W���\������Ă��邼�I",
        "�Ō�ɋ��͂Ȕ����Ƃ��ĕ��o���邼�I���܂��g�����I",
        "�Ō�܂Œ��߂��ɐ킦�I"
    };
    const char* descs3[] = {
        "�����@�̒��S�ɂ��鏬���Ȍ���ʂ������蔻��ł��I",
        "",
        "",
        "",
        "",
        ""
    };
    
    DrawBox(300, 700, 1300, 830, GetColor(20, 20, 40), TRUE);
    DrawBox(300, 700, 1300, 830, GetColor(255, 255, 255), FALSE);
    
    if (current_slide_ >= 0 && current_slide_ < 6) {
        DrawStringToHandle(320, 710, titles[current_slide_], GetColor(255, 255, 0), titleFont);
        DrawStringToHandle(320, 755, descs1[current_slide_], GetColor(255, 255, 255), font24);
        DrawStringToHandle(320, 785, descs2[current_slide_], GetColor(255, 255, 255), font24);
        DrawStringToHandle(320, 815, descs3[current_slide_], GetColor(255, 100, 100), font24);
    }
    
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    
    // �����I�ȑ���𑣂����߁A�߂�{�^���Ƀ}�E�X���d�Ȃ����ۂɐF��ω�������
    bool hoverBack = (mouseX >= 600 && mouseX <= 700 && mouseY >= 840 && mouseY <= 890);
    DrawBox(600, 840, 700, 890, hoverBack ? GetColor(100, 100, 100) : GetColor(50, 50, 50), TRUE);
    DrawBox(600, 840, 700, 890, GetColor(255, 255, 255), FALSE);
    DrawStringToHandle(615, 855, "BACK", GetColor(255, 255, 255), font24);
    
    // ���݈ʒu�𖾎����邽�߁A2�y�[�W�ڈȍ~�̂ݑO�֖߂�{�^����`��
    if (current_slide_ > 0) {
        bool hoverPrev = (mouseX >= 750 && mouseX <= 850 && mouseY >= 840 && mouseY <= 890);
        DrawBox(750, 840, 850, 890, hoverPrev ? GetColor(100, 100, 100) : GetColor(50, 50, 50), TRUE);
        DrawBox(750, 840, 850, 890, GetColor(255, 255, 255), FALSE);
        DrawStringToHandle(770, 855, "PREV", GetColor(255, 255, 255), font24);
    }
    
    // �X���C�h�i�s�󋵂ɍ��킹�āA���փ{�^���Ɗ����{�^���̕\����؂�ւ��`��
    bool hoverNext = (mouseX >= 900 && mouseX <= 1000 && mouseY >= 840 && mouseY <= 890);
    DrawBox(900, 840, 1000, 890, hoverNext ? GetColor(100, 150, 100) : GetColor(50, 100, 50), TRUE);
    DrawBox(900, 840, 1000, 890, GetColor(255, 255, 255), FALSE);
    if (current_slide_ < 5) {
        DrawStringToHandle(920, 855, "NEXT", GetColor(255, 255, 255), font24);
    } else {
        DrawStringToHandle(920, 855, "DONE", GetColor(255, 255, 255), font24);
    }
    
    Scene::Draw();
}

void RuleScene::Finalize() {
}

