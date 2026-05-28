#include "ResultScene.h"
#include "SceneManager.h"
#include "Master.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "Utility.h"
#include "GameScene.h"
#include "Player.h"
#include <DxLib.h>
#include <cmath>
#include <cstdlib>

bool ResultScene::s_isVictory = false;

void ResultScene::Initialize() {
    m_stateTimer = 0;
    m_particles.clear();
    
    if (s_isVictory) {
        SoundManager::GetInstance()->PlayBGM("Resource/BGM/MusMus-BGM-115.mp3");
        m_bgGraph = ResourceManager::GetInstance()->GetGraph("Resource/bg_phase1.png");
        Utility::SaveTimeRanking((GameScene::s_playFrameCount * 1000) / 60); 
    } else {
        SoundManager::GetInstance()->PlayBGM("Resource/BGM/MusMus-BGM-112.mp3");
        m_bgGraph = ResourceManager::GetInstance()->GetGraph("Resource/bg_phase3.png"); 
    }
    
    if (Player::s_selectedCharacterType == 2) {
        m_playerGraph = ResourceManager::GetInstance()->GetGraph("Resource/player2.png");
    } else if (Player::s_selectedCharacterType == 3) {
        m_playerGraph = ResourceManager::GetInstance()->GetGraph("Resource/player3.png");
    } else {
        m_playerGraph = ResourceManager::GetInstance()->GetGraph("Resource/player1.png");
    }
}

void ResultScene::Update() {
    m_stateTimer++;
    
    if (InputManager::CheckDownKey(KEY_INPUT_RETURN) || InputManager::CheckDownKey(KEY_INPUT_Z) || 
       (GetMouseInput() & MOUSE_INPUT_LEFT)) {
        if (m_stateTimer > 60) {
            SoundManager::GetInstance()->PlaySE("Resource/SE/Œˆ’èƒ{ƒ^ƒ“‚ð‰Ÿ‚·42.mp3");
            Master::sceneManager->SetNextScene(SceneManager::SCENE_TITLE);
        }
    }
    
    if (s_isVictory) {
        if (m_stateTimer % 2 == 0) {
            ResultParticle p;
            p.x = static_cast<float>(rand() % Utility::SCREEN_WIDTH);
            p.y = -50.0f;
            p.vx = (rand() % 100 - 50) / 20.0f;
            p.vy = (rand() % 100 + 50) / 20.0f;
            p.size = 5.0f + (rand() % 15);
            p.angle = 0.0f;
            p.rotSpeed = (rand() % 100 - 50) / 200.0f;
            
            int r = 150 + rand() % 105;
            int g = 150 + rand() % 105;
            int b = 50 + rand() % 105;
            p.color = GetColor(r, g, b);
            p.life = 300;
            m_particles.push_back(p);
        }
    } else {
        if (m_stateTimer % 3 == 0) {
            ResultParticle p;
            p.x = static_cast<float>(rand() % Utility::SCREEN_WIDTH);
            p.y = Utility::SCREEN_HEIGHT + 50.0f;
            p.vx = (rand() % 100 - 50) / 30.0f;
            p.vy = -(rand() % 100 + 50) / 30.0f;
            p.size = 3.0f + (rand() % 10);
            p.angle = 0.0f;
            p.rotSpeed = 0.0f;
            
            p.color = GetColor(150 + rand() % 105, 0, 0);
            p.life = 300;
            m_particles.push_back(p);
        }
    }
    
    for (auto it = m_particles.begin(); it != m_particles.end(); ) {
        it->x += it->vx;
        it->y += it->vy;
        it->angle += it->rotSpeed;
        if (s_isVictory) {
            it->vx += std::sin(m_stateTimer * 0.05f + it->y * 0.01f) * 0.1f;
        }
        it->life--;
        if (it->life <= 0 || it->y > Utility::SCREEN_HEIGHT + 100 || it->y < -100) {
            it = m_particles.erase(it);
        } else {
            ++it;
        }
    }
    
    Scene::Update();
}

void ResultScene::DrawOutlinedString(int x, int y, const char* str, unsigned int color, unsigned int outlineColor, int fontHandle) {
    DrawStringToHandle(x - 2, y - 2, str, outlineColor, fontHandle);
    DrawStringToHandle(x + 2, y - 2, str, outlineColor, fontHandle);
    DrawStringToHandle(x - 2, y + 2, str, outlineColor, fontHandle);
    DrawStringToHandle(x + 2, y + 2, str, outlineColor, fontHandle);
    DrawStringToHandle(x, y, str, color, fontHandle);
}

void ResultScene::Draw() {
    Scene::Draw();
    
    if (m_bgGraph != -1) {
        DrawExtendGraph(0, 0, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, m_bgGraph, FALSE);
        if (!s_isVictory) {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
            DrawBox(0, 0, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, GetColor(30, 0, 0), TRUE);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        } else {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
            DrawBox(0, 0, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, GetColor(255, 255, 255), TRUE);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
    } else {
        DrawBox(0, 0, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, GetColor(0, 10, 20), TRUE);
    }
    
    if (m_playerGraph != -1) {
        int w, h;
        GetGraphSize(m_playerGraph, &w, &h);
        float scale = 2.5f;
        int drawW = (int)(w * scale);
        int drawH = (int)(h * scale);
        
        int targetX = s_isVictory ? 150 : Utility::SCREEN_WIDTH / 2 - drawW / 2;
        int startX = s_isVictory ? -500 : Utility::SCREEN_WIDTH / 2 - drawW / 2;
        int targetY = Utility::SCREEN_HEIGHT - drawH - 50;
        int startY = s_isVictory ? targetY : Utility::SCREEN_HEIGHT + 200;
        
        float t = (m_stateTimer > 60) ? 1.0f : (m_stateTimer / 60.0f);
        t = 1.0f - std::pow(1.0f - t, 3.0f);
        
        int drawX = startX + (int)((targetX - startX) * t);
        int drawY = startY + (int)((targetY - startY) * t);
        
        if (!s_isVictory) {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
        }
        DrawExtendGraph(drawX, drawY, drawX + drawW, drawY + drawH, m_playerGraph, TRUE);
        if (!s_isVictory) {
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
    }
    
    for (const auto& p : m_particles) {
        if (s_isVictory) {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, (p.life > 200) ? 255 : p.life);
            // Confetti
            int s = static_cast<int>(p.size);
            int cx = static_cast<int>(p.x);
            int cy = static_cast<int>(p.y);
            // Draw rotated rect manually or just circle if we can't be bothered with rotation math
            DrawCircle(cx, cy, s, p.color, TRUE);
        } else {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, (p.life > 100) ? 150 : p.life);
            DrawCircle(static_cast<int>(p.x), static_cast<int>(p.y), static_cast<int>(p.size), p.color, TRUE);
        }
    }
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    
    int titleFont = ResourceManager::GetInstance()->GetFont(96, 8);
    int subFont = ResourceManager::GetInstance()->GetFont(48, 4);
    int promptFont = ResourceManager::GetInstance()->GetFont(32, 2);
    
    float textT = (m_stateTimer > 40) ? 1.0f : (m_stateTimer / 40.0f);
    textT = 1.0f - std::pow(1.0f - textT, 4.0f);
    int titleY = -100 + (int)(250 * textT);

    if (s_isVictory) {
        DrawOutlinedString(500, titleY, "GAME CLEAR!!", GetColor(255, 255, 0), GetColor(255, 100, 0), titleFont);
        if (m_stateTimer > 60) {
            DrawOutlinedString(550, titleY + 120, "THANK YOU FOR PLAYING", GetColor(255, 255, 255), GetColor(0, 0, 100), subFont);
        }
    } else {
        DrawOutlinedString(350, titleY, "GAME OVER", GetColor(255, 50, 50), GetColor(50, 0, 0), titleFont);
        if (m_stateTimer > 60) {
            DrawOutlinedString(400, titleY + 120, "TRY AGAIN...", GetColor(200, 200, 200), GetColor(50, 50, 50), subFont);
        }
    }

    if (m_stateTimer > 90) {
        int alpha = (int)(128 + 127 * std::sin(m_stateTimer / 10.0f));
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
        DrawOutlinedString(350, 600, "Press ENTER / Click to return to Title", GetColor(255, 255, 255), GetColor(0, 0, 0), promptFont);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}

void ResultScene::Finalize() {
}
